#include "skip.h"
#include <boost/log/trivial.hpp>

namespace commands
{

Skip::Skip()
{
}

void Skip::Execute(Context* ctx)
{
	Inst.Stop();
	Inst.callOverlay();
	BOOST_LOG_TRIVIAL(debug) << "[Skip::Execute] ";
}

}
