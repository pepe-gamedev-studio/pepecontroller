#pragma once
#include "phase.h"
namespace commands 
{
	class VotePhase : public Phase
	{
	public:
		VotePhase();
		const CommandSet& GetCommands() override;
		bool Vote(user_id user, uint8_t num);
		//uint8_t result();
	private:
		CommandSet voteCommands
		{
			{"vote", std::make_shared<commands::VoteConstructor>() },
		};
		std::unordered_set<user_id> VoteCache;
		const uint8_t counter_size = 10;
		std::vector<uint8_t> VotesCounter;
	};
}
