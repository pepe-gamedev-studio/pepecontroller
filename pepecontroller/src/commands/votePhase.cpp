#include "votePhase.h"

#include "vote.h"

namespace commands 
{
	VotePhase::VotePhase() : VotesCounter(counter_size, 0)
	{
		mergeCommands(this->voteCommands);
	}
	const CommandSet& VotePhase::GetCommands()
	{
		return this->voteCommands;
	}
	bool VotePhase::Vote(user_id user, uint32_t num)
	{
		auto it = std::find(this->VoteCache.begin(), this->VoteCache.end(), user);
		if (num < this->counter_size && it == this->VoteCache.end())
		{
			++this->VotesCounter[num];
			VoteCache.insert(user);
			return true;
		}
		else return false;
	}
}