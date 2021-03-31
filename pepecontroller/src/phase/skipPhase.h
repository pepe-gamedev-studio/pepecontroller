#pragma once
#include "phase.h"
namespace phase
{
	class SkipConstructor;
	class SkipPhase : public Phase
	{
	public:
		SkipPhase();
		const CommandSet& GetCommands() override;
		bool Skip(user_id user);
	private:
		CommandSet skipCommands;
		std::unordered_set<user_id> SkipCache;
		uint32_t skipCounter = 0;
	};
}