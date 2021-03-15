#pragma once
#include "commands/command.h"
#include "commands/commandConstructor.h"
#include "commands/phase.h"
#include "storage/models/user.h"
#include "storage/sqliteStorage.h"
#include "peka2tv/peka2tvHttpClient.h"
#include "peka2tv/peka2tvSIOClient.h"
#include "userCache.h"
#include "appApi.h"
#include "commands/phase.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <fstream>
class App
{
public:
	using CommandSet = std::unordered_map<std::string, std::shared_ptr<commands::CommandConstructor>>;
public:
	explicit App(
		peka2tv::Peka2tvSIOClient::EventHubPtr msgSource,
		storage::Storage* storage,
		peka2tv::Peka2tvHttpClient* httpClient);
	~App();
public:
	void HandleMessage(const peka2tv::Peka2tvSIOClient::ChatMessage& x);
	/*void SetCommands(const CommandSet& set);*/
	template <typename T, typename std::enable_if<std::is_base_of<commands::Phase, T>::value, bool>::type = true> void SetPhase()
	{
		this->phase = std::make_unique<T>();
	}
private:
	bool CanExecute(const peka2tv::Peka2tvSIOClient::ChatMessage & x);
	bool IsOwner(const peka2tv::Peka2tvSIOClient::ChatMessage & msg);
	bool IsCommand(const std::string& msg);
	std::string ExtractCommand(const std::string& msg);
	
private:
	peka2tv::Peka2tvSIOClient::EventHubPtr msgSource;
	storage::Storage* storage;
	peka2tv::Peka2tvHttpClient* httpClient;
	std::ofstream logFile;
	UserCache userCache;
	AppApi appApi;
	/*CommandSet commands;*/
	std::unique_ptr<commands::Phase> phase;
};

