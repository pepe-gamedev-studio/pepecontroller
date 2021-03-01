#include "peka2tv/peka2tvSIOClient.h"
#include "peka2tv/peka2tvHttpClient.h"
#include "storage.h"
#include "storage/models/user.h"
#include "commands/banConstructor.h"
#include "commands/skipConstructor.h"
#include "commands/voteConstructor.h"
#include "app.h"

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <memory>
#include <boost/log/trivial.hpp>

#include <boost/asio.hpp>

int Main(int argc, char * argv[]);

#ifdef _WIN32
#include <Windows.h>
int wmain(int argc, wchar_t * argv[])
{
	SetConsoleOutputCP(CP_UTF8);

	char** u8argv = new char*[argc];
	for (int argn = 0; argn < argc; ++argn)
	{
		int size = WideCharToMultiByte(CP_UTF8, 0, argv[argn], -1, NULL, 0, NULL, NULL);

		u8argv[argn] = new char[size];

		WideCharToMultiByte(CP_UTF8, 0, argv[argn], -1, u8argv[argn], size, NULL, NULL);
	}

	Main(argc, u8argv);
}
#else
int main(int argc, char * argv[])
{
	Main(argc, argv);
}
#endif


int Main(int argc, char * argv[])
{
	using namespace std::string_literals;

	if (argc < 2)
	{
		std::cerr << "Missing chat id" << std::endl;
		return 1;
	}

	BOOST_LOG_TRIVIAL(debug) << "[main] channel " << argv[1];

	boost::asio::io_context io;
	boost::asio::executor_work_guard<decltype(io.get_executor())> work{ io.get_executor() };

	auto storage = storage::InitStorage();
	peka2tv::Peka2tvHttpClient httpClient;
	peka2tv::Peka2tvSIOClient sioClient;

	sioClient.Connect();

	App app(sioClient.Join("stream/"s + argv[1]), &storage, &httpClient);
	
	App::CommandSet allCommands
	{
		{"skip"s, std::make_shared<commands::SkipConstructor>() },
		{"vote"s, std::make_shared<commands::VoteConstructor>() },
		{"ban"s, std::make_shared<commands::BanConstructor>() },
	};
	
	app.SetCommands(allCommands);

	io.run();
	return 0;
}