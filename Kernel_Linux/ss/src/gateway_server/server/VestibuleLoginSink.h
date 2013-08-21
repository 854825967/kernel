#ifndef _VESTIBULELOGINSINK_H_
#define _VESTIBULELOGINSINK_H_
#include "IDBClient.h"

class CVestibuleLoginSink : public IDBClientSink
{
public:
	CVestibuleLoginSink(void);
	~CVestibuleLoginSink(void);

	virtual	void OnRet(s32 nIndex, s32 nRetCode, s64 qwUserID, s32 nRequestID,
		LPSTR pOutData, s32 nOutDataLen, LPSTR pInData = NULL, s32 nInDataLen = 0);

private:


};
extern CVestibuleLoginSink g_VestibuleLoginSink;

#endif // _VESTIBULELOGINSINK_H_
