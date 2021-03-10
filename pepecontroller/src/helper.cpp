#include "helper.h"

namespace storage::models::user
{

static const std::vector<std::string> groups{ "Ignored", "Viewer", "Moderator", "Admin" };

std::ostream& operator<<(std::ostream& os, const storage::models::user::User& x)
{
	return os << x.id << " " << x.name << " " << x.voteWeight << " " << groups[x.group];
}

}
