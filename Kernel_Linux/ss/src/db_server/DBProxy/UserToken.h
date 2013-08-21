#ifndef __USERTOKEN_H__
#define __USERTOKEN_H__
#include "DataProcToken.h"
#include "ITimeAxis.h"

// 用户令牌
class CUserToken : public ITimerHandler
{
public:
	// 构造函数
	CUserToken(s64 qwUserID, CDataProcToken *pDataProcToken);

	// 析构函数
	~CUserToken();

	// 定时器回调
	virtual void OnTimer(u32 dwTimerID);

	// 生成令牌
	BOOL Create(s32 nRequestID, LPSTR pInData, s32 nInDataLen,
		LPSTR pOutData, s32 &nOutDataLen);

	// 验证令牌
	BOOL Check(s32 nRequestID, LPSTR pInData, s32 nInDataLen,
		LPSTR pOutData, s32 &nOutDataLen);

	// 踢人
	BOOL KickUser(s32 nRequestID, LPSTR pInData, s32 nInDataLen,
		LPSTR pOutData, s32 &nOutDataLen);

private:
	s64		m_qwUserID;		// 用户ID
	u32		m_dwToken[4];	// 用户令牌
	BOOL	m_dwTokenOK;	// 用户令牌是否生成标志
	char 	m_szFlag[16];	// 客户端标示串
	s32		m_lJumpType;	// 跳转类型
	CDataProcToken	*m_pDataProcToken;	// 数据处理指针
};

#endif // __USERTOKEN_H__

