#include "app.h"
#include <boost/log/trivial.hpp>
#include <functional>

App::App(
	/*peka2tv::Peka2tvSIOClient::EventHubPtr msgSource,*/
	storage::Storage* storage,
	pepebackend::Instance* inst,
	peka2tv::Peka2tvHttpClient* httpClient,
	peka2tv::Peka2tvSIOClient* sioClient,
	WebClients* w) :
	storage(storage),
	inst(inst),
	webclients(w),
	//httpClient(httpClient),
	userCache(1000),
	appApi(&userCache, storage, httpClient, inst)
{
	using namespace storage::models::user;
	sioClient->Connect();
	appApi.FindUser(&User::name, *webclients->sc2tv,
	                [=](std::optional<User> u)
	                {
		                User Owner = {u->id, u->name, u->voteWeight, Admin};
		                appApi.UpdateUser(Owner);
		                msgSource = sioClient->Join("stream/" + std::to_string(u->id));
		                msgSource->connect(
			                std::bind(&App::HandleMessage, this, std::placeholders::_1));
	                });
}

App::~App()
{
	msgSource->disconnect_all_slots();
	logFile.close();
}

void App::HandleMessage(const peka2tv::Peka2tvSIOClient::ChatMessage& x)
{
	using namespace storage::models::user;
	appApi.FindUser(&User::id, x.from.id, [=](std::optional<User> u)
	{
		if (!(IsCommand(x.text) && CanExecute(x)))
			return;
		auto ctr = this->phase->GetCommands().find(ExtractCommand(x.text));
		if (ctr != this->phase->GetCommands().end())
		{
			commands::Context ctx{&x, &appApi};
			if (u->group >= ctr->second.cmdGroup)
				ctr->second.cmdConst->Construct(x)->Execute(&ctx);
			LogChatCommands(x, logFile);
		}
	});
}

void App::NametoId(std::string name, std::function<void(int64_t)> callback)
{
	using namespace storage::models::user;
	appApi.FindUser(&User::name, name, [=](std::optional<User> u)
	{
		callback(u->id);
	});
}

bool App::CanExecute(const peka2tv::Peka2tvSIOClient::ChatMessage& x)
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
