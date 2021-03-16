#include "moviePhase.h"
namespace commands
{
	MoviePhase::MoviePhase()
	{
		mergeCommands(this->movieCommands);
	}
	const CommandSet& MoviePhase::GetCommands()
	{
		return this->movieCommands;
	}
}