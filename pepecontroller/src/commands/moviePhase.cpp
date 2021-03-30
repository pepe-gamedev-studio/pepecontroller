#include "moviePhase.h"
#include "likeConstructor.h"
#include "dislikeConstructor.h"
namespace commands
{
	MoviePhase::MoviePhase() : movieCommands({
			{"like", std::make_shared<commands::LikeConstructor>() },
			{"dislike", std::make_shared<commands::DislikeConstructor>() },
		})
	{
		mergeCommands(this->movieCommands);
	}
	const CommandSet& MoviePhase::GetCommands()
	{
		return this->movieCommands;
	}
}