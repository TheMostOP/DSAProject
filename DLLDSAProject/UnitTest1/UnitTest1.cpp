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
			const int testData[width][height] = {
				{ 0, 1, 0, 0, 0 },
				{ 0, 1, 0, 0, 0 },
				{ 0, 1, 1, 1, 0 },
				{ 0, 1, 0, 1, 0 },
				{ 0, 1, 0, 1, 0 },
				{ 0, 0, 0, 1, 0 },
				{ 0, 0, 1, 1, 0 },
				{ 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0 }
			};

			const int* testDataPtr = *testData;
			SetMaze(&testDataPtr, width, height);

			int* retWidth = new int();
			int* retHeight = new int();
			int* retDataPtr = *(GetMaze(*retWidth, *retHeight));

			Assert::AreEqual(width, *retWidth);
			Assert::AreEqual(height, *retHeight);
			Assert::AreEqual(testData[0][2], (&retDataPtr)[0][2]);
		}

		TEST_METHOD(TestNextPosition)
		{
			const int width = 10;
			const int height = 5;

			const int** data = new const int* [width];
			data[0] = new int[] { 0, 1, 0, 0, 0 };
			data[1] = new int[] { 0, 1, 0, 0, 0 };
			data[2] = new int[] { 0, 1, 1, 1, 0 };
			data[3] = new int[] { 0, 1, 0, 1, 0 };
			data[4] = new int[] { 0, 1, 0, 1, 0 };
			data[5] = new int[] { 0, 0, 0, 1, 0 };
			data[6] = new int[] { 0, 0, 1, 1, 0 };
			data[7] = new int[] { 0, 0, 0, 0, 0 };
			data[8] = new int[] { 0, 0, 0, 0, 0 };
			data[9] = new int[] { 0, 0, 0, 0, 0 };
			
			int xPos, yPos;
			SetMaze(data, width, height);
			SetStart(1, 0);
			SetEnd(1, 2);
			GetStart(xPos, yPos);
			
			GetNextPosition(xPos, yPos);
			Assert::AreEqual(xPos, 0);
			Assert::AreEqual(yPos, 2);
		}

		TEST_METHOD(TestEndPosFuncs)
		{
			int endPos[] = { -1,-1 };
			int endPosPtr = *endPos;
			int* xPos = new int(4);
			int* yPos = new int(1);
			SetEnd(*xPos, *yPos);

			int* retXPos = new int();
			int* retYPos = new int();
			GetEnd(*retXPos, *retYPos);

			Assert::AreNotEqual(*xPos, -1);
			Assert::AreNotEqual(*yPos, -1);
			Assert::AreEqual(*xPos, *retXPos);
			Assert::AreEqual(*yPos, *retYPos);
		}
	};
}
