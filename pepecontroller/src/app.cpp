#include "app.h"
#include <boost/log/trivial.hpp>

#include <functional>

App::App(
	peka2tv::Peka2tvSIOClient::EventHubPtr msgSource,
	storage::Storage* storage,
	peka2tv::Peka2tvHttpClient* httpClient) :
	msgSource(msgSource),
	storage(storage),
	httpClient(httpClient),
	userCache(1000),
	appApi(&userCache, storage, httpClient)
{
	msgSource->connect(std::bind(&App::HandleMessage, this, std::placeholders::_1));
}

App::~App()
{
	msgSource->disconnect_all_slots();
	logFile.close();
}

void App::HandleMessage(const peka2tv::Peka2tvSIOClient::ChatMessage & x)
{
	if (!(IsCommand(x.text) && CanExecute(x)))
		return;

	auto ctr = this->commands.find(ExtractCommand(x.text));
	if (ctr != this->commands.end())
	{
		commands::Context ctx{ &x, storage, httpClient, &appApi };
		ctr->second->Construct(x)->Execute(&ctx);
		peka2tv::LogChatCommands(x, logFile);
	}
}

bool App::CanExecute(const peka2tv::Peka2tvSIOClient::ChatMessage & x)
{
	using namespace storage::models::user;

	std::shared_ptr<User> user;

	if (auto found = userCache.Get(x.from.id))
	{
		user = found;
	}
	else if (auto found = storage->get_pointer<User>(x.from.id))
	{
		user = std::move(found);
		userCache.Insert(*user);
	}

	bool ret = !(user && user->group == UserGroup::Ignored) || IsOwner(x);

	BOOST_LOG_TRIVIAL(debug) << "[App::CanExecute] " << x.from.id << " " << ret;

	return ret;
}

void App::SetCommands(const CommandSet & set)
{
	this->commands = set;
}

bool App::IsOwner(const peka2tv::Peka2tvSIOClient::ChatMessage & msg)
{
	// stream/12345
	return std::stoi(msg.channel.substr(7)) == msg.from.id;
}

bool App::IsCommand(const std::string & msg)
{
	return !msg.empty() && msg.front() == '!';
}

std::string App::ExtractCommand(const std::string & msg)
{
	std::stringstream ss(msg);
	std::string cmd; ss >> cmd;

	return std::string(++cmd.begin(), cmd.end());
}
