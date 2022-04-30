// DLLDSAProject.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "DLLDSAProject.h"

// Fields
Graph* graph = nullptr;
int** path = nullptr;
int currentPathIndex;
int* pathLength = new int();
const int** mazeData = nullptr;
int mazeWidth, mazeHeight = 0;

// This is an example of an exported variable
extern "C" DLLDSAPROJECT_API int nDLLDSAProject = 0;

// This is an example of an exported function.
extern "C" DLLDSAPROJECT_API int fnDLLDSAProject(void)
{
	return 0;
}

// Connor's functions
const char* teamName = "Luke and Connor";
extern "C" DLLDSAPROJECT_API char* GetTeam()
{
	return (char*)teamName;
}

extern "C" DLLDSAPROJECT_API bool SetMaze(const int** data, int width, int height)
{
	//if the data is not a nullptr and the width and height are both greater than zero, set the maze and return true
	if (data != nullptr && width > 0 && height > 0)
	{
		mazeData = data;
		mazeWidth = width;
		mazeHeight = height;

		// Create Graph object
		graph = new Graph(data, width, height, -1, -1, -1, -1); // Start and End will be nullptrs

		return true;
	}
	//if the data is a nullptr or width or height are null, negative, or zero, return false
	else
	{
		return false;
	}
}

extern "C" DLLDSAPROJECT_API int** GetMaze(int& width, int& height)
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

extern "C" DLLDSAPROJECT_API bool GetNextPosition(int& xPos, int& yPos)
{
	// If we have run the pathfinder algorithm
	if (path != nullptr) {
		//If the current position is one away from the size of the positions array (or any amount greater) then there are no more steps to take.
		//The function will in that case return false
		if (currentPathIndex + 1 >= *pathLength)
		{
			return false;
		}
		//Otherwise, increase the current position index by one, set the x and y positions to the next position in the array and return true.
		else
		{
			currentPathIndex++;
			xPos = path[currentPathIndex][0];
			yPos = path[currentPathIndex][1];
			return true;
		}
	}
	else {
		// This shouldn't happen
		return false;
	}
}

//Luke's Functions
extern "C" DLLDSAPROJECT_API bool SetStart(int xpos, int ypos)
{
	//Check if the given values are valid. If so, set the new start position and return true.
	if (xpos >= 0 && xpos < mazeWidth && ypos >= 0 && ypos < mazeHeight)
	{
		graph->SetStart(xpos, ypos);
		// Because we changed the start, we have to calculate the path again
		// If there's also an end (obviously we know there's a start)
		int temp1, temp2 = 0;
		if (graph->GetEnd(temp1, temp2)) {
			path = graph->FindPath(*pathLength);
			currentPathIndex = -1;
		}
		return true;
	}
	//Otherwise, return false.
	else
	{
		return false;
	}
}

extern "C" DLLDSAPROJECT_API bool GetStart(int& xpos, int& ypos)
{
	// If there is a start, it'll change the values, otherwise it returns false
	return graph->GetStart(xpos, ypos);
}

extern "C" DLLDSAPROJECT_API bool SetEnd(int xpos, int ypos)
{
	//Check if the given values are valid. If so, set the new end position and return true.
	if (xpos >= 0 && xpos < mazeWidth && ypos >= 0 && ypos < mazeHeight)
	{
		graph->SetEnd(xpos, ypos);
		// Because we changed the end, we have to calculate the path again
		// If there's also a start (obviously we know there's an end)
		int temp1, temp2 = 0;
		if (graph->GetStart(temp1, temp2)) {
			path = graph->FindPath(*pathLength);
			currentPathIndex = -1;
		}
		return true;
	}
	//Otherwise, return false.
	else
	{
		return false;
	}
}

extern "C" DLLDSAPROJECT_API bool GetEnd(int& xpos, int& ypos)
{
	// If there is an end, it'll change the values, otherwise it returns false
	return graph->GetEnd(xpos, ypos);
}

/// <summary>
///  this function will make the player start back at their start location and step through each part of the path to the end again.
/// </summary>
/// <returns></returns>
extern "C" DLLDSAPROJECT_API bool Restart(int xPos, int yPos)
{
	//set currentPathIndex back to -1
	currentPathIndex = -1;
	//set the given x and y positions to Start (if GetStart returns false, stop and return false
	if (!GetStart(xPos, yPos))
	{
		return false;
	}
	//call GetNextPosition until it returns false
	while (GetNextPosition(xPos, yPos)){}
	//If you made it this far return true
	return true;
}

// This is the constructor of a class that has been exported.
extern "C" CDLLDSAProject::CDLLDSAProject()
{
	return;
}

