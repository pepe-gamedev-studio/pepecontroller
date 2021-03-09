#include "appApi.h"

AppApi::AppApi(UserCache* userCache, storage::Storage* storage, peka2tv::Peka2tvHttpClient* httpClient) :
	userCache(userCache),
	storage(storage),
	httpClient(httpClient) {}
