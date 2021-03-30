#include "like.h"
#include <boost/log/trivial.hpp>
#include "../storage.h"
namespace commands
{

	void Like::Execute(Context* ctx)
	{
		//Movie.GetId();
		//storage::models::movieVotes::MovieVotes x { 0, ctx->message->from.id, storage::models::movieVotes::LIKE};
		BOOST_LOG_TRIVIAL(debug) << "[Like::Execute] ";
	}

}