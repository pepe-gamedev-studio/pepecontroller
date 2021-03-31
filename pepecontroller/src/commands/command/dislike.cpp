#include "dislike.h"
#include <boost/log/trivial.hpp>

namespace commands
{

	Dislike::Dislike()
	{
	}

	void Dislike::Execute(Context* ctx)
	{
		BOOST_LOG_TRIVIAL(debug) << "[Dislike::Execute] ";
	}

}