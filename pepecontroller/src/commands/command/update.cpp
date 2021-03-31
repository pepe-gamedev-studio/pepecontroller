#include "update.h"
#include "../../storage/SqliteStorage.h"
#include "../../peka2tv/peka2tvHttpClient.h"
#include <boost/log/trivial.hpp>
namespace commands 
{
	Update::Update(const std::string& arg) : arg(arg) {}
	void Update::Execute(Context* ctx)
	{
		if (arg == "movies")
		{
			ctx->api->UpdateMovies();
		}
	}
}