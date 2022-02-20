<<<<<<< Updated upstream
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
=======
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


// Start of Connor's functions
DLLDSAPROJECT_API const char* names = "Luke and Connor";
DLLDSAPROJECT_API char* GetTeam()
{
    return (char*)names;
}

DLLDSAPROJECT_API const int** mazeData = nullptr;
DLLDSAPROJECT_API int mazeWidth = 0;
DLLDSAPROJECT_API int mazeHeight = 0;

DLLDSAPROJECT_API void SetMaze(const int** data, int width, int height)
{
    mazeData = data;
    mazeWidth = width;
    mazeHeight = height;
}
>>>>>>> Stashed changes
