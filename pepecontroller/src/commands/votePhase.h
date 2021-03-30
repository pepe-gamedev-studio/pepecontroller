#pragma once
#include "phase.h"

#include <unordered_map>
namespace commands 
{
	class VotePhase : public Phase
	{
	public:
		VotePhase();
		const CommandSet& GetCommands() override;
		bool Vote(user_id user, uint32_t num);
		bool Unvote(user_id user);

	private:
		CommandSet voteCommands;
		const uint32_t counter_size = 10;
		std::vector<uint32_t> VotesCounter;
		std::unordered_map<user_id, uint32_t> VoteCache;
		
	};

}
