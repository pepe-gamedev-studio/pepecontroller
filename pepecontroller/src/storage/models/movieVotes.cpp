#include "movieVotes.h"

namespace storage::models::movieVotes
{

TableType MakeTable()
{
	using namespace sqlite_orm;

	return make_table("movieVotes",
		make_column("id", &MovieVotes::id),
		make_column("userId", &MovieVotes::userId),
		make_column("vote", &MovieVotes::vote));
}

}