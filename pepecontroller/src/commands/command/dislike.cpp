#include "dislike.h"
#include <boost/log/trivial.hpp>

namespace commands
{
	Dislike::Dislike(const int64_t movieID) : movieID(movieID)
	{
	}
	Dislike::Dislike()
	{
	}

	void Dislike::Execute(Context* ctx)
	{
		using namespace storage::models::movieVotes;
		MovieVotes x;

		if (movieID)
			x = { *movieID,  ctx->message->from.id, DISLIKE };
		else
		{
			movieID = ctx->api->GetCurrentMovieId();
			if (movieID == -1)
			{
				return;
			}
			x = { *movieID,  ctx->message->from.id, DISLIKE };
		}
		if(ctx->api->UpdateVotes(x))
			BOOST_LOG_TRIVIAL(debug) << "[Dislike::Execute] " << *movieID << " Disliked by " << ctx->message->from.name;
	}

}