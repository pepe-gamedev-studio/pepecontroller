#include "sqliteStorage.h"

namespace storage
{

Storage InitStorage(std::string dbname)
{
	using namespace sqlite_orm;

	auto storage = make_storage(dbname,
		models::user::MakeTable(),
		models::movie::MakeTable(),
		models::movieVotes::MakeTable());

	storage.sync_schema();

	return storage;
}

}
