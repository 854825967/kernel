// DllUser.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include "../DllThread/IExportFun.h"

typedef IFunctionInterface* (* GET_INTERFACE)();


int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _DEBUG
	HMODULE hModule = ::LoadLibraryA("../Bin/Debug/DllThread.dll");
#else
	HMODULE hModule = ::LoadLibraryA("../Bin/Release/DllThread.dll");
#endif

	if ( hModule )
	{
		GET_INTERFACE pFunction = (GET_INTERFACE)::GetProcAddress( hModule, "GetInterface");
		if ( pFunction )
		{
			IFunctionInterface* pInterface = (*pFunction)();

			if ( pInterface )
			{
				pInterface->StartWork();

				Sleep(100);
			}
		}

		::FreeLibrary(hModule);
	}

	return 0;
}

