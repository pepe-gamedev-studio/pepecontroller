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
	AppApi* api;
};

struct Command // base class
{
	virtual void Execute(Context* ctx) = 0; // command implementation 
	virtual ~Command() = default;
};
}
