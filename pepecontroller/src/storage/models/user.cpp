#include "user.h"

namespace storage::models::user
{

TableType MakeTable()
{
	using namespace sqlite_orm;

	return make_table("user",
		make_column("id", &User::id, primary_key()),
		make_column("name", &User::name, collate_nocase()),
		make_column("vote_weight", &User::voteWeight),
		make_column("group", &User::group));
}

}