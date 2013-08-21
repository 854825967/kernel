/*******************************************************************
** 文件名:  ITokenzeFun.h
** 版  权:	(C)  
** 创建人:	
** 日  期:	2010-01-14
** 版  本:	1.0
** 描  述:	字符串分割 函数实现
** 应  用:  
 
**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/


#ifndef _ITOKENZEFUN_H_
#define _ITOKENZEFUN_H_

#include <string>
#include <vector>

// 实现字符串按照steps 字符进行分割数组
extern int inline ToStrkenize(const char *ptr,const char *steps,std::vector<std::string>& v);

// 实现字符串按照steps 字符进行分割数组
extern int inline ToWordkenize(const char *ptr,const char *steps,std::vector<WORD>& v);

// 实现字符串按照steps 字符进行分割数组
extern int inline ToByteKenize(char *ptr,const char *steps,std::vector<BYTE>& v);
// 实现字符串按照steps 字符进行分割数组
extern int inline TolongKenize(char *ptr,const char *steps,std::vector<int>& v);

template<class T> 
extern inline int ParseIntArray(const char* str, T* arr, int count, const char sep = '+');

// 将一个字符串分解为浮点列表
extern int inline  ParseFloatArray(const char* str, float* arr, int count, const char sep = '+');

 
// 实现字符串按照steps 字符进行分割数组
int inline ToStrkenize(const char *ptr,const char *steps,std::vector<std::string>& v)
{
	if (ptr == NULL)
	{
		return 0;
	}

	int numToken = 0;
	char *token = 0;
	v.clear();
	//strtok 这个函数 会修改回来字符串的内容
	//所以要把内容缓存起来
	int len= strlen(ptr);
	if (len==0)
	{
		return 0;
	}
	char *tmp=new char[len+1];
	memset(tmp,0,len+1);
	strncpy(tmp,ptr,len+1);


	token=strtok(tmp,steps);
	while(token != NULL)
	{   v.push_back(token);
	numToken++;
	token=strtok(NULL,steps);
	}

	if (tmp != NULL)
	{
		delete [] tmp;
		tmp = NULL;
	}

	return numToken;
}

// 实现字符串按照steps 字符进行分割数组
int inline ToWordkenize(const char *ptr,const char *steps,std::vector<WORD>& v)
{
	if (ptr == NULL)
	{
		return 0;
	}
	int numToken = 0;
	char *token = 0;
	v.clear();
	//strtok 这个函数 会修改回来字符串的内容
	//所以要把内容缓存起来
	int len= strlen(ptr);
	if (len==0)
	{
		return 0;
	}
	char *tmp=new char[len+1];
	memset(tmp,0,len+1);
	strncpy(tmp,ptr,len+1);


	token=strtok(tmp,steps);
	while(token != NULL)
	{   v.push_back((WORD)atoi(token));
	numToken++;
	token=strtok(NULL,steps);
	}

	if (tmp != NULL)
	{
		delete [] tmp;
		tmp = NULL;
	}

	return numToken;
}

// 实现字符串按照steps 字符进行分割数组
int inline ToByteKenize(char *ptr,const char *steps,std::vector<BYTE>& v)
{
	if (ptr == NULL)
	{
		return 0;
	}
	int numToken = 0;
	char *token = 0;
	v.clear();
	//strtok 这个函数 会修改回来字符串的内容
	//所以要把内容缓存起来
	int len= strlen(ptr);
	if (len==0)
	{
		return 0;
	}
	char *tmp=new char[len+1];
	memset(tmp,0,len+1);
	strncpy(tmp,ptr,len+1);


	token=strtok(tmp,steps);
	while(token != NULL)
	{
		v.push_back((BYTE)atoi(token));
		numToken++;
		token=strtok(NULL,steps);
	}

	if (tmp != NULL)
	{
		delete [] tmp;
		tmp = NULL;
	}

	return numToken;
}

// 实现字符串按照steps 字符进行分割数组
int inline TolongKenize(char *ptr,const char *steps,std::vector<s32>& v)
{
	if (ptr == NULL)
	{
		return 0;
	}
	int numToken = 0;
	char *token = 0;
	v.clear();
	//strtok 这个函数 会修改回来字符串的内容
	//所以要把内容缓存起来
	int len= strlen(ptr);
	if (len==0)
	{
		return 0;
	}
	char *tmp=new char[len+1];
	memset(tmp,0,len+1);
	strncpy(tmp,ptr,len+1);


	token=strtok(tmp,steps);
	while(token != NULL)
	{
		v.push_back(atoi(token));
		numToken++;
		token=strtok(NULL,steps);
	}

	if (tmp != NULL)
	{
		delete [] tmp;
		tmp = NULL;
	}

	return numToken;
}

/// 将一个字符串分解为整数列表
template<class T>
inline int ParseIntArray(const char* str, T* arr, int count, const char sep )
{
	if(arr == NULL || count == 0)
	{
		return 0;
	}
	if (!str) return 0;

	char buf[32];
	int i = 0;
	int j = 0;
	const char* p = str;
	while (*p)
	{
		if (*p == sep)
		{
			p++;
			buf[i] = 0;
			i = 0;
			arr[j++] = (T)atoi(buf);
			if (j >= count)
				return j;
		}
		else
			buf[i++] = *p++;
	}

	if (i > 0)
	{
		buf[i] = 0;
		arr[j++] = (T)atoi(buf);
	}

	return j;
}

// 将一个字符串分解为浮点列表
int inline ParseFloatArray(const char* str, float* arr, int count, const char sep)
{
	if(arr == NULL || count == 0)
	{
		return 0;
	}

	if (!str) return 0;

	char buf[32];
	int i = 0;
	int j = 0;
	const char* p = str;
	while (*p)
	{
		if (*p == sep)
		{
			p++;
			buf[i] = 0;
			i = 0;
			arr[j++] = (float)atof(buf);
			if (j >= count)
				return j;
		}
		else
			buf[i++] = *p++;
	}

	if (i > 0)
	{
		buf[i] = 0;
		arr[j++] = (float)atof(buf);
	}

	return j;
}

#endif // _ITOKENZEFUN_H_
