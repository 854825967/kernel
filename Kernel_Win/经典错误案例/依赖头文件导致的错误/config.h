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
	std::string m_strEntryAddr;
};
#endif // _CONFIG_H
