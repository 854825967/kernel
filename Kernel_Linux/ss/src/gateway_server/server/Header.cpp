#include "Header.h"

#include <stdarg.h>
#include <time.h>

ILog *g_pServerLog = NULL;
char LogFileName[MAX_PATH] = "./gateway_server.log";

void PrintInfoLog(LPCSTR lpszFormat, ...)
{
	va_list	args;
	va_start(args, lpszFormat);

	char szBuffer[1024] = {0};
	vsnprintf(szBuffer, sizeof(szBuffer) - 1, lpszFormat, args);

	time_t now;
	time(&now);
	tm when = *localtime(&now);
	char szCurTime[32] = {0};
	strftime(szCurTime, sizeof(szCurTime), "%Y-%m-%d %H:%M:%S", &when);

	FILE *fp = fopen(LogFileName, "a");
	if (fp != NULL)
	{
		fprintf(fp, "[%s]: %s\n", szCurTime, szBuffer);
		fclose(fp);
	}

	va_end(args);
}
