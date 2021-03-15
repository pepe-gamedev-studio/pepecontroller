#include "moviePhase.h"
namespace commands
{
	MoviePhase::MoviePhase()
	{
		mergeCommands(this->movieCommands);
	}
	const Phase::CommandSet& MoviePhase::GetCommands()
	{
		return this->movieCommands;
	}
}