#include "votePhase.h"
#include "../commands/constructor/unvoteConstructor.h"
#include "../commands/constructor/voteConstructor.h"

namespace phase 
{
	using namespace storage::models::user;
	VotePhase::VotePhase() : votesCounter(counter_size, 0),
		voteCommands(
		{ 
			{"vote", 
			{std::make_shared<commands::VoteConstructor>(this), UserGroup::Viewer }},
			{"unvote",
			{std::make_shared<commands::UnvoteConstructor>(this), UserGroup::Viewer}}
		})
	{
		mergeCommands(this->voteCommands);
	}
	const CommandSet& VotePhase::GetCommands()
	{
		return this->voteCommands;
	}
	bool VotePhase::Vote(user_id user, uint32_t num)
	{
		auto it = this->voteCache.find(user);
		if (num < this->counter_size && it == this->voteCache.end())
		{
			++this->votesCounter[num];
			voteCache.insert({ user, num });
			return true;
		}
		else return false;
	}
	bool VotePhase::Unvote(user_id user)
	{
		auto it = this->voteCache.find(user);
		if (it != this->voteCache.end())
		{
			--this->votesCounter[this->voteCache[user]];
			voteCache.erase(user);
			return true;
		}
		else return false;
	}
}