#pragma once
#include "../column.h"
#include "movie.h"
#include <sqlite_orm/sqlite_orm.h>

namespace storage::models::movieVotes
{

enum VoteType { DISLIKE, LIKE };

struct MovieVotes
{
	int64_t movieId;
	int64_t userId;
	uint8_t vote;
};
using namespace storage::models;

using TableType = sqlite_orm::internal::table_t<MovieVotes,
	Column<MovieVotes, decltype(MovieVotes::movieId)>,
	Column<MovieVotes, decltype(MovieVotes::userId)>,
	Column<MovieVotes, decltype(MovieVotes::vote)>,
	sqlite_orm::constraints::primary_key_t<decltype(MovieVotes::movieId) MovieVotes::*, decltype(MovieVotes::userId) MovieVotes::*>,
	sqlite_orm::constraints::foreign_key_t<std::tuple<decltype(MovieVotes::movieId) MovieVotes::*>,
	std::tuple<decltype(movie::Movie::id) movie::Movie::*>>>;

TableType MakeTable();

}