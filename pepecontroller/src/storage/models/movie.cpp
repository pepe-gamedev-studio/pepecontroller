#include "movie.h"

namespace storage::models::movie
{

TableType MakeTable()
{
	using namespace sqlite_orm;

	return make_table("movie",
		make_column("id", &Movie::id, primary_key(), autoincrement()),
		make_column("title", &Movie::title, unique()),
		make_column("length", &Movie::length),
		make_column("year", &Movie::year),
		make_column("filename", &Movie::filename)
	);
}

}