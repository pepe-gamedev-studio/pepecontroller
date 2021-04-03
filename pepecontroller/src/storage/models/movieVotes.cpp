#include "movieVotes.h"

namespace storage::models::movieVotes
{

TableType MakeTable()
{
	using namespace sqlite_orm;
	using namespace storage::models;

	return make_table("movieVotes",
		make_column("id", &MovieVotes::movieId),
		make_column("userId", &MovieVotes::userId),
		make_column("vote", &MovieVotes::vote),
		primary_key(&MovieVotes::movieId, &MovieVotes::userId),
		foreign_key(&MovieVotes::movieId).references(&movie::Movie::id));
}

}