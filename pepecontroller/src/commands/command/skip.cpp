#include "../command/skip.h"
#include <boost/log/trivial.hpp>

namespace commands
{

Skip::Skip(phase::SkipPhase* ph) : phase(ph)
{
}

void Skip::Execute(Context* ctx)
{
	//Inst.Stop();
	//Inst.callOverlay();
	if(this->phase->Skip(ctx->message->from.id))
		BOOST_LOG_TRIVIAL(debug) << "[Skip::Execute] ";
	else
		BOOST_LOG_TRIVIAL(debug) << "[Skip::Execute] " << "wrong";
}

}
