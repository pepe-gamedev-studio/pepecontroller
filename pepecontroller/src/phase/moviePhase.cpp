#include "moviePhase.h"
#include "../commands/constructor/likeConstructor.h"
#include "../commands/constructor/dislikeConstructor.h"
#include "../commands/constructor/skipConstructor.h"
namespace phase
{
	using namespace storage::models::user;
	MoviePhase::MoviePhase() : Commands(
		{
			{"skip", 
			{std::make_shared<commands::SkipConstructor>(this), UserGroup::Viewer} },
			{"like", 
			{std::make_shared<commands::LikeConstructor>(), UserGroup::Viewer} },
			{"dislike", 
			{std::make_shared<commands::DislikeConstructor>(), UserGroup::Viewer} },
		})
	{
		mergeCommands(this->Commands);
	}
	const CommandSet& MoviePhase::GetCommands()
	{
		return this->Commands;
	}
	bool MoviePhase::Skip(user_id user)
	{
		auto it = this->SkipCache.find(user);
		if (it == this->SkipCache.end())
		{
			++this->skipCounter;
			this->SkipCache.insert(user);
			return true;
		}
		else return false;
	}
}