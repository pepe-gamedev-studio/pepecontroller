#pragma once
#include "userCache.h"
#include "storage.h"
#include "peka2tv/peka2tvHttpClient.h"
#include "helper.h"
#include <pepebackend.h>
#include <boost/log/trivial.hpp>
#include <optional>

class AppApi
{
	using User = storage::models::user::User;
	using Movie = storage::models::movie::Movie;
	using MovieVotes = storage::models::movieVotes::MovieVotes;
	using UserInfo = peka2tv::Peka2tvHttpClient::UserInfo;
public:
	explicit AppApi(UserCache* userCache, storage::Storage* storage, peka2tv::Peka2tvHttpClient* httpClient, pepebackend::Instance* inst);

	template <typename UserInfoMember, typename T>
	void FindUser(UserInfoMember m, T val, std::function<void(std::optional<User>)> callback)
	{
		using namespace sqlite_orm;
		using UserGroup = storage::models::user::UserGroup;

		if (auto cached = userCache->Get(val))
		{
			BOOST_LOG_TRIVIAL(debug)
                        << "[AppApi::FindUser] cache " << *cached;

			callback(*cached);
			return;
		}

		auto stored = storage->get_all<User>(where(c(m) == val));
		if (!stored.empty())
		{
			User& u = stored.front();
			userCache->Insert(u);

			BOOST_LOG_TRIVIAL(debug)
                        << "[AppApi::FindUser] storage " << u;

			callback(u);
			return;
		}

		httpClient->FetchUserInfo(
			m, val, [&](std::optional<UserInfo> info)
			{
				if (info)
				{
					User u{
						info->id, info->name, 1,
						UserGroup::Viewer
					};
					storage->replace(u);
					userCache->Insert(u);

					BOOST_LOG_TRIVIAL(debug)
                                << "[AppApi::FindUser] http " << u;

					callback(u);
				}
				else
				{
					BOOST_LOG_TRIVIAL(debug)
                                << "[AppApi::FindUser] not found " << val;
					callback({});
				}
			});
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

	void UpdateMovies()
	{
		using namespace storage::models::movie;
		auto strMovieSet = inst->GetPlaylist();
		for (auto& it : strMovieSet)
		{
			try
			{
				storage->insert(str_to_mv(it.string()));
			}
			catch (const std::exception&) {}
		}
		BOOST_LOG_TRIVIAL(debug) << "[AppApi::UpdateMovies] ";
	}
	
	int64_t GetCurrentMovieId() 
	{
		using namespace storage::models::movie;

		auto m = storage->get_pointer<Movie>(this->inst->PlayingFilename().string());
		if (m)
		{
			return m->id;
		}
		else
		{
			BOOST_LOG_TRIVIAL(debug) << "Cannot get current movie ID now" << std::endl;
			return -1;
		}
	}
	bool UpdateVotes(const MovieVotes& mv)
	{
		using namespace storage::models::movieVotes;
		try
		{
			storage->replace(mv);
			BOOST_LOG_TRIVIAL(debug) << "[AppApi::UpdateVotes] " << mv.movieId;
			return true;
		}
		catch (const std::exception&)
		{
			BOOST_LOG_TRIVIAL(debug) << "[AppApi::UpdateVotes] " << mv.movieId << " does not exist ";
			return false;
		}
	}

private:
	UserCache* userCache;
	storage::Storage* storage;
	peka2tv::Peka2tvHttpClient* httpClient;
	pepebackend::Instance* inst;
	};

