#pragma once

#include "IExportFun.h"


class CFunctionInterface : public IFunctionInterface
{
public:
	CFunctionInterface();
	~CFunctionInterface();

	static void WorkThreadPro( void* pParam );

public:
	bool StartWork();

private:
	HANDLE m_hThread;
	bool m_bQuit;
};
