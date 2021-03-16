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
}