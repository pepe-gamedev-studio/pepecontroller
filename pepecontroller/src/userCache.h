#pragma once
#include "storage/models/user.h"

#include <list>
#include <memory>
#include <string>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>

class UserCache
{
public:
	using User = storage::models::user::User;
	using UserPtr = std::shared_ptr<User>;
	using LRU = std::list<std::shared_ptr<User>>;
	struct UserInfoIndex
	{
		std::shared_ptr<User> data;
		mutable LRU::iterator it;

		uint64_t Id() const { return data->id; }
		std::string Name() const { return data->name; }
	};
public:
	explicit UserCache(size_t capacity);
	void Insert(const User& val);
	UserPtr Get(uint64_t id);
	UserPtr Get(std::string name);
private:
	size_t capacity;

	boost::multi_index_container <
		UserInfoIndex,
		boost::multi_index::indexed_by<
		boost::multi_index::hashed_unique<boost::multi_index::const_mem_fun<UserInfoIndex, uint64_t, &UserInfoIndex::Id>>,
		boost::multi_index::hashed_unique<boost::multi_index::const_mem_fun<UserInfoIndex, std::string, &UserInfoIndex::Name>>>> index;

	LRU lru;
};
