#include "unban.h"
#include <boost/log/trivial.hpp>

namespace commands
{

	Unban::Unban(const std::string& name) : name(name) {}

	void Unban::Execute(Context* ctx)
	{
		using namespace storage::models::user;
		ctx->api->FindUser(&User::name, name, [&](std::optional<User> u)
		{
			if (u && u->group == Ignored)
			{
				ctx->api->UpdateUser(
					{u->id, u->name, u->voteWeight, Viewer});
			}

			BOOST_LOG_TRIVIAL(debug)
                          << "[Unban::Execute] " << name << " "
                          << (u ? "FOUND" : "UNKNOWN");
		});
		
	}

}