#include "moviePhase.h"
#include "../commands/constructor/likeConstructor.h"
#include "../commands/constructor/dislikeConstructor.h"
#include "../commands/constructor/skipConstructor.h"
namespace phase
{
	using namespace storage::models::user;
	MoviePhase::MoviePhase() : movieCommands(
		{
			{"skip", 
			{std::make_shared<commands::SkipConstructor>(this), UserGroup::Viewer} 
			},

		})
	{
		mergeCommands(this->movieCommands);
	}
	const CommandSet& MoviePhase::GetCommands()
	{
		return this->movieCommands;
	}
	bool MoviePhase::Skip(user_id user)
	{
		auto it = this->skipCache.find(user);
		if (it == this->skipCache.end())
		{
			++this->skipCounter;
			this->skipCache.insert(user);
			return true;
		}
		else return false;
	}
}