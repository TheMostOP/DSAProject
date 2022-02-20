// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the DLLDSAPROJECT_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// DLLDSAPROJECT_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DLLDSAPROJECT_EXPORTS
#define DLLDSAPROJECT_API __declspec(dllexport)
#else
#define DLLDSAPROJECT_API __declspec(dllimport)
#endif

// This class is exported from the dll
class DLLDSAPROJECT_API CDLLDSAProject {
public:
	CDLLDSAProject(void);
	// TODO: add your methods here.
};

extern DLLDSAPROJECT_API int nDLLDSAProject;

DLLDSAPROJECT_API int fnDLLDSAProject(void);
DLLDSAPROJECT_API char* GetTeam();
