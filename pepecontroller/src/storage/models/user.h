#pragma once
#include "../column.h"

#include <sqlite_orm/sqlite_orm.h>

#include <string>

namespace storage::models::user
{

enum UserGroup : uint8_t { Ignored, Viewer, Moderator, Admin };
enum Pltaform : uint8_t { Twitch, Sc2tv, Goodgame };
struct User
{
	int64_t id;
	uint8_t platform;
	std::string name;
	int64_t voteWeight;
	uint8_t group;
};

using TableType = sqlite_orm::internal::table_t<User,
	Column<User, decltype(User::id)>,
	Column<User, decltype(User::platform)>,
	Column<User, decltype(User::name), sqlite_orm::constraints::collate_t>,
	Column<User, decltype(User::voteWeight)>,
	Column<User, decltype(User::group)>,
	sqlite_orm::constraints::primary_key_t<decltype(User::id) User::*, decltype(User::platform) User::*>>;

TableType MakeTable();

}