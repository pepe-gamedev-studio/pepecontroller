#pragma once
#include "commandConstructor.h"
#include "phase.h"

#include <memory>

namespace commands
{

class VoteConstructor : public CommandConstructor
{
public:
	VoteConstructor(VotePhase* ph);
	std::unique_ptr<Command> Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg) override;
private:
	VotePhase* phase;
};
	
}
