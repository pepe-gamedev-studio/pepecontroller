#include "unvote.h"
#include <boost/log/trivial.hpp>

namespace commands
{

Unvote::Unvote(phase::VotePhase* ph) : phase(ph) {}

void Unvote::Execute(Context* ctx)
{
	if (this->phase->Unvote(ctx->message->from.id))
		BOOST_LOG_TRIVIAL(debug) << "[Vote::Execute] " << "Unvoted";
	else
		BOOST_LOG_TRIVIAL(debug) << "[Vote::Execute] " << "wrong";
}

}
