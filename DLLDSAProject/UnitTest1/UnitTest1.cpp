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

		TEST_METHOD(TestMazeDataFuncs)
		{
			const int width = 10;
			const int height = 5;
			int testData[width][height] = {
				{ 11, 12, 13, 14, 15 },
				{ 21, 22, 23, 24, 25 },
				{ 31, 32, 33, 34, 35 },
				{ 41, 42, 43, 44, 45 },
				{ 51, 52, 53, 54, 55 },
				{ 61, 62, 63, 64, 65 },
				{ 71, 72, 73, 74, 75 },
				{ 81, 82, 83, 84, 85 },
				{ 91, 92, 93, 94, 95 },
				{ 01, 02, 03, 04, 05 }
			};
			int* testDataPtr = *testData;
			SetMaze(&testDataPtr, width, height);

			int* retWidth = new int();
			int* retHeight = new int();
			int* retDataPtr = *(GetMaze(*retWidth, *retHeight));

			Assert::AreEqual(width, *retWidth);
			Assert::AreEqual(height, *retHeight);
			Assert::AreEqual(testData[0][2], (&retDataPtr)[0][2]);
		}
	};
}
