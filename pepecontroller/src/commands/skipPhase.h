#pragma once
#include "phase.h"
#include "likeConstructor.h"
#include "dislikeConstructor.h"
#include "skipConstructor.h"
namespace commands
{
	class SkipPhase : public Phase
	{
	public:
		SkipPhase();
		const CommandSet& GetCommands() override;
	private:
		CommandSet skipCommands
		{
			{"skip", std::make_shared<commands::SkipConstructor>() },
			{"like", std::make_shared<commands::LikeConstructor>() },
			{"dislike", std::make_shared<commands::DislikeConstructor>() },
		};
	};
}