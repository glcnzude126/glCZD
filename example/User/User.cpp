// User.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MatureApproach.h"

#ifdef _x64
#ifdef _DEBUG
#pragma comment(lib, "MatureApproach.lib")
#else
#pragma comment(lib, "MatureApproach.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "../debug/MatureApproach.lib")
#else
#pragma comment(lib, "../release/MatureApproach.lib")
#endif
#endif

/*
// 动态库单实例调用
int _tmain(int argc, _TCHAR* argv[])
{
	IExport* pExport = CreateExportObj();
	pExport->Hi();
	pExport->Test();
	DestroyExportObj(pExport);
	system("pause");
	return 0;
}
*/

// 动态库多实例调用
int _tmain(int argc, _TCHAR* argv[])
{
	IExport* pExport[255];

	for (int i = 0; i < 255; i++)
	{
		pExport[i]  = CreateExportObj();
		pExport[i]->Hi();
		pExport[i]->Test();

		//DestroyExportObj(pExport[i]);
	}

	for (int i = 0; i < 255; i++)
	{
		DestroyExportObj(pExport[i]);
	}

	system("pause");
	return 0;
}