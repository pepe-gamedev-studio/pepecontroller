#pragma once
#include "phase.h"
namespace phase
{
	class SkipConstructor;
	class MoviePhase : public Phase
	{
	public:
		MoviePhase();
		const CommandSet& GetCommands() override;
		bool Skip(user_id user);
	private:
		CommandSet movieCommands;
		std::unordered_set<user_id> skipCache;
		uint32_t skipCounter = 0;
	};
}