#pragma once
#include "phase.h"
#include "likeConstructor.h"
#include "dislikeConstructor.h"
namespace commands
{
	class MoviePhase : public Phase
	{
	public:
		MoviePhase();
		const CommandSet& GetCommands() override;
	private:
		CommandSet movieCommands
		{
			{"like", std::make_shared<commands::LikeConstructor>() },
			{"dislike", std::make_shared<commands::DislikeConstructor>() },
		};
	};
}