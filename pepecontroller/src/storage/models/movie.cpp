#include "movie.h"

namespace storage::models::movie
{

TableType MakeTable()
{
	using namespace sqlite_orm;

	return make_table("movie",
		make_column("id", &Movie::id, primary_key()),
		make_column("title", &Movie::title));
}

}