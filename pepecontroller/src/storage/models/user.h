#pragma once
#include "../column.h"

#include <sqlite_orm/sqlite_orm.h>

#include <string>

namespace storage::models::user
{

enum UserGroup : uint8_t { Ignored, Viewer, Moderator, Admin };
struct User
{
	uint64_t id;
	std::string name;
	int64_t voteWeight;
	uint8_t group;
};

using TableType = sqlite_orm::internal::table_t<User,
	Column<User, decltype(User::id), sqlite_orm::constraints::primary_key_t<>>,
	Column<User, decltype(User::name)>,
	Column<User, decltype(User::voteWeight)>,
	Column<User, decltype(User::group)>>;

TableType MakeTable();

}