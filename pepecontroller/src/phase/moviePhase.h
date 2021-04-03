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
		CommandSet Commands;
		std::unordered_set<user_id> SkipCache;
		uint32_t skipCounter = 0;
	};
}