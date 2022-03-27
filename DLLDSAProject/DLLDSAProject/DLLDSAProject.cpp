// DLLDSAProject.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "DLLDSAProject.h"


// This is an example of an exported variable
DLLDSAPROJECT_API int nDLLDSAProject = 0;

// This is an example of an exported function.
DLLDSAPROJECT_API int fnDLLDSAProject(void)
{
	return 0;
}

// Connor's functions
const char* teamName = "Luke and Connor";
DLLDSAPROJECT_API char* GetTeam()
{
	return (char*)teamName;
}

const int** mazeData = nullptr;
int mazeWidth, mazeHeight = 0;
DLLDSAPROJECT_API bool SetMaze(const int** data, int width, int height)
{
	//if the data is not a nullptr and the width and height are both greater than zero, set the maze and return true
	if (data != nullptr && width > 0 && height > 0)
	{
		mazeData = data;
		mazeWidth = width;
		mazeHeight = height;
		return true;
	}
	//if the data is a nullptr or width or height are null, negative, or zero, return false
	else
	{
		return false;
	}
}

DLLDSAPROJECT_API int** GetMaze(int& width, int& height)
{
	//If the mazeData hasn't been set and is still nullptr, return nullptr
	if (mazeData == nullptr)
	{
		return nullptr;
	}
	else
	{
		width = mazeWidth;
		height = mazeHeight;
		return (int**)mazeData;
	}
}

int positions[10][2] =
{
	{ 1, 5 },
	{ 3, 2 },
	{ 7, 3 },
	{ 6, 9 },
	{ 2, 5 },
	{ 4, 1 },
	{ 3, 3 },
	{ 7, 8 },
	{ 8, 4 },
	{ 1, 6 }
};
int currentPosIndex = -1;
DLLDSAPROJECT_API bool GetNextPosition(int& xPos, int& yPos)
{
	//If the current position is one away from the size of the positions array (or any amount greater) then there are no more steps to take.
	//The function will in that case return false
	if (currentPosIndex + 1 >= sizeof(positions))
	{
		return false;
	}
	//Otherwise, increase the current position index by one, set the x and y positions to the next position in the array and return true.
	else
	{
		currentPosIndex++;
		xPos = positions[currentPosIndex][0];
		yPos = positions[currentPosIndex][1];
		return true;
	}

}

//Luke's Functions
int startPos[] = { -1,-1 };
DLLDSAPROJECT_API bool SetStart(int xpos, int ypos)
{
	//Check if the given values are valid. If so, set the new start position and return true.
	if (xpos >= 0 && ypos >= 0)
	{
		startPos[0] = xpos;
		startPos[1] = ypos;
		return true;
	}
	//Otherwise, return false.
	else
	{
		return false;
	}
}

DLLDSAPROJECT_API void GetStart(int& xpos, int& ypos)
{
	xpos = startPos[0];
	ypos = startPos[1];
}

int endPos[] = { -1,-1 };
DLLDSAPROJECT_API void SetEnd(int xpos, int ypos)
{
	endPos[0] = xpos;
	endPos[1] = ypos;
}

DLLDSAPROJECT_API void GetEnd(int& xpos, int& ypos)
{
	xpos = endPos[0];
	ypos = endPos[1];
}

// This is the constructor of a class that has been exported.
CDLLDSAProject::CDLLDSAProject()
{
	return;
}

