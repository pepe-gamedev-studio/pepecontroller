#include "peka2tv/peka2tvSIOClient.h"
#include "peka2tv/peka2tvHttpClient.h"
#include "storage.h"
#include "app.h"
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <memory>
#include <boost/log/trivial.hpp>
#include <boost/asio.hpp>
#include "phase/votePhase.h"
#include "phase/moviePhase.h"

int Main(int argc, char* argv[]);

#ifdef _WIN32
#include <Windows.h>

int wmain(int argc, wchar_t* argv[])
{
	SetConsoleOutputCP(CP_UTF8);

	auto u8argv = new char*[argc];
	for (int argn = 0; argn < argc; ++argn)
	{
		int size = WideCharToMultiByte(CP_UTF8, 0, argv[argn], -1, nullptr, 0, nullptr, nullptr);

		u8argv[argn] = new char[size];

		WideCharToMultiByte(CP_UTF8, 0, argv[argn], -1, u8argv[argn], size, nullptr, nullptr);
	}

	Main(argc, u8argv);
}
#else
int main(int argc, char * argv[])
{
	Main(argc, argv);
}
#endif


int Main(int argc, char* argv[])
{
	using namespace std::string_literals;

	if (argc < 2)
	{
		std::cerr << "Missing chat id" << std::endl;
		return 1;
	}

	BOOST_LOG_TRIVIAL(debug) << "[main] channel " << argv[1];

	boost::asio::io_context ioc;
	boost::asio::executor_work_guard<decltype(ioc.get_executor())> work{
		ioc.get_executor()
	};

	auto storage = storage::InitStorage();
	peka2tv::Peka2tvHttpClient httpClient(boost::asio::make_strand(ioc), "https://sc2tv.ru");
	/*std::make_shared<peka2tv::Peka2tvHttpClient>(
	    boost::asio::make_strand(ioc));*/
	peka2tv::Peka2tvSIOClient sioClient;
	pepebackend::Instance inst("./movies");
	sioClient.Connect();

	App app(sioClient.Join("stream/"s + argv[1]), &storage, &inst, &httpClient);

	app.SetPhase<phase::MoviePhase>();

	ioc.run();
	return 0;
}
