#ifndef __VESTIBULERUNSINK_H__
#define __VESTIBULERUNSINK_H__
#include "IDBClient.h"

class CVestibuleRunSink : public IDBClientSink
{
public:
	CVestibuleRunSink(void);
	~CVestibuleRunSink(void);
	virtual	void OnRet(s32 nIndex, s32 nRetCode, s64 qwUserID, s32 nRequestID,
		LPSTR pOutData, s32 nOutDataLen, LPSTR pInData = NULL, s32 nInDataLen = 0);

};

extern CVestibuleRunSink g_VestibuleRunSink;


#endif // __VESTIBULERUNSINK_H__
