#pragma once
#include "storage/models/user.h"
#include "storage/models/movie.h"
#include <iostream>
#include <unordered_set>
namespace storage::models::user
{

	std::ostream& operator<<(std::ostream& os, const storage::models::user::User& x);
	bool operator==(const User& a, const User& b);
	bool operator!=(const User& a, const User& b);
}
namespace storage::models::movie
{
	Movie str_to_mv(const std::string& str);
	std::ostream& operator<<(std::ostream& os, const Movie& mv);
	bool operator<(const Movie& a, const Movie& b);
}