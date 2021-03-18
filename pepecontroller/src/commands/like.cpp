#include "like.h"
#include <boost/log/trivial.hpp>
#include "../storage.h"
namespace commands
{

	void Like::Execute(Context* ctx)
	{
		//Movie.GetId();
		//storage::models::movieVotes::MovieVotes x { 0, ctx->message->from.id, storage::models::movieVotes::LIKE};
		//auto inserted = ctx->storage->insert(x);
		BOOST_LOG_TRIVIAL(debug) << "[Like::Execute] ";
	}

}