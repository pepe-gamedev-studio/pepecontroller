#pragma once
#include "../peka2tv/peka2tvSIOClient.h"
#include "command.h"

#include <memory>

namespace commands
{

struct CommandConstructor // base class
{
	virtual std::unique_ptr<Command> Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg) = 0;
	virtual ~CommandConstructor() = default;
};

}
