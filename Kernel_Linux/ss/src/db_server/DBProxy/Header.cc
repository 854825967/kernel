#include "Header.h"
#include <time.h>

#include "util/Util.h"

// ȫ��Logָ��
ILog *g_pTrace = NULL;
// ȫ��ʱ����ָ��
ITimerAxis		*g_pTimeAxis= NULL;
// ȫ�����ݿ�����ָ��
IDBEngine		*g_pDBEngine= NULL;
// ȫ���û�����ص�ָ��
IDBProxyUserSink	*g_pUserSink= NULL;
// ����ʱ��ȫ�ֶ���
u32 g_dwSaveTimes =0 ;

extern "C" u32 GetTickCount()
{
/*
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC,&ts);//�˴������ж�һ�·���ֵ
	return (ts.tv_sec*1000 + ts.tv_nsec/(1000*1000));
  */

  return util::GetTickCount();
}



