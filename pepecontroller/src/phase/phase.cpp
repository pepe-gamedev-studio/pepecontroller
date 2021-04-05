#include "phase.h"
#include "../commands/constructor/banConstructor.h"
#include "../commands/constructor/unbanConstructor.h"
#include "../commands/constructor/updateConstructor.h"
#include "../commands/constructor/likeConstructor.h"
#include "../commands/constructor/dislikeConstructor.h"

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
		{"like",
		{ std::make_shared<commands::LikeConstructor>(), UserGroup::Viewer} 
		},
		{"dislike",
		{ std::make_shared<commands::DislikeConstructor>(), UserGroup::Viewer} 
		},
	}) {}

void Phase::mergeCommands(CommandSet& cs)
{
	cs.insert(basicCommands.begin(), basicCommands.end());
}

}