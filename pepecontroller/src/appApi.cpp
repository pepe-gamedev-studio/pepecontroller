#include "appApi.h"

AppApi::AppApi(UserCache* userCache, storage::Storage* storage, peka2tv::Peka2tvHttpClient* httpClient, pepebackend::Instance* inst) :
	userCache(userCache),
	storage(storage),
	httpClient(httpClient),
	inst(inst)
	{
		UpdateMovies();
	}
	
