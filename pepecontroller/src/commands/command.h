#pragma once
#include "../peka2tv/peka2tvHttpClient.h"
#include "../peka2tv/peka2tvSIOClient.h"
#include "../storage/sqliteStorage.h"
#include "../appApi.h"

namespace commands
{

struct Context
{
	const peka2tv::Peka2tvSIOClient::ChatMessage* message;
	storage::Storage* storage;
	peka2tv::Peka2tvHttpClient* httpClient;
	AppApi* api;
};

struct Command
{
	virtual void Execute(Context* ctx) = 0;
	virtual ~Command() = default;
};

}
