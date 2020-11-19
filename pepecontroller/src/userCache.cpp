#include "UserCache.h"
#include "helper.h"

#include <boost/log/trivial.hpp>

UserCache::UserCache(size_t capacity) : capacity(capacity) {}

void UserCache::Insert(const UserCache::User& val)
{
	if (Get(val.id))
		return;

	if (lru.size() >= capacity)
	{
		auto lr = index.get<0>().find(lru.front()->id);
		assert(lr != index.end());

		index.erase(lr);
		lru.erase(lru.begin());
	}

	lru.push_back(std::make_shared<User>(val));

	index.insert({ lru.back(), --lru.end() });

	BOOST_LOG_TRIVIAL(debug) << "[UserCache::Insert] " << val;
}

UserCache::UserPtr UserCache::Get(uint64_t id)
{
	decltype(index)::nth_index<0>::type::iterator found = index.get<0>().find(id);

	if (found == index.end())
		return {};

	if (--lru.end() != found->it)
	{
		lru.erase(found->it);
		lru.push_back(found->data);
		found->it = --lru.end();
	}

	return found->data;
}

UserCache::UserPtr UserCache::Get(std::string name)
{
	auto found = index.get<1>().find(name);

	if (found == index.get<1>().end())
		return {};

	if (--lru.end() != found->it)
	{
		lru.erase(found->it);
		lru.push_back(found->data);
		found->it = --lru.end();
	}
	
	return found->data;
}
