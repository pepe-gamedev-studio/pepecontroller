#include "skipPhase.h"
namespace commands
{
	SkipPhase::SkipPhase()
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