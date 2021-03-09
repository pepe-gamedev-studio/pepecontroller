#include "helper.h"

namespace storage::models::user
{

std::ostream& operator<<(std::ostream& os, const storage::models::user::User& x)
{
	return os << x.id << " " << x.name << " " << x.voteWeight << " " << x.group;
}

}
