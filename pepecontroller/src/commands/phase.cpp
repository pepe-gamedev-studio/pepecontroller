#include "phase.h"
namespace commands
{

Phase::Phase()
{
}
void Phase::mergeCommands(CommandSet& cs)
{
	cs.insert(basicCommands.begin(), basicCommands.end());
}

}