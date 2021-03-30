#include "appApi.h"

AppApi::AppApi(UserCache* userCache, storage::Storage* storage, peka2tv::Peka2tvHttpClient* httpClient, backend::Instance* inst) :
	userCache(userCache),
	storage(storage),
	httpClient(httpClient),
	inst(inst)
	{
		InitMovies();
	}
	
