/******************************************************************
** 文件名:	SimpleEncrypt.h
** 创建人:	
** 版  权:	(C)  
** 日  期:	
** 版  本:	0.1
** 描  述:	简单加密类的定义
** 应  用:  服务器、客户端
** 备  注:  用于对玩家的密码进行简单加密

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/

#ifndef __SIMPLE_ENCRYPT_H__
#define __SIMPLE_ENCRYPT_H__


#include<stdlib.h>

#include "Util.h"


class CSimpleEncrypt
{
public:
	//将密钥填充到pKeyBuff，nBuffLen为缓冲区的长度（单位：字节）
	void MakeRandKey(char *pKeyBuff, int nBuffLen);

	//////////////////////////////////////////////////////////////////////////
	// 描  述：对pStrIn指向的字符串进行加密
	// 输  入：pKeyBuff为密钥缓冲区的地址，dwEnterCode为登录服发下来的登录随机数
	// 返回值：pStrOut为加密后的字符串，nOutLen为pStrOut的长度（单位：字节）
	// 备  注：pStrOut指向的缓冲区至少要是pStrIn字符串长度的2倍
	//////////////////////////////////////////////////////////////////////////
	void MakeEncrypt(const char *pStrIn, const char *pKeyBuff, DWORD dwEnterCode, char *pStrOut, int &nOutLen);

	//////////////////////////////////////////////////////////////////////////
	// 描  述：对pStrIn指向的字符串进行解密
	// 输  入：pKeyBuff为密钥缓冲区的地址，dwEnterCode为登录服发下来的登录随机数
	// 返回值：pStrOut为解密后的字符串，nOutLen为pStrOut的长度（单位：字节）
	// 备  注：pStrOut指向的缓冲区至少要是pStrIn字符串长度的二分之一
	//////////////////////////////////////////////////////////////////////////
	void UnEncrypt(const char *pStrIn, const char *pKeyBuff, DWORD dwEnterCode, char *pStrOut, int &nOutLen);

	//////////////////////////////////////////////////////////////////////////
	// 描  述：对pStrIn指向的字符串进行加密
	// 输  入：pKeyBuff为密钥缓冲区的地址，dwEnterCode为登录服发下来的登录随机数
	// 返回值：pStrOut为加密后的字符串，nOutLen为pStrOut的长度（单位：字节）
	// 备  注：pStrOut指向的缓冲区至少要是pStrIn字符串长度的2倍
	//////////////////////////////////////////////////////////////////////////
	void MakeEncrypt_SCard(const char *pStrIn, const char *pKeyBuff, DWORD dwEnterCode, char *pStrOut, int &nOutLen);

	//////////////////////////////////////////////////////////////////////////
	// 描  述：对pStrIn指向的字符串进行解密
	// 输  入：pKeyBuff为密钥缓冲区的地址，dwEnterCode为登录服发下来的登录随机数
	// 返回值：pStrOut为解密后的字符串，nOutLen为pStrOut的长度（单位：字节）
	// 备  注：pStrOut指向的缓冲区至少要是pStrIn字符串长度的二分之一
	//////////////////////////////////////////////////////////////////////////
	void UnEncrypt_SCard(const char *pStrIn, const char *pKeyBuff, DWORD dwEnterCode, char *pStrOut, int &nOutLen);

	CSimpleEncrypt();

private:
	//把字符串换成字节流
	void StrToBin(char *pStr, int nBufLen);

	//将字节流转换成字符串
	void BinToStr(char *pStr);
};



inline CSimpleEncrypt::CSimpleEncrypt()
{
	static BOOL st_bInit = FALSE;
	if (FALSE == st_bInit)
	{
		srand(util::GetTickCount());
		st_bInit = TRUE;
	}
}

//用随机字符填充pKeyBuff，nBuffLen为缓冲区的长度（单位：字节）
inline void CSimpleEncrypt::MakeRandKey(char *pKeyBuff, int nBuffLen)
{
	if (NULL == pKeyBuff)
	{
		return;
	}

	for (int i = 0; i < nBuffLen; ++i, pKeyBuff++)
	{
		*pKeyBuff = rand();
	}
}


//////////////////////////////////////////////////////////////////////////
// 描  述：对pStrIn指向的字符串进行加密
// 输  入：pKeyBuff为密钥缓冲区的地址，dwEnterCode为登录服发下来的登录随机数
// 返回值：pStrOut为加密后的字符串，nOutLen为pStrOut的长度（单位：字节）
// 备  注：pStrOut指向的缓冲区：pStrIn字符串长度的2倍 + 1
//////////////////////////////////////////////////////////////////////////
inline void CSimpleEncrypt::MakeEncrypt(const char *pStrIn, const char *pKeyBuff, DWORD dwEnterCode, char *pStrOut, int &nOutLen)
{
	if (NULL == pStrIn || NULL == pKeyBuff || NULL == pStrOut)
	{
		return;
	}

	char szTemp[512];
	memset(szTemp, 0, sizeof(szTemp));
	strncpy(szTemp, pStrIn, sizeof(szTemp));

	int nStrLen = strlen(szTemp);

	char *pKey = (char *) pKeyBuff + ((dwEnterCode + 7) % 19);
	int nKeyLen = 11;

	int nRand[9] = {22, 12, 8, 33, 1, 9, 7, 15, 18};

	int nRandPos = 0;
	int nKeyPos = 0;
	for (int i = 0; i < nStrLen; ++i, nKeyPos++, nRandPos++)
	{
		nKeyPos = nKeyPos % nKeyLen;
		nRandPos = nRandPos % (sizeof(nRand) / sizeof(int));

		szTemp[i] += (pKey[nKeyPos] % 23);
		szTemp[i] += (nRand[nRandPos]);
	}

	nOutLen = 2 * nStrLen + 1;
	StrToBin(szTemp, nOutLen);

	strncpy(pStrOut, szTemp, nOutLen);
}

//////////////////////////////////////////////////////////////////////////
// 描  述：对pStrIn指向的字符串进行解密
// 输  入：pKeyBuff为密钥缓冲区的地址，dwEnterCode为登录服发下来的登录随机数
// 返回值：pStrOut为解密后的字符串，nOutLen为pStrOut的长度（单位：字节）
// 备  注：pStrOut指向的缓冲区：pStrIn字符串长度的二分之一 + 1
//////////////////////////////////////////////////////////////////////////
inline void CSimpleEncrypt::UnEncrypt(const char *pStrIn, const char *pKeyBuff, DWORD dwEnterCode, char *pStrOut, int &nOutLen)
{
	if (NULL == pStrIn || NULL == pKeyBuff || NULL == pStrOut)
	{
		return;
	}

	char szTemp[512];
	memset(szTemp, 0, sizeof(szTemp));
	strncpy(szTemp, pStrIn, sizeof(szTemp));

	BinToStr(szTemp);
	int nStrLen = strlen(szTemp);

	char *pKey = (char *) pKeyBuff + ((dwEnterCode + 7) % 19);
	int nKeyLen = 11;

	int nRand[9] = {22, 12, 8, 33, 1, 9, 7, 15, 18};

	int nRandPos = 0;
	int nKeyPos = 0;
	for (int i = 0; i < nStrLen; ++i, nKeyPos++, nRandPos++)
	{
		nKeyPos = nKeyPos % nKeyLen;
		nRandPos = nRandPos % (sizeof(nRand) / sizeof(int));

		szTemp[i] -= (pKey[nKeyPos] % 23);
		szTemp[i] -= (nRand[nRandPos]);
	}

	nOutLen = nStrLen + 1;
	strncpy(pStrOut, szTemp, nOutLen);
}

//把字符串换成字节流
inline void CSimpleEncrypt::StrToBin(char *pStr, int nBufLen)
{
#define GET_HIGH_BY(ByValue)	((ByValue) >> 4)
#define GET_LOW_BY(ByValue)		((ByValue) & 0x0f)


	char szTemp[512];
	memset(szTemp, 0, sizeof(szTemp));

	int nStrLen = strlen(pStr);
	BYTE *pByStr = (BYTE *) pStr;
	for (int i = 0, j = 0; i < nStrLen; ++i)
	{
		BYTE byHigh = GET_HIGH_BY(pByStr[i]);
		BYTE byLow = GET_LOW_BY(pByStr[i]);

		if (byHigh <= 9) 
		{
			szTemp[j++] = (byHigh + 48);
		}
		else
		{
			szTemp[j++] = (byHigh + 55);
		}

		if (byLow <= 9) 
		{
			szTemp[j++] = (byLow + 48);
		}
		else
		{
			szTemp[j++] = (byLow + 55);
		}
	}

	strncpy(pStr, szTemp, nBufLen);
}

//将字节流转换成字符串
inline void CSimpleEncrypt::BinToStr(char *pStr)
{
#define MAKE_BYTE(ByHigh, ByLow)	(((ByHigh) << 4) | (ByLow))


	char szTemp[512];
	memset(szTemp, 0, sizeof(szTemp));

	int nStrLen = strlen(pStr);
	BYTE *pByStr = (BYTE *) pStr;
	for (int i = 0, j = 0; (i + 1) < nStrLen; i += 2)
	{
		BYTE byHigh = pByStr[i];
		BYTE byLow = pByStr[i + 1];

		if (byHigh <= 57) 
		{
			byHigh -= 48;
		}
		else
		{
			byHigh -= 55;
		}

		if (byLow <= 57) 
		{
			byLow -= 48;
		}
		else
		{
			byLow -= 55;
		}

		szTemp[j++] = MAKE_BYTE(byHigh, byLow);
	}

	strncpy(pStr, szTemp, nStrLen);
}

//////////////////////////////////////////////////////////////////////////
// 描  述：对pStrIn指向的字符串进行加密
// 输  入：pKeyBuff为密钥缓冲区的地址，dwEnterCode为登录服发下来的登录随机数
// 返回值：pStrOut为加密后的字符串，nOutLen为pStrOut的长度（单位：字节）
// 备  注：pStrOut指向的缓冲区至少要是pStrIn字符串长度的2倍
//////////////////////////////////////////////////////////////////////////
inline void CSimpleEncrypt::MakeEncrypt_SCard(const char *pStrIn, const char *pKeyBuff, DWORD dwEnterCode, char *pStrOut, int &nOutLen)
{
	if (NULL == pStrIn || NULL == pKeyBuff || NULL == pStrOut)
	{
		return;
	}

	char szTemp[512];
	memset(szTemp, 0, sizeof(szTemp));
	strncpy(szTemp, pStrIn, sizeof(szTemp));

	int nStrLen = strlen(szTemp);

	char *pKey = (char *) pKeyBuff + ((dwEnterCode + 6) % 17);
	int nKeyLen = 13;

	int nRand[11] = {3, 12, 8, 33, 1, 9, 7, 17, 19, 7, 9};
 
	int nRandPos = 0;
	int nKeyPos = 0;
	for (int i = 0; i < nStrLen; ++i, nKeyPos++, nRandPos++)
	{
		nKeyPos = nKeyPos % nKeyLen;
		nRandPos = nRandPos % (sizeof(nRand) / sizeof(int));

		szTemp[i] += (pKey[nKeyPos] % 19);
		szTemp[i] += (nRand[nRandPos]);
	}

	nOutLen = 2 * nStrLen + 1;
	StrToBin(szTemp, nOutLen);

	strncpy(pStrOut, szTemp, nOutLen);
}

//////////////////////////////////////////////////////////////////////////
// 描  述：对pStrIn指向的字符串进行解密
// 输  入：pKeyBuff为密钥缓冲区的地址，dwEnterCode为登录服发下来的登录随机数
// 返回值：pStrOut为解密后的字符串，nOutLen为pStrOut的长度（单位：字节）
// 备  注：pStrOut指向的缓冲区至少要是pStrIn字符串长度的二分之一
//////////////////////////////////////////////////////////////////////////
inline void CSimpleEncrypt::UnEncrypt_SCard(const char *pStrIn, const char *pKeyBuff, DWORD dwEnterCode, char *pStrOut, int &nOutLen)
{
	if (NULL == pStrIn || NULL == pKeyBuff || NULL == pStrOut)
	{
		return;
	}

	char szTemp[512];
	memset(szTemp, 0, sizeof(szTemp));
	strncpy(szTemp, pStrIn, sizeof(szTemp));

	BinToStr(szTemp);
	int nStrLen = strlen(szTemp);

	char *pKey = (char *) pKeyBuff + ((dwEnterCode + 6) % 17);
	int nKeyLen = 13;

	int nRand[11] = {3, 12, 8, 33, 1, 9, 7, 17, 19, 7, 9};

	int nRandPos = 0;
	int nKeyPos = 0;
	for (int i = 0; i < nStrLen; ++i, nKeyPos++, nRandPos++)
	{
		nKeyPos = nKeyPos % nKeyLen;
		nRandPos = nRandPos % (sizeof(nRand) / sizeof(int));

		szTemp[i] -= (pKey[nKeyPos] % 19);
		szTemp[i] -= (nRand[nRandPos]);
	}

	nOutLen = nStrLen + 1;
	strncpy(pStrOut, szTemp, nOutLen);
}



#endif //__SIMPLE_ENCRYPT_H__
