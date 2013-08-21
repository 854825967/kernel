/******************************************************************
** 文件名:	RandClientStr.h
** 创建人:	
** 版  权:	(C)  
** 日  期:	
** 版  本:	0.1
** 描  述:	客户端随机串生成器类的定义
** 应  用:  服务器、客户端
** 备  注:  客户端必须保证这个类对象唯一

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/
#ifndef __RAND_MAC_H__
#define __RAND_MAC_H__


#include <stdlib.h>
#include <time.h>



#pragma pack(push, 1)

//128字节的结构
struct SRAND_BUF
{
	char RandBuf[128];		//128字节的空间
};

//16字节的随机串
struct SRAND_MAC_16
{
	char RandMac16[16];		//16字节的空间
};

struct MY_RAND_STR_EX16
{
	WORD wRand1;
	WORD wRand2;
	WORD wRand3;
	WORD wRand4;

	WORD wRand5;
	WORD wRand6;
	WORD wRand7;
	WORD wRand8;

	MY_RAND_STR_EX16()
	{
		memset(this, 0, sizeof(*this));
	}
};

#pragma pack(pop)



class CRandClientStr
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 描  述：将一个16字节的随机串按位置nPos写入结构Rand_Buf中，并加密
	// 输  入：Rand_Buf，nPos的取值范围0 ~ 99
	// 返回值：写入16字节随机串的Rand_Buf
	// 备  注：Rand_Buf里面的字节不要清0，要保持随机字符
	//////////////////////////////////////////////////////////////////////////
	void CreateRandMACBuf(SRAND_BUF &Rand_Buf, int nPos);

	//////////////////////////////////////////////////////////////////////////
	// 描  述：按位置nPos从Rand_Buf中取出16字节的随机串
	// 输  入：Rand_Buf，nPos的取值范围0 ~ 99，RandMac
	// 返回值：16字节随机串RandMac
	//////////////////////////////////////////////////////////////////////////
	void GetRandMAC(SRAND_BUF &Rand_Buf, int nPos, SRAND_MAC_16 &RandMac);

	CRandClientStr();

private:
	//用随机字符填充Rand_Buf
	void MakeRandChar(SRAND_BUF &Rand_Buf);

private:
	SRAND_MAC_16 m_RandMac16;
};




inline CRandClientStr::CRandClientStr()
{
	static BOOL bInit = FALSE;
	if (FALSE == bInit)
	{
		srand(time(NULL));
		bInit = TRUE;
	}

	MY_RAND_STR_EX16 *pRandStr = (MY_RAND_STR_EX16 *) (m_RandMac16.RandMac16);

	pRandStr->wRand1 = rand();
	pRandStr->wRand2 = rand();
	pRandStr->wRand3 = rand();
	pRandStr->wRand4 = rand();

	pRandStr->wRand5 = rand();
	pRandStr->wRand6 = rand();
	pRandStr->wRand7 = rand();
	pRandStr->wRand8 = rand();
}

//////////////////////////////////////////////////////////////////////////
// 描  述：将一个16字节的随机串按位置nPos写入结构Rand_Buf中，并加密
// 输  入：Rand_Buf，nPos的取值范围0 ~ 99
// 返回值：写入16字节随机串的Rand_Buf
// 备  注：Rand_Buf里面的字节不要清0，要保持随机字符
//////////////////////////////////////////////////////////////////////////
inline void CRandClientStr::CreateRandMACBuf(SRAND_BUF &Rand_Buf, int nPos)
{
	MakeRandChar(Rand_Buf);

	nPos = nPos % 100;

	memcpy(&(Rand_Buf.RandBuf[nPos]), m_RandMac16.RandMac16, sizeof(m_RandMac16.RandMac16));

	int nTemp = 117 + (nPos % 10);
	char cXOR = Rand_Buf.RandBuf[nTemp];
	for(int i = 0; i < 116; i++)
	{
		Rand_Buf.RandBuf[i] ^= cXOR;
	}
}

//////////////////////////////////////////////////////////////////////////
// 描  述：按位置nPos从Rand_Buf中取出16字节的随机串
// 输  入：Rand_Buf，nPos的取值范围0 ~ 99，RandMac
// 返回值：16字节随机串RandMac
//////////////////////////////////////////////////////////////////////////
inline void CRandClientStr::GetRandMAC(SRAND_BUF &Rand_Buf, int nPos, SRAND_MAC_16 &RandMac)
{
	nPos = nPos % 100;

	int nTemp = 117 + (nPos % 10);
	char cXOR = Rand_Buf.RandBuf[nTemp];

	for(int i = 0; i < 16; i++)
	{
		RandMac.RandMac16[i] = Rand_Buf.RandBuf[nPos + i] ^ cXOR;
	}
}

//用随机字符填充Rand_Buf
inline void CRandClientStr::MakeRandChar(SRAND_BUF &Rand_Buf)
{
	WORD *pwTemp = (WORD *) Rand_Buf.RandBuf;

	int nCount = sizeof(Rand_Buf.RandBuf) / sizeof(WORD);
	for (int i = 0; i < nCount; ++i, pwTemp++)
	{
		*pwTemp = rand();
	}
}


#endif //__RAND_MAC_H__
