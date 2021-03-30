#include "phase.h"
#include "banConstructor.h"
#include "unbanConstructor.h"

namespace commands
{

	Phase::Phase() : basicCommands({
		{"ban", std::make_shared<commands::BanConstructor>() },
		{"unban", std::make_shared<commands::UnbanConstructor>() },
	})
{
}
void Phase::mergeCommands(CommandSet& cs)
{
	cs.insert(basicCommands.begin(), basicCommands.end());
}

}