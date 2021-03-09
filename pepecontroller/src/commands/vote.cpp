#include "vote.h"

#include <boost/log/trivial.hpp>

namespace commands
{

Vote::Vote(uint32_t num) : num(num) {}

void Vote::Execute(Context* ctx)
{
	BOOST_LOG_TRIVIAL(debug) << "[Vote::Execute] " << num;
}

}
