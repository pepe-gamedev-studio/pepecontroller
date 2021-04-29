#include "ban.h"
#include "../../storage/SqliteStorage.h"
#include "../../peka2tv/peka2tvHttpClient.h"
#include <boost/log/trivial.hpp>

namespace commands
{
Ban::Ban(const std::string& name) : name(name) {}

void Ban::Execute(Context* ctx)
{
	using namespace storage::models::user;

	ctx->api->FindUser(&User::name, name, [=](std::optional<User> u)
	{
		if (u && (u->group != Ignored))
		{
			ctx->api->UpdateUser(
				{u->id, u->platform, u->name, u->voteWeight, Ignored});
		}

		BOOST_LOG_TRIVIAL(debug)
              << "[Ban::Execute] " << name << " " << (u ? "FOUND" : "UNKNOWN");
	});
	
}

}
