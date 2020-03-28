#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <exception>
#include <LogCatLog.h>
#include "..\ConsoleApplication1\ConsoleApplication1.h"

#pragma comment(lib, "bhriguutilscpp.lib")

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

BEGIN_TEST_MODULE_ATTRIBUTE()
TEST_MODULE_ATTRIBUTE(L"Date", L"2010/6/12")
END_TEST_MODULE_ATTRIBUTE()

TEST_MODULE_INITIALIZE(ModuleInitialize)
{
	Logger::WriteMessage("In Module Initialize");
}

TEST_MODULE_CLEANUP(ModuleCleanup)
{
	Logger::WriteMessage("In Module Cleanup");
}


namespace bhrigu_text_test
{
	TEST_CLASS(bhrigu_text_test_class)
	{
	public:

		TEST_METHOD(TestMethod1)
		{

			auto func = [] { mai(); };

			Assert::ExpectException<std::exception>(func);
			

		}
	};
}
