#include "phase.h"
#include "../commands/constructor/banConstructor.h"
#include "../commands/constructor/unbanConstructor.h"
#include "../commands/constructor/updateConstructor.h"

namespace phase
{
	using namespace storage::models::user;
	Phase::Phase() : basicCommands
	({
		{"ban", 
		{ std::make_shared<commands::BanConstructor>(), UserGroup::Moderator } 
		},
		{"unban", 
		{ std::make_shared<commands::UnbanConstructor>(), UserGroup::Moderator} 
		},
		{"update", 
		{ std::make_shared<commands::UpdateConstructor>(), UserGroup::Admin } 
		},
	}) {}

void Phase::mergeCommands(CommandSet& cs)
{
	cs.insert(basicCommands.begin(), basicCommands.end());
}

}