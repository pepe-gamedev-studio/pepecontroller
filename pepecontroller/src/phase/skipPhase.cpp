#include "skipPhase.h"
#include "../commands/constructor/likeConstructor.h"
#include "../commands/constructor/dislikeConstructor.h"
#include "../commands/constructor/skipConstructor.h"
namespace phase
{
	SkipPhase::SkipPhase() : skipCommands({
			{"skip", std::make_shared<commands::SkipConstructor>(this) },
			{"like", std::make_shared<commands::LikeConstructor>() },
			{"dislike", std::make_shared<commands::DislikeConstructor>() },
		})
	{
		mergeCommands(this->skipCommands);
	}
	const CommandSet& SkipPhase::GetCommands()
	{
		return this->skipCommands;
	}
	bool SkipPhase::Skip(user_id user)
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