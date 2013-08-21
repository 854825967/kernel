// DllUser.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include "../DllThread/IExportFun.h"

typedef IFunctionInterface* (* GET_INTERFACE)();

typedef void (* SET_INTERFACE)(ThreadCallBack pPro);

bool g_quit = false;

void WorkThreadPro( void* pParam )
{
	while( g_quit == false )
	{
		Sleep(100);
	}
}

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
		SET_INTERFACE pSetFun = (SET_INTERFACE)::GetProcAddress( hModule, "SetThreadCallBack");
		if ( pFunction && pSetFun )
		{
			(*pSetFun)(WorkThreadPro);
			IFunctionInterface* pInterface = (*pFunction)();

			if ( pInterface )
			{
				pInterface->StartWork();

				Sleep(100);
			}
		}

		::FreeLibrary(hModule);

		Sleep(1000);

		g_quit = true;
		Sleep(1000);
	}

	//while(1)
	//{
		Sleep(1000);
	//}

	return 0;
}

