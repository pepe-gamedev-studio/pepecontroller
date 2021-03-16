#pragma once
#include "phase.h"
#include "voteConstructor.h"
namespace commands 
{
	class VoteConstructor;
	class VotePhase : public Phase
	{
	public:
		VotePhase();
		const CommandSet& GetCommands() override;
		bool Vote(user_id user, uint32_t num);
		//uint8_t result();
	private:
		CommandSet voteCommands
		{
			{"vote", std::make_shared<VoteConstructor>(this) },
		};
		std::unordered_set<user_id> VoteCache;
		const uint32_t counter_size = 10;
		std::vector<uint8_t> VotesCounter;
	};

}
