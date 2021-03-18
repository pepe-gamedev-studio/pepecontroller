#include "unvoteConstructor.h"
#include "votePhase.h"
#include "unvote.h"
namespace commands
{

	UnvoteConstructor::UnvoteConstructor(VotePhase* ph) : phase(ph)
	{
	}
	std::unique_ptr<Command> UnvoteConstructor::Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg)
	{
		return std::make_unique<Unvote>(phase);
	}
	
}