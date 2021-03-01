#pragma once
#include "../column.h"

#include <sqlite_orm.h>

namespace storage::models::movieVotes
{

enum VoteType { DISLIKE, LIKE };

struct MovieVotes
{
	uint64_t id;
	uint64_t userId;
	uint8_t vote;
};

using TableType = sqlite_orm::internal::table_t<MovieVotes,
	Column<MovieVotes, decltype(MovieVotes::id)>,
	Column<MovieVotes, decltype(MovieVotes::userId)>,
	Column<MovieVotes, decltype(MovieVotes::vote)>>;

TableType MakeTable();

}