#include "stdafx.h"
#include "ExportFun.h"

#include <process.h>

CFunctionInterface g_interface;

IFunctionInterface* GetInterface()
{
	return &g_interface;
}

CFunctionInterface::CFunctionInterface()
{
	m_hThread = NULL;
	m_bQuit = false;
}

CFunctionInterface::~CFunctionInterface()
{
}

void CFunctionInterface::WorkThreadPro( void* pParam )
{
	CFunctionInterface* pInterface = (CFunctionInterface*)pParam;

	while( pInterface->m_bQuit == false )
	{
		Sleep(100);
	}
}

bool CFunctionInterface::StartWork()
{
	m_hThread = (HANDLE)_beginthread( WorkThreadPro, 0, this);

	return true;
}
