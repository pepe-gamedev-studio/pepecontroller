#include "phase.h"
#include "../commands/constructor/banConstructor.h"
#include "../commands/constructor/unbanConstructor.h"

namespace phase
{

	Phase::Phase() : basicCommands({
		{"ban", std::make_shared<commands::BanConstructor>() },
		{"unban", std::make_shared<commands::UnbanConstructor>() },
		//{"update", std::make_shared<commands::UpdateConstructor>() },
	})
{
}
void Phase::mergeCommands(CommandSet& cs)
{
	cs.insert(basicCommands.begin(), basicCommands.end());
}

}