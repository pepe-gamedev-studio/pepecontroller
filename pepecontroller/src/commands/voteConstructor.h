#pragma once
#include "commandConstructor.h"

#include <memory>

namespace commands
{

class VoteConstructor: public CommandConstructor
{
public:
	std::unique_ptr<Command> Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg) override;
};

}
