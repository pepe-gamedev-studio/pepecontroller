#pragma once
#include <nlohmann/json.hpp>

#include <string>
#include <exception>
#include <optional>
#include <type_traits>

namespace peka2tv
{

template<typename T, typename U> constexpr size_t offsetOf(U T::*member)
{
	return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

template<typename T>
struct MemberType {};

template<typename T, typename M>
struct MemberType<T M::*> { using type = T; };

class Peka2tvHttpClient
{
public:
	struct UserInfo
	{
		uint64_t id;
		std::string name;
		std::string slug;
	};
public:
	Peka2tvHttpClient(std::string entry = "https://sc2tv.ru");
	template<typename UserInfoMember, typename T>
	std::optional<UserInfo> FetchUserInfo(UserInfoMember m, T val)
	{
		static_assert(std::is_convertible_v<T, MemberType<UserInfoMember>::type>, "Type mismatch between property and provided value");

		const std::string resource = "/api/user";
		nlohmann::json q;
		if (offsetOf(m) == offsetOf(&UserInfo::id))
			q["id"] = val;
		else if (offsetOf(m) == offsetOf(&UserInfo::name))
			q["name"] = val;
		else if (offsetOf(m) == offsetOf(&UserInfo::slug))
			q["slug"] = val;
		else
			throw std::runtime_error("Invalid query");

		auto r = nlohmann::json::parse(Call(resource, q.dump()));

		if (r.find("id") == r.end())
			return {};

		return UserInfo{ r["id"].get<uint64_t>(), r["name"].get<std::string>(), r["slug"].get<std::string>() };
	}
protected:
	std::string Call(std::string method, std::string data);
private:
	std::string host;
	std::string port;
};

}
