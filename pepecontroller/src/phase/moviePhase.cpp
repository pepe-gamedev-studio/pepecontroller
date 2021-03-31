#include "moviePhase.h"
#include "../commands/constructor/likeConstructor.h"
#include "../commands/constructor/dislikeConstructor.h"
namespace phase
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