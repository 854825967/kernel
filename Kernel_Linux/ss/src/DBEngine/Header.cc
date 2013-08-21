#include "Header.h"
#include "stdarg.h"
#include "util/Util.h"

// 输出信息日志
extern "C" void GPrintInfoLog(LPCSTR lpszFormat, ...)
{
	va_list	args;
	va_start(args, lpszFormat);

	char szBuffer[1024] = {0};
	snprintf(szBuffer, sizeof(szBuffer) - 1, lpszFormat, args);

	time_t now;
	time(&now);
	tm when = *localtime(&now);
	char szCurTime[32] = {0};
	strftime(szCurTime, sizeof(szCurTime), "%Y-%m-%d %H:%M:%S", &when);

	FILE *fp = fopen(INFO_FILE, "a");
	if (fp != NULL)
	{
		fprintf(fp, "[%s][%d]: %s\n", szCurTime, GetTickCount(), szBuffer);
		fclose(fp);
	}

	va_end(args);
}

extern "C" u32 GetTickCount()
{
/*
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC,&ts);//此处可以判断一下返回值
	return (ts.tv_sec*1000 + ts.tv_nsec/(1000*1000));
  */
  return util::GetTickCount();
}
