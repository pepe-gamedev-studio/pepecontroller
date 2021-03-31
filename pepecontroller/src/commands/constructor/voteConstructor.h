#pragma once
#include "../commandConstructor.h"
#include <memory>

namespace phase
{
	class VotePhase;
}

namespace commands
{
class VoteConstructor : public CommandConstructor
{
public:
	VoteConstructor(phase::VotePhase* ph);
	std::unique_ptr<Command> Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg) override;
private:
	phase::VotePhase* phase;
};
	
}
