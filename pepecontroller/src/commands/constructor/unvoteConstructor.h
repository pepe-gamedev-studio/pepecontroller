#pragma once
#include "../commandConstructor.h"
#include <memory>

namespace phase
{
	class VotePhase;
}
namespace commands
{
	
	class UnvoteConstructor : public CommandConstructor
	{
	public:
		UnvoteConstructor(phase::VotePhase* ph);
		std::unique_ptr<Command> Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg) override;
	private:
		phase::VotePhase* phase;
	};

}
