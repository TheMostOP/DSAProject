// DLLDSAProject.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "DLLDSAProject.h"


// This is an example of an exported variable
DLLDSAPROJECT_API int nDLLDSAProject=0;

// This is an example of an exported function.
DLLDSAPROJECT_API int fnDLLDSAProject(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CDLLDSAProject::CDLLDSAProject()
{
    return;
}

// Connor's functions
const char* teamName = "Luke and Connor";
DLLDSAPROJECT_API char* GetTeam()
{
    return (char*)teamName;
}

const int** mazeData = nullptr;
int mazeWidth, mazeHeight = 0;
DLLDSAPROJECT_API void SetMaze(int** data, int width, int height)
{
    mazeData = data;
    mazeWidth = width;
    mazeHeight = height;
}