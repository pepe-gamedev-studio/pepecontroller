#include "vote.h"

#include <boost/log/trivial.hpp>

namespace commands
{

//Vote::Vote(uint32_t num) : num(num) {}

Vote::Vote(VotePhase* ph, uint8_t num) : phase(ph), num(num) {}

//const size_t counter_size = 10;
//std::vector<size_t> counter(counter_size, 0);

//void Vote::resetCache()
//{
//	this->voteCache.erase(this->voteCache.begin(), this->voteCache.end());
//}

void Vote::Execute(Context* ctx)
{
	if(this->phase->Vote(ctx->message->from.id, num))
		BOOST_LOG_TRIVIAL(debug) << "[Vote::Execute] " << num;
	else
		BOOST_LOG_TRIVIAL(debug) << "[Vote::Execute] " << "wrong";
}

}
