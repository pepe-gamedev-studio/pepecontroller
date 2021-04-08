#include "like.h"
#include <boost/log/trivial.hpp>
#include "../../storage.h"
namespace commands
{
	Like::Like(const int64_t movieID) : movieID(movieID)
	{
	}
	Like::Like()
	{
	}
	void Like::Execute(Context* ctx)
	{
		
		using namespace storage::models::movieVotes;
		MovieVotes x;

		if (movieID)
			x = { *movieID,  ctx->message->from.id, LIKE };
		else
		{
			movieID = ctx->api->GetCurrentMovieId();
			if (movieID == -1)
			{
				return;
			}	
			x = { *movieID,  ctx->message->from.id, LIKE };
		}
		if (ctx->api->UpdateVotes(x))
			BOOST_LOG_TRIVIAL(debug) << "[Like::Execute] " << *movieID << " Liked by " << ctx->message->from.name;
	}

}