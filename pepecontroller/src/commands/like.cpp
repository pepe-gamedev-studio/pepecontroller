#include "like.h"
#include <boost/log/trivial.hpp>

namespace commands
{

	Like::Like()
	{
	}

	void Like::Execute(Context* ctx)
	{
		BOOST_LOG_TRIVIAL(debug) << "[Like::Execute] ";
	}

}