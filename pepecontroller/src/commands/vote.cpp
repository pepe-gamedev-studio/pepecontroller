#include "vote.h"

#include <boost/log/trivial.hpp>

namespace commands
{

Vote::Vote(uint32_t num) : num(num) {}

const size_t counter_size = 10;
std::vector<size_t> counter(counter_size, 0);

void Vote::resetCache()
{
	this->voteCache.erase(this->voteCache.begin(), this->voteCache.end());
}

void Vote::Execute(Context* ctx)
{
	auto it = find(this->voteCache.begin(), this->voteCache.end(), ctx->message->from.id);
	if ((num < counter_size) && (it == this->voteCache.end()))
	{
		++counter[num];
		voteCache.insert(ctx->message->from.id);
		BOOST_LOG_TRIVIAL(debug) << "[Vote::Execute] " << num;
	}
	else 
	{
		BOOST_LOG_TRIVIAL(debug) << "[Vote::Execute] " << "wrong";
	}
}

}
