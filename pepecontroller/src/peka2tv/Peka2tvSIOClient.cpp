#include "Peka2tvSIOClient.h"

#include <iostream>
#include <functional>
#include <nlohmann/json.hpp>
#include <fstream>
#include <boost/date_time/posix_time/posix_time.hpp>
namespace peka2tv
{

void Peka2tvSIOClient::Connect(std::string host)
{
	this->host = host;
	client.connect(host);
}

Peka2tvSIOClient::EventHubPtr Peka2tvSIOClient::Join(std::string channel)
{
	auto args = sio::object_message::create();

	std::dynamic_pointer_cast<sio::object_message>(args)->insert("channel", channel);

	client.socket()->emit("/chat/join", args);

	if (!isChatListen)
	{
		client.socket()->on("/chat/message", std::bind(&Peka2tvSIOClient::OnMessage, this, std::placeholders::_1));
		isChatListen = true;
	}

	auto eh = std::make_shared<EventHub>();
	if (channel == "all")
		allChatListeners.push_back(eh);
	else
		chatListeners.insert({ channel, eh });

	return eh;
}

void Peka2tvSIOClient::Leave(std::string channel)
{
	auto args = sio::object_message::create();

	std::dynamic_pointer_cast<sio::object_message>(args)->insert("channel", channel);

	client.socket()->emit("/chat/leave", args);
}

Peka2tvSIOClient::~Peka2tvSIOClient()
{
	client.close();
}

void Peka2tvSIOClient::OnMessage(sio::event & e)
{
	auto msg = e.get_message()->get_map();

	RemoveDanglingListeners();

	std::optional<ChatMessage> m;
	if (!allChatListeners.empty())
	{
		m = ParseChatMessage(msg);

		for (auto x : allChatListeners)
			(*x.lock())(*m);
	}

	const std::string channel = msg["channel"]->get_string();
	auto found = chatListeners.find(channel);
	if (found == chatListeners.end())
	{
		Leave(channel);
		return;
	}

	auto listener = found->second.lock();
	if (!listener)
	{
		chatListeners.erase(found);
		Leave(channel);
		return;
	}

	if (!m)
		m = ParseChatMessage(msg);

	(*listener)(*m);
}

void Peka2tvSIOClient::RemoveDanglingListeners()
{
	auto rit = std::remove_if(allChatListeners.begin(), allChatListeners.end(), [](const std::weak_ptr<EventHub>& x)
	{
		return !x.lock();
	});

	allChatListeners.erase(rit, allChatListeners.end());
}

void LogChatCommands(const Peka2tvSIOClient::ChatMessage& m, std::ofstream& f)
{	
	boost::posix_time::ptime date_time = boost::posix_time::microsec_clock::local_time();
	if(!f.is_open())
		f.open("log.txt", std::ios::app);
	f << "[" << date_time << "] " << m.from.name << "#" << m.from.id << ": " << m.text << std::endl;
}

Peka2tvSIOClient::ChatMessage Peka2tvSIOClient::ParseChatMessage(std::map<std::string, sio::message::ptr>& obj)
{
	ChatMessage m;

	auto from = obj["from"]->get_map();
	m.from.id = from["id"]->get_int();
	m.from.name = from["name"]->get_string();
	m.from.color = from["color"]->get_int();

	auto to = obj["to"];
	if (to->get_flag() == sio::message::flag::flag_object)
	{
		auto o = to->get_map();
		m.to = { o["color"]->get_int(), o["id"]->get_int(), o["name"]->get_string() };
	}

	m.text = obj["text"]->get_string();
	m.timestamp = obj["time"]->get_int();
	m.anonymous = obj["anonymous"]->get_bool();
	m.channel = obj["channel"]->get_string();
	return m;
}

}
