#pragma once
#include "../column.h"

#include <sqlite_orm/sqlite_orm.h>

#include <string>

namespace storage::models::movie
{

struct Movie
{
	int64_t id;
	std::string title;
	uint32_t length;
	uint32_t year;
	std::string filename;
};

using TableType = sqlite_orm::internal::table_t<Movie,
	Column<Movie, decltype(Movie::id), sqlite_orm::constraints::primary_key_t<>, sqlite_orm::constraints::autoincrement_t>,
	Column<Movie, decltype(Movie::title), sqlite_orm::constraints::unique_t<>>,
	Column<Movie, decltype(Movie::length)>,
	Column<Movie, decltype(Movie::year)>,
	Column<Movie, decltype(Movie::filename)>
>;

TableType MakeTable();

}