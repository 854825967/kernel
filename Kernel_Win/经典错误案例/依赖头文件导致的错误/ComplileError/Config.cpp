#include "Config.h"

CConfig::CConfig()
{
	m_nEntryId = 1;
	m_strEntryAddr = "";
}

CConfig::~CConfig()
{
	
}

void CConfig::SetEntryId( int nEntryId )
{
	m_nEntryId = nEntryId;
}

int CConfig::GetEntryId()
{
	return m_nEntryId;
}

void CConfig::SetEntryAddr( const char* strEntryAddr)
{
	m_strEntryAddr = strEntryAddr;
}

const char* CConfig::GetEntryAddr()
{
	return m_strEntryAddr.c_str();
}
