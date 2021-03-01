#pragma once
#include "models/user.h"
#include "models/movie.h"
#include "models/movieVotes.h"

#include <sqlite_orm.h>

#include <string>
#include <optional>

namespace storage
{

using Storage = sqlite_orm::internal::storage_t<
	models::user::TableType,
	models::movie::TableType,
	models::movieVotes::TableType>;

Storage InitStorage(std::string dbname = "pepe.sqlite3");

}