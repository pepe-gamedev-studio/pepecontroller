#include "helper.h"
#include "commands/command.h"
#include "storage.h"
#include <pepebackend.h>
namespace storage::models::user
{

	static const std::vector<std::string> groups{ "Ignored", "Viewer", "Moderator", "Admin" };

	std::ostream& operator<<(std::ostream& os, const storage::models::user::User& x)
	{
		return os << x.id << " " << x.platform << " " << x.name << " " << x.voteWeight << " " << groups[x.group];
	}
	bool operator==(const User& a, const User& b)
	{
		return (a.id == b.id) && (a.platform == b.platform) && (a.name == b.name) && (a.group == b.group) && (a.voteWeight == b.voteWeight);
	}
	bool operator!=(const User& a, const User& b)
	{
		return !(a == b);
	}
}

namespace storage::models::movie
{
	std::ostream& operator<<(std::ostream& os, const Movie& mv)
	{
		return os << mv.id << " " << mv.title << " " << mv.year << " " << mv.length;
	}
	bool operator<(const Movie& a, const Movie& b)
	{
		return a.title < b.title;
	}

	storage::models::movie::Movie str_to_mv(const std::string& str)
	{
		auto found = str.find("[");
		if (found < str.length())
		{
			auto x = [](std::string s) {
				auto rb = s.find_last_of("[") + 1;
				auto lb = s.find_last_of("]");
				return std::stoul(s.substr(rb, lb - rb)); };

			auto y = [](std::string s) {
				auto rb = s.find_last_of("[");
				auto lb = s.find_last_of("]");
				return s.substr(0, rb); };

			return { -1, y(str), 0, x(str), str };
		}
		else
		{
			auto y = [](std::string s)
			{
				auto ss = s.find_last_of(".");
				return s.substr(0, ss);
			};
			return { -1, y(str), 0, 0, str };
		}
	}
}
