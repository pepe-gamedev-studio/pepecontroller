#include "moviePhase.h"
#include "../commands/constructor/likeConstructor.h"
#include "../commands/constructor/dislikeConstructor.h"
namespace phase
{
	using namespace storage::models::user;
	MoviePhase::MoviePhase() : movieCommands(
		{
			{"like", 
			{std::make_shared<commands::LikeConstructor>(), UserGroup::Viewer} },
			{"dislike", 
			{std::make_shared<commands::DislikeConstructor>(), UserGroup::Viewer} },
		})
	{
		mergeCommands(this->movieCommands);
	}
	const CommandSet& MoviePhase::GetCommands()
	{
		return this->movieCommands;
	}
}