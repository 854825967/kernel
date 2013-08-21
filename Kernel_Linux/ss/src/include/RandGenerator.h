 /******************************************************************
 ** 文件名:	RandGenerator.h
 ** 创建人:	
 ** 版  权:	(C)  
 ** 日  期:	 
 ** 版  本:	0.1
 ** 描  述:	随机数发生器，使用前须播种子CRandGenerator::Seed
 ** 应  用:  
 ** 备  注:   
 
 **************************** 修改记录 ******************************
 ** 修改人: 
 ** 日  期: 
 ** 描  述: 
 ********************************************************************/

#ifndef __RAND__GENERATOR__h
#define __RAND__GENERATOR__h

#include <stdlib.h>

#define GENIUS_NUMBER 0x376EAC5D

#define MAX_RAND_NUMBER 99999

class CRandGenerator {
 public:
  CRandGenerator() : rand_number_(0), seed_(0) {}
  ~CRandGenerator() {}

  void Seed(unsigned int seed) {
    this->seed_ = seed;
    srand(this->seed_);
  }

  unsigned int Seed() {
    this->rand_number_ = 0;
    this->Seed((unsigned int)(time(NULL)));
    return this->seed_;
  }

  WORD GetWORD() {
    if(++rand_number_ > MAX_RAND_NUMBER) {
      this->Seed();
    }
    return (WORD)(rand());
  }

  DWORD GetDWORD() {
    if(++rand_number_ > MAX_RAND_NUMBER) {
      this->Seed();
    }
    return (DWORD)(rand());
  }

 private:
  u32 rand_number_;
  u32 seed_;
};

#if 0

class CRandGenerator
{
	enum 
	{
		Number = 0x1000, 
	};
public:
	/** 固定种子
	@param   
	@param   
	@return  
	*/
	void Seed(DWORD dwSeed)
	{
		m_Seed = dwSeed^GENIUS_NUMBER;

		Batch();
	}

	/** 随机种子
	@param   
	@param   
	@return  
	*/
	DWORD Seed(void)
	{
		int s = time(NULL);
		Seed(s);

		return s^GENIUS_NUMBER;
	}

	/** 
	@param   
	@param   
	@return  
	*/
	DWORD GetSeed(void) const
	{
		return m_Seed^GENIUS_NUMBER;
	}

	/** 产生一个WORD
	@param   
	@param   
	@return  
	*/
	WORD GetWORD(void)
	{
		if(m_Ptr >= Number * 2)
		{
			Batch();
			m_Ptr = 0;
		}

		return *((WORD *)m_pBuffer + m_Ptr++);
	};

	/** 产生一个DWord
	@param   
	@param   
	@return  
	*/
	DWORD GetDWORD(void)
	{
		if(m_Ptr >= Number * 2 - 1)
		{
			Batch();
			m_Ptr=0;
		}	

		m_Ptr += 2;
		return *(DWORD *)((WORD *)m_pBuffer + m_Ptr - 2);
	}

	/** 
	@param   
	@param   
	@return  
	*/
	CRandGenerator(void)
	{
		int s = time(NULL);
		m_pBuffer = new DWORD[Number];
		m_Ptr = Number * 2;
		m_Seed = s;
	}

	/** 
	@param   
	@param   
	@return  
	*/
	virtual ~CRandGenerator(void)
	{
		delete[] m_pBuffer;
	}

private:
	/** 产生一批
	@param   
	@param   
	@return  
	*/
	void		Batch(void)
	{
		__asm 
		{
			cld
				mov edi,[ecx]CRandGenerator.m_pBuffer
				mov eax,[ecx]CRandGenerator.m_Seed
				mov ecx,0x1000		;//WRandom::Number
			mov esi,0xE7BD2160

				ALIGN 4
_loop_circle1:
			push ecx
				mov ecx,32
_loop_circle2:
			mov ebx,eax
				shl eax,1
				and ebx,esi;	//select the bit for xor
			mov edx,ebx
				bswap ebx
				xor bx,dx
				xor bh,bl;		// because P only judge one byte
			;// so must XOR to judge the p of whole word 
			jp _next;		//jp equals the xor 
			inc eax
_next:
			dec ecx
				jnz _loop_circle2
				pop ecx
				stosd
				dec ecx
				jnz _loop_circle1
				mov ecx,this
				mov [ecx]CRandGenerator.m_Seed,eax
		}
	}

private:
	DWORD *		m_pBuffer;
	DWORD		m_Seed;
	unsigned	m_Ptr;
};

#endif // 0

extern CRandGenerator g_RandGenerator;

#endif // __RAND__GENERATOR__h
