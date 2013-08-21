// ComplileError.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "../Config.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CConfig pConfig;
	pConfig.SetEntryAddr( "12345" );

	return 0;
}

