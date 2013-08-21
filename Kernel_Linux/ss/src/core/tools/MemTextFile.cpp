
#include <string.h>

#include "MemTextFile.h"


CMemTextFile::~CMemTextFile()
{
	if (m_pBuffer)
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		m_nBufSize = 0;
	}
}

BOOL CMemTextFile::Open(LPCSTR szFileName)
{
	if (!szFileName || *szFileName == '\0') 
		return FALSE;

	FILE* hFile = fopen(szFileName, "rb");
	if (!hFile)
		return FALSE;

	fseek(hFile, 0, SEEK_END);
	m_nFileSize = ftell(hFile);
	int nGoodSize = m_nFileSize + 3; // 为了在后面加入 '\r' '\n' '\0'

	m_nBufSize = (nGoodSize + 7) & ~7;
	m_pBuffer = new char[m_nBufSize];
	if (!m_pBuffer)
		return FALSE;

	fseek(hFile, 0, SEEK_SET);
	if (1 != fread(m_pBuffer, m_nFileSize, 1, hFile))
	{
		fclose(hFile);
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		return FALSE;
	}

	MakeSimpleMap2((BYTE*)m_pBuffer, "Mska@qws#d!");
	MakeSimpleMap((BYTE*)m_pBuffer, nGoodSize);
	m_pBuffer[m_nFileSize] = '\r';
	m_pBuffer[m_nFileSize + 1] = '\n';
	m_pBuffer[m_nFileSize + 2] = '\0';
	m_pPos = m_pBuffer;

	fclose(hFile);

	return TRUE;
}

BOOL CMemTextFile::Open(LPCSTR lpBuff,int nLen)
{
	m_nFileSize =nLen;
 
	m_nBufSize = ( m_nFileSize + 3 + 7) & ~7; // 为了在后面加入 '\r' '\n' '\0'
 
	m_pBuffer = new char[m_nBufSize];
	if (!m_pBuffer)
		return FALSE;

	memcpy(m_pBuffer,lpBuff,nLen);
	m_pBuffer[m_nFileSize] = '\r';
	m_pBuffer[m_nFileSize + 1] = '\n';
	m_pBuffer[m_nFileSize + 2] = '\0';

	m_pPos = m_pBuffer;
	return TRUE;
}


BOOL CMemTextFile::Save(LPCSTR szFileName)
{
	if (!szFileName || *szFileName == '\0') 
		return FALSE;

	char* pBuffer = new char[m_nBufSize];
	if (!pBuffer)
		return FALSE;

	FILE* hFile = fopen(szFileName, "w");
	if (!hFile)
		return FALSE;

	memcpy(pBuffer, m_pBuffer, m_nBufSize);
	MakeSimpleMap((BYTE*)pBuffer, m_nFileSize + 3);
	MakeSimpleMap2((BYTE*)pBuffer, "Mska@qws#d!");
	if (1 != fwrite(pBuffer, m_nFileSize, 1, hFile))
	{
		fclose(hFile);
		delete[] pBuffer;
		return FALSE;
	}

	delete[] pBuffer;
	fclose(hFile);

	return TRUE;
}

// 文本文件的一行：a b c d \r \n
// GetLine后变为：a b c d \n \0
char* CMemTextFile::GetLine(char* pString, int nSize)
{
	int nLen = 0;
	if (*m_pPos == '\0') return NULL;
	while (*m_pPos != '\r')
	{
		m_pPos ++;
		nLen ++;
	}
	if (m_pPos - m_pBuffer >= m_nFileSize && nLen == 0) // 文件尾
		return NULL;
	if (nLen + 2 > nSize) // 传入的缓存太小
	{
		// OutputDebugString("pString size too small!\r\n");
		return NULL;
	}
	memcpy(pString, m_pPos - nLen, nLen);
	*(pString + nLen) = '\n';
	*(pString + nLen + 1) = '\0';
	m_pPos += 2;
	return (m_pPos - nLen - 2);
}

// 作简单异或运算
// 速度测试结果:一个130K的buffer经过10000次MakeSimpleMap操作，耗时1000ms
BOOL CMemTextFile::MakeSimpleMap(BYTE* buf, int nLen)
{
/*
	__asm{
		// eax:(nLen/8)
		// ebx:尾部经过8字节对齐后剩余的小于8字节的字节数所占的位数
		// ecx:64-ebx
		// mm7:key
		mov esi, dword ptr buf;
		mov eax, nLen;
		pcmpeqd mm7, mm7;
		movd mm6, eax;
		mov ebx, eax;
		psllq mm6, 32;
		movd mm5, ebx;
		and ebx, 7;
		paddd mm6, mm5;
		shr eax, 3;
		pxor mm7, mm6;
		align 4;
_loop:	
		cmp eax, 0;
		jz _tail;
		movq mm0, [esi];
		pxor mm0, mm7;
		movq [esi], mm0;
		add esi,8;
		dec eax;
		jmp _loop;
_tail:
		cmp ebx, 0;
		jz _done;

		// 处理尾部残余的字节
		pcmpeqd mm1, mm1;
		pcmpeqd mm2, mm2;
		shl ebx, 3;
		mov ecx, 64;
		movq mm0, [esi];
		sub ecx, ebx;
		movd mm3, ebx;
		movd mm4, ecx;
		psllq mm1, mm3;
		psrlq mm2,mm4;
		pand mm1, mm0;
		por mm1, mm2;
		pxor mm0, mm7;
		pand mm0, mm1;
		movq [esi], mm0;
_done:
		emms;
	}
*/
	return TRUE;
}


void CMemTextFile::MakeSimpleMap2(BYTE* buf, const char *szKey)
{
	const char	*szKeyTemp = szKey;

	for (int i = 0; i < m_nFileSize; i ++)
	{
		buf[i] ^= *szKeyTemp ++;

		if (0 == *szKeyTemp)
		{
			szKeyTemp = szKey;
		}
	}
}
