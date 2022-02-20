#include "pch.h"
#include "CppUnitTest.h"
#include "DLLDSAProject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestTeamNames)
		{
			char* test = "Just Connor";
			char* ret = GetTeam();
			Assert::AreNotEqual(test, ret);
		}
	};
}
