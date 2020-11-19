#include "ban.h"

#include <boost/log/trivial.hpp>

namespace commands
{

Ban::Ban(std::string name) : name(name) {}

void Ban::Execute(Context* ctx)
{
	using namespace storage::models::user;

	auto u = ctx->api->FindUser(&User::name, name);
	if (u && u->group != UserGroup::Ignored)
	{
		ctx->api->UpdateUser({ u->id, u->name, u->voteWeight, UserGroup::Ignored });
	}

	BOOST_LOG_TRIVIAL(debug) << "[Ban::Execute] " << name << " " << (u ? "FOUND" : "UNKNOWN");
}

}
