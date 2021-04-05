#include "pch.h"
#include "CppUnitTest.h"
#include <filesystem>
#include <pepebackend.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace pepetests
{
	TEST_CLASS(pepetests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::filesystem::path p(L".");
			pepebackend::Instance inst(p);

		}
	};
}
