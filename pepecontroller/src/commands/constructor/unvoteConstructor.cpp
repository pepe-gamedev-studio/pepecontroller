#include "unvoteConstructor.h"
#include "../../phase/votePhase.h"
#include "../command/unvote.h"
namespace commands
{

	UnvoteConstructor::UnvoteConstructor(phase::VotePhase* ph) : phase(ph)
	{
	}
	std::unique_ptr<Command> UnvoteConstructor::Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg)
	{
		return std::make_unique<Unvote>(phase);
	}
	
}