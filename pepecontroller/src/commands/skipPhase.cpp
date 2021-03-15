#include "skipPhase.h"
namespace commands
{
	SkipPhase::SkipPhase()
	{
		mergeCommands(this->skipCommands);
	}
	const Phase::CommandSet& SkipPhase::GetCommands()
	{
		return this->skipCommands;
	}
}