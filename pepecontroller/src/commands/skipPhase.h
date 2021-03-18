#pragma once
#include "phase.h"
#include "likeConstructor.h"
#include "dislikeConstructor.h"
#include "skipConstructor.h"
namespace commands
{
	class SkipConstructor;
	class SkipPhase : public Phase
	{
	public:
		SkipPhase();
		const CommandSet& GetCommands() override;
		bool Skip(user_id user);
	private:
		CommandSet skipCommands
		{
			{"skip", std::make_shared<commands::SkipConstructor>(this) },
			{"like", std::make_shared<commands::LikeConstructor>() },
			{"dislike", std::make_shared<commands::DislikeConstructor>() },
		};
		std::unordered_set<user_id> SkipCache;
		uint32_t skipCounter = 0;
	};
}