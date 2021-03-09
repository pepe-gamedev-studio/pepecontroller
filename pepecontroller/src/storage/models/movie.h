#pragma once
#include "../column.h"

#include <sqlite_orm.h>

#include <string>

namespace storage::models::movie
{

struct Movie
{
	uint64_t id;
	std::string title;
};

using TableType = sqlite_orm::internal::table_t<Movie,
	Column<Movie, decltype(Movie::id), sqlite_orm::constraints::primary_key_t<>>,
	Column<Movie, decltype(Movie::title)>>;

TableType MakeTable();

}