#include "unban.h"
#include <boost/log/trivial.hpp>

namespace commands
{

	Unban::Unban(const std::string& name) : name(name) {}

	void Unban::Execute(Context* ctx)
	{
		using namespace storage::models::user;

		auto u = ctx->api->FindUser(&User::name, name);
		if (u && u->group == UserGroup::Ignored)
		{
			ctx->api->UpdateUser({ u->id, u->name, u->voteWeight, UserGroup::Viewer });
		}

		BOOST_LOG_TRIVIAL(debug) << "[Unban::Execute] " << name << " " << (u ? "FOUND" : "UNKNOWN");
	}

}