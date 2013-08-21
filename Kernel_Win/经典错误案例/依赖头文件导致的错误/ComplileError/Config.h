#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>

// CConfig

class CConfig
{
public:
	CConfig();
	~CConfig();

	void SetEntryId( int nEntryId );
	int GetEntryId();

	void SetEntryAddr( const char* strEntryAddr);
	const char* GetEntryAddr();
private:
	int m_nEntryId;
	int m_n1;
	int m_n2;
	int m_n3;
	int m_n4;
	int m_n5;
	int m_n6;
	int m_n7;
	int m_n8;
	int m_n9;
	std::string m_strEntryAddr;
};

#endif // _CONFIG_H