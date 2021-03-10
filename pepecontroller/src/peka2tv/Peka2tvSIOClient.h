#pragma once
#include <sio_client.h>

#include <boost/signals2.hpp>

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <optional>

namespace peka2tv
{

class Peka2tvSIOClient
{
public:
	struct ChatMessage
	{
		struct User
		{
			int64_t	color;
			int64_t		id;
			std::string	name;
		};

		User					from;
		std::optional<User>		to;
		std::string				text;
		uint64_t				timestamp;
		bool					anonymous;
		std::string				channel;
	};
	using ms = int;
	using EventHub = boost::signals2::signal<void(const ChatMessage&)>;
	using EventHubPtr = std::shared_ptr<EventHub>;
public:
	void Connect(std::string host = "http://chat.sc2tv.ru/");
	EventHubPtr Join(std::string channel);
	void Leave(std::string channel);
	~Peka2tvSIOClient();
private:
	void OnMessage(sio::event& e);
	void RemoveDanglingListeners();
private:
	static ChatMessage ParseChatMessage(std::map<std::string, sio::message::ptr>& obj);
private:
	std::string host;
	sio::client client;

	bool isChatListen = false;
	std::unordered_map<std::string, std::weak_ptr<EventHub>> chatListeners;
	std::vector<std::weak_ptr<EventHub>> allChatListeners;
};
void LogChatCommands(const Peka2tvSIOClient::ChatMessage&, std::ofstream&);
}
