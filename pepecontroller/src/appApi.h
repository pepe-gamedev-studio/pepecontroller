#pragma once
#include "userCache.h"
#include "storage.h"
#include "peka2tv/peka2tvHttpClient.h"
#include "helper.h"

#include <boost/log/trivial.hpp>

#include <optional>

class AppApi
{
	using User = storage::models::user::User;
public:
	explicit AppApi(UserCache* userCache, storage::Storage* storage, peka2tv::Peka2tvHttpClient* httpClient);

	template<typename UserInfoMember, typename T>
	std::optional<User> FindUser(UserInfoMember m, T val)
	{
		using namespace sqlite_orm;
		using UserInfo = peka2tv::Peka2tvHttpClient::UserInfo;
		using UserGroup = storage::models::user::UserGroup;

		if (auto cached = userCache->Get(val))
		{
			BOOST_LOG_TRIVIAL(debug) << "[AppApi::FindUser] cache " << *cached;

			return *cached;
		}

		auto stored = storage->get_all<User>(where(c(m) == val));
		if (!stored.empty())
		{
			User& u = stored.front();
			userCache->Insert(u);

			BOOST_LOG_TRIVIAL(debug) << "[AppApi::FindUser] storage " << u;

			return u;
		}

		if (auto fetched = httpClient->FetchUserInfo(m, val))
		{
			User u{ fetched->id, fetched->name, 1, UserGroup::Viewer };
			storage->replace(u);
			userCache->Insert(u);

			BOOST_LOG_TRIVIAL(debug) << "[AppApi::FindUser] http " << u;

			return u;
		}

		BOOST_LOG_TRIVIAL(debug) << "[AppApi::FindUser] not found " << val;

		return {};
	}
	void UpdateUser(const User& u)
	{
		BOOST_LOG_TRIVIAL(debug) << "[AppApi::UpdateUser] " << u;

		using namespace sqlite_orm;

		if (auto cached = userCache->Get(u.id))
		{
			*cached = u;
		}
		else
		{
			userCache->Insert(u);
		}

		storage->replace(u);
	}
private:
	UserCache* userCache;
	storage::Storage* storage;
	peka2tv::Peka2tvHttpClient* httpClient;
};

