#include "pch.h"
#include "CppUnitTest.h"
#include "DLLDSAProject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestTeamName)
		{
			char* test = "not the team name";
			char* ret = GetTeam();
			Assert::AreNotEqual(test, ret);
		}
	};
}
