/*******************************************************************
** 文件名:	ArrayAlloter.h
** 版  权:	(C)  
** 创建人:	
** 日  期:	2008/11/6
** 版  本:	1.0
** 描  述:	数组分配器
** 应  用:  快速取得一个数组中可用的元素
			方便的统计已分配的元素个数

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/

#ifndef __TOOL_CLASS_ARRAY_ALLOTER_H__
#define __TOOL_CLASS_ARRAY_ALLOTER_H__

#include <list>

#include "GameSys.h"

///////////////////////////////////////////////////////////////////////////////
template< s32 nArraySize , class Element >
class CArrayAlloter
{
public:
	// ------------------------------------------------------------------------
	Element & operator[]( s32 nIndex )
	{
		ASSERT( nIndex >= 0 && nIndex < nArraySize );
		return m_element[nIndex];
	}

	// ------------------------------------------------------------------------
	// 分配一个可用的元素
	// ------------------------------------------------------------------------
	s32  Allot()
	{
		if( m_UsableList.empty() )
			return -1;

		s32 nIndex = m_UsableList.front();
		m_UsableList.pop_front();

		m_nAllotedCount ++;
		return nIndex;
	}

	// ------------------------------------------------------------------------
	// 归还一个元素
	// ------------------------------------------------------------------------
	void Restore( s32 nIndex )
	{
		m_UsableList.push_back( nIndex );
		m_nAllotedCount --;
	}

	// ------------------------------------------------------------------------
	// 返回已分配的个数
	// ------------------------------------------------------------------------
	s32  CountAlloted()
	{
		return m_nAllotedCount;
	}

	// ------------------------------------------------------------------------
	CArrayAlloter() : m_nAllotedCount( 0 )
	{
		for( s32 i = 0 ; i < nArraySize ; i ++ )
		{
			m_UsableList.push_back(i);
		}
	}

private:
	Element		m_element[ nArraySize ];
	std::list< s32 > m_UsableList;
	s32			m_nAllotedCount;
};

///////////////////////////////////////////////////////////////////////////////
// 下面这个模版不需要显示的调用Restore
// 但要提供一个仿函数判断某个元素是否可用
///////////////////////////////////////////////////////////////////////////////
template< class TYPE >
struct is_element_canuse
{
	bool operator()(TYPE& d1 ) const
	{
		return !(d1.IsHaveUsed());
	}
};

template< s32 nArraySize , class Element , class __CHECK_CAN_USE2 >
class CArrayAlloter2
{
public:
	// ------------------------------------------------------------------------
	Element & operator[]( s32 nIndex )
	{
		ASSERT( nIndex >= 0 && nIndex<nArraySize );
		return m_element[nIndex];
	}

	// ------------------------------------------------------------------------
	// 分配一个可用的元素
	// ------------------------------------------------------------------------
	s32  Allot()
	{
		int i = 0;
		for ( i = m_nLastAllotIndex ; i < nArraySize ; i ++ )
		{
			if( __CHECK_CAN_USE2()( m_element[i] ) )
			{
				m_nLastAllotIndex = i + 1;
				return i;
			}
		}

		for ( i = 0 ; i < m_nLastAllotIndex ; i ++ )
		{
			if( __CHECK_CAN_USE2()( m_element[i] ) )
			{
				m_nLastAllotIndex = i + 1;
				return i;
			}
		}

		return -1;
	}

	// ------------------------------------------------------------------------
	CArrayAlloter2() : m_nLastAllotIndex( 0 )
	{
	}

private:
	Element		m_element[ nArraySize ];
	s32			m_nLastAllotIndex;
};

#endif//__TOOL_CLASS_ARRAY_ALLOTER_H__
