#include "Header.h"
#include "AsynObject.h"

// ���캯��
CAsynObject::CAsynObject()
{
	m_nIndex = 0;
	m_qwUserID = -1;
	m_pInData = NULL;
	m_nInDataLen = 0;
	m_pOutData = NULL;
	m_nOutDataLen = 0;
	m_nReturn = DBRET_ERROR_LOGIC;

	m_pRequestConfig = NULL;
	m_pDBADO = NULL;
	m_pRet = NULL;
}

// ��������
CAsynObject::~CAsynObject()
{
}

// �����첽���󻷾�
BOOL CAsynObject::Create(s32 nIndex, s32 nRequestID, s64 qwUserID, LPSTR pInData, s32 nInDataLen,
						 CDBADO *pDBADO, IDBRetSink *pRet)
{
	if (NULL == pInData || nInDataLen <= 0 || NULL == pDBADO)
	{
		return FALSE;
	}

	if (m_pInData != NULL || m_pOutData != NULL)
	{
		return FALSE;
	}

	// ����Ҳ��������������Ϣ�򲻴���
	m_pRequestConfig = g_RequestConfig.FindRequestConfig(nRequestID);
	if (NULL == m_pRequestConfig)
	{
		return FALSE;
	}

	// ����������ݳ����������е��������ݳ��Ȳ�һ���򲻴���
	if (nInDataLen != GetInDataLen())
	{
		return FALSE;
	}

	m_nIndex = nIndex;
	m_qwUserID = qwUserID;

	m_pInData = new char[nInDataLen];
	if (NULL == m_pInData)
	{
		return FALSE;
	}

	memcpy(m_pInData, pInData, nInDataLen);
	m_nInDataLen = nInDataLen;

	m_pDBADO = pDBADO;
	m_pRet = pRet;

	return TRUE;
}

// �ͷ��첽����
void CAsynObject::Close(void)
{
	if (m_pInData != NULL)
	{
		delete[] m_pInData;
		m_pInData = NULL;
	}

	if (m_pOutData != NULL)
	{
		delete[] m_pOutData;
		m_pOutData = NULL;
	}

	m_nIndex = 0;
	m_qwUserID = -1;
	m_nInDataLen = 0;
	m_nOutDataLen = 0;
	m_nReturn = DBRET_ERROR_LOGIC;

	m_pRequestConfig = NULL;
	m_pDBADO = NULL;
	m_pRet = NULL;
}

// �����첽��������ݿ�����
s32 CAsynObject::OnRequest(void)
{
	try
	{
    while(true) {
      m_pDBADO->ClearParam();
      m_pDBADO->SetSPName(m_pRequestConfig->szSPName);

      u32 dwTotalParam = m_pRequestConfig->SPParamList.size();
      u32 dwParamIndex = 0;
      list<SPPARAM>::iterator	itSPParam = m_pRequestConfig->SPParamList.begin();
      for (; itSPParam != m_pRequestConfig->SPParamList.end(); ++ itSPParam)
      {
        SPPARAM		*pSPParam = &(*itSPParam);

        SQLTypeAdapter	vtTemp;

        if (adParamInput == pSPParam->nDirection || adParamInputOutput == pSPParam->nDirection)
        {
          if (FALSE == GetInDataMem(pSPParam->szInputStructMemName, pSPParam->nType, vtTemp))
          {
            m_nReturn = DBRET_ERROR_UNKNOWN;
            return m_nReturn;
          }
        }
        dwParamIndex++;
        m_pDBADO->AddParam(vtTemp, (DataTypeEnum)pSPParam->nType, dwParamIndex, dwTotalParam);
      }

      if (TRUE == m_pRequestConfig->bRecordset)
      {
#ifdef PERFORMANCE_TEST
        // �����ʱͳ��
        timespec ts;
        s64 startCounter = 0;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        startCounter = (uint64)(ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
        //::QueryPerformanceCounter((LARGE_INTEGER *)&startCounter);
        //LARGE_INTEGER litmp;
        //::QueryPerformanceFrequency(&litmp);
#endif

        if(m_pDBADO->OpenRecordset() != 0) break;

#ifdef PERFORMANCE_TEST
        // �����ʱͳ��
        s64 endCounter = 0;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        endCounter = (uint64)(ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
        //::QueryPerformanceCounter((LARGE_INTEGER *)&endCounter);
        if(endCounter - startCounter > 10000)
          // g_pDBEngine->PrintInfoLog("����[%d]�����ʱ[%lu]us", m_pRequestConfig->nID, (endCounter - startCounter));
          g_pDBEngine->PrintInfoLog("����[%d]�����ʱ[%lu]us", m_pRequestConfig->nID, (endCounter - startCounter));
        //printf("����[%d]�����ʱ[%lld]us\n\n\n", m_pRequestConfig->nID, (endCounter - startCounter) * 1000000 / litmp.QuadPart);
#endif
      }
      else
      {
        if(m_pDBADO->OpenNoRecordset() != 0) break;
      }
    }

		// ��ȡ����ֵ��Ϣ
		s32 lReturnValue = 0;
		m_nReturn = DBRET_OK;

		m_nOutDataLen = GetOutDataLen();
		if (m_nOutDataLen < 0)
		{
			m_nReturn = DBRET_ERROR_UNKNOWN;
			return m_nReturn;
		}

		m_pOutData = new char[m_nOutDataLen];
		if (NULL == m_pOutData)
		{
			m_nReturn = DBRET_ERROR_UNKNOWN;
			return m_nReturn;
		}

		LPSTR pOutData = m_pOutData;

		// ����洢���̷��ز���
		list<OUTPUTSTRUCTMEM>::iterator	itOutputStructMem = m_pRequestConfig->OutputStructMemList.begin();
		for (; itOutputStructMem != m_pRequestConfig->OutputStructMemList.end(); ++ itOutputStructMem)
		{
			OUTPUTSTRUCTMEM	*pOutputStructMem = &(*itOutputStructMem);
			if (DS_INPUTSTRUCT == pOutputStructMem->nSource)
			{
				pOutData = PutOutDataMemForStruct(pOutData, pOutputStructMem->szParamName, pOutputStructMem->nLen);
				if (NULL == pOutData)
				{
					m_nReturn = DBRET_ERROR_UNKNOWN;
					return m_nReturn;
				}
			}
			else if (DS_STOREPROCEDURE == pOutputStructMem->nSource)
			{
				/*
				_variant_t	vtTemp;
				m_pDBADO->GetParamValue(pOutputStructMem->szParamName, vtTemp);
				pOutData = PutOutDataMemForVT(pOutData, vtTemp, pOutputStructMem->nLen);
				if (NULL == pOutData)
				{
					m_nReturn = DBRET_ERROR_UNKNOWN;
					return m_nReturn;
				}
				*/
			}
		}

		// ��������
		if (TRUE == m_pRequestConfig->bRecordset)
		{
			s32	nRecordCount = m_pDBADO->GetRecordCount();
			for (s32 i = 0; i < nRecordCount; i ++)
			{
				// ����Ѿ����˼�¼���Ľ�β�򷵻�
				if (TRUE == m_pDBADO->IsRecordsetEOF())
				{
					break;
				}

				list<OUTPUTSTRUCTMEM>::iterator	itOutputStructMemForRst = m_pRequestConfig->OutputStructMemForRstList.begin();
				for (; itOutputStructMemForRst != m_pRequestConfig->OutputStructMemForRstList.end(); ++ itOutputStructMemForRst)
				{
					OUTPUTSTRUCTMEM	*pOutputStructMemForRst = &(*itOutputStructMemForRst);
					if (DS_INPUTSTRUCT == pOutputStructMemForRst->nSource)
					{
						pOutData = PutOutDataMemForStruct(pOutData, pOutputStructMemForRst->szParamName, pOutputStructMemForRst->nLen);
						if (NULL == pOutData)
						{
							m_nReturn = DBRET_ERROR_UNKNOWN;
							return m_nReturn;
						}
					}
					else if (DS_STOREPROCEDURE == pOutputStructMemForRst->nSource)
					{
						String	vtTemp;
						m_pDBADO->GetParamValue(pOutputStructMemForRst->szParamName, vtTemp);
						pOutData = PutOutDataMemForVT(pOutData, vtTemp, pOutputStructMemForRst->nLen);
						if (NULL == pOutData)
						{
							m_nReturn = DBRET_ERROR_UNKNOWN;
							return m_nReturn;
						}
					}
					else if (DS_RECORDSET == pOutputStructMemForRst->nSource)
					{
						String	vtTemp;
            if(m_pDBADO->GetFieldValue(pOutputStructMemForRst->szParamName, vtTemp) == FALSE)
            {
              return m_nReturn;
            }
            pOutData = PutOutDataMemForVT(pOutData, vtTemp, pOutputStructMemForRst->nLen);
            if (NULL == pOutData)
            {
              m_nReturn = DBRET_ERROR_UNKNOWN;
              return m_nReturn;
            }
					}
				}

				// ׼����ȡ��һ����¼
				if (FALSE == m_pDBADO->RecordsetNext())
				{
					m_nReturn = DBRET_ERROR_UNKNOWN;
					return m_nReturn;
				}
			}

			// �رս����
			m_pDBADO->CloseRecordset();
		}

		return m_nReturn;
	}
	catch (...)
	{
		m_nReturn = DBRET_ERROR_UNKNOWN;
		return m_nReturn;
	}

	m_nReturn = DBRET_ERROR_UNKNOWN;
	return m_nReturn;
}

// �����첽��������ݿⷵ��
void CAsynObject::OnRet(void)
{
	if (m_pRet != NULL)
	{
		m_pRet->OnRet(m_nIndex, m_qwUserID, m_pRequestConfig->nID, m_pInData, m_nInDataLen, 
			m_nReturn, m_pOutData, m_nOutDataLen);
	}
}

// ��ȡ�����û�ID
s64 CAsynObject::GetUserID(void)
{
	return m_qwUserID;
}

// ��ȡ��Ҫ��
s32 CAsynObject::GetWeightness(void)
{
	return m_pRequestConfig->nWeightNess;
}

// ��ȡ����ID
s32 CAsynObject::GetRequestID(void)
{
	return m_pRequestConfig->nID;
}

// �������ݵ��ļ�
void CAsynObject::DumpToFile(FILE *fp)
{
	time_t	now;
	time(&now);
	tm	when = *localtime(&now);
	char	szCurTime[32] = {0};
	strftime(szCurTime, sizeof(szCurTime), "%Y-%m-%d %H:%M:%S", &when);

	// д��ʱ����Ϣ(32�ֽ�)
	fwrite(szCurTime, sizeof(szCurTime), 1, fp);
	// д������ID(4�ֽ�)
	fwrite(&m_pRequestConfig->nID, sizeof(m_pRequestConfig->nID), 1, fp);
	// д���û�ID(4�ֽ�)
	fwrite(&m_qwUserID, sizeof(m_qwUserID), 1, fp);
	// д���������ݳ���(4�ֽ�)
	fwrite(&m_nInDataLen, sizeof(m_nInDataLen), 1, fp);
	// д����������(�������泤��д��)
	fwrite(m_pInData, m_nInDataLen, 1, fp);
}

// ��ȡ�������ݳ���
s32 CAsynObject::GetInDataLen(void)
{
	try
	{
		s32	nInDataLen = 0;

		list<INPUTSTRUCTMEM>::iterator	itInputStructMem = m_pRequestConfig->InputStructMemList.begin();
		for (; itInputStructMem != m_pRequestConfig->InputStructMemList.end(); ++ itInputStructMem)
		{
			INPUTSTRUCTMEM	*pInputStructMem = &(*itInputStructMem);
			nInDataLen += pInputStructMem->nLen;
		}

		return nInDataLen;
	}
	catch (...)
	{
		return -1;
	}

	return -1;
}

// ��ȡ�������ݵĳ�Ա��Ϣ, ע������ֽڶ�������
BOOL CAsynObject::GetInDataMem(LPSTR szMemName, s32 nType, SQLTypeAdapter &vtMem)
{
	try
	{
		LPSTR		pInBuf = m_pInData;
		s32			i = 0;
		s32			lX = 0;

		list<INPUTSTRUCTMEM>::iterator	it = m_pRequestConfig->InputStructMemList.begin();
		for (; it != m_pRequestConfig->InputStructMemList.end(); ++ it)
		{
			INPUTSTRUCTMEM	*pInputStructMem = &(*it);
			if (0 == strcmp(pInputStructMem->szName, szMemName))
			{
				switch(nType)
				{
				case adTinyInt:
					vtMem = SQLTypeAdapter((*((signed char*)pInBuf)));
					return TRUE;

				case adSmallInt:
					vtMem = SQLTypeAdapter((*((short*)pInBuf)));
					return TRUE;

				case adInteger:
					vtMem = SQLTypeAdapter((*((int*)pInBuf)));
					return TRUE;

				case adBigInt:
					vtMem = SQLTypeAdapter((*((s64*)pInBuf)));
					return TRUE;

				case adDouble:
					vtMem = SQLTypeAdapter((*((double*)pInBuf)));
					return TRUE;

				case adChar:
				case adVarChar:
				case adBinary:
				case adVarBinary:
          {
            u32 dwEscapedLen = m_pDBADO->EscapeString(m_EscapeStringBuffer, pInBuf, pInputStructMem->nLen);
            vtMem = SQLTypeAdapter(m_EscapeStringBuffer, (int)dwEscapedLen);
            return TRUE;
          }
				default:
					return FALSE;
				}
			}

			pInBuf += pInputStructMem->nLen;
		}
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

// ��ȡ������ݳ���
s32 CAsynObject::GetOutDataLen(void)
{
	try
	{
		s32	nOutDataLen = 0;

		list<OUTPUTSTRUCTMEM>::iterator	itOutputStructMem = m_pRequestConfig->OutputStructMemList.begin();
		for (; itOutputStructMem != m_pRequestConfig->OutputStructMemList.end(); ++ itOutputStructMem)
		{
			OUTPUTSTRUCTMEM	*pOutputStructMem = &(*itOutputStructMem);
			nOutDataLen += pOutputStructMem->nLen;
		}

		if (TRUE == m_pRequestConfig->bRecordset)
		{
			s32	nOutputStructForRstNum = m_pDBADO->GetRecordCount();
			if (nOutputStructForRstNum < 0)
			{
				return -1;
			}

			s32	nOutputStructForRstSize = 0;
			list<OUTPUTSTRUCTMEM>::iterator	itOutputStructMemForRst = m_pRequestConfig->OutputStructMemForRstList.begin();
			for (; itOutputStructMemForRst != m_pRequestConfig->OutputStructMemForRstList.end(); ++ itOutputStructMemForRst)
			{
				OUTPUTSTRUCTMEM	*pOutputStructMemForRst = &(*itOutputStructMemForRst);
				nOutputStructForRstSize += pOutputStructMemForRst->nLen;
			}

			nOutDataLen += nOutputStructForRstSize * nOutputStructForRstNum;
		}

		return nOutDataLen;
	}
	catch (...)
	{
		return -1;
	}

	return -1;
}

// ��дֱͨ���ݵ����������, ע������ֽڶ�������
LPSTR CAsynObject::PutOutDataMemForStruct(LPSTR pOutData, LPSTR szMemName, s32 nMemLen)
{
	try
	{
		char *pInBuf = m_pInData;
		list<INPUTSTRUCTMEM>::iterator	itInputStructMem = m_pRequestConfig->InputStructMemList.begin();
		for (; itInputStructMem != m_pRequestConfig->InputStructMemList.end(); ++ itInputStructMem)
		{
			INPUTSTRUCTMEM	*pInputStructMem = &(*itInputStructMem);
			if (0 == strcmp(pInputStructMem->szName, szMemName))
			{
				memcpy(pOutData, pInBuf, nMemLen);
				pOutData += nMemLen;
				return pOutData;
			}

			pInBuf += pInputStructMem->nLen;
		}
	}
	catch (...)
	{
		return NULL;
	}

	return NULL;
}

// ��дVT���ݵ����������, ע������ֽڶ�������
LPSTR CAsynObject::PutOutDataMemForVT(LPSTR pOutData, String &vtMem, s32 nLen)
{
	try
	{
		u8	bTinyInt = 0;
		s16	nSmallInt = 0;
		s32	nInteger = 0;
		float fFloat = 0.0f;
		s64	nInt64 = 0;
		double	dDouble = 0.0f;

		s32		i = 0;
		s32		lX = 0;
		char	*pOutDataTemp = pOutData;


		LPCSTR szSqlName = vtMem.type().sql_name();
    size_t vtMemSize = vtMem.length();

    if(strcmp(szSqlName, "TINYINT NULL") == 0 || strcmp(szSqlName, "TINYINT NOT NULL") == 0)
    {
      if(vtMem == "NULL")
      {
        bTinyInt = 0;
      }
      else
      {
        bTinyInt = (u8)vtMem;
      }
      memcpy(pOutData, &bTinyInt, nLen);
    }
    else if(vtMem.type().c_type() == typeid(s16) || vtMem.type().c_type() == typeid(u16) || strcmp(szSqlName, "SMALLINT NULL") == 0 || strcmp(szSqlName, "SMALLINT NOT NULL") == 0)
    {
      if(vtMem == "NULL")
        nSmallInt = 0;
      else
        nSmallInt = (s16)vtMem;
      memcpy(pOutData, &nSmallInt, nLen);
    }
    else if(vtMem.type().c_type() == typeid(s32) || vtMem.type().c_type() == typeid(u32) || strcmp(szSqlName, "INT NULL") == 0 || strcmp(szSqlName, "INT NOT NULL") == 0)
    {
      if(vtMem == "NULL")
        nInteger = 0;
      else
        nInteger = (s32)vtMem;
      memcpy(pOutData, &nInteger, nLen);
    }
    else if(vtMem.type().c_type() == typeid(float) || strcmp(szSqlName, "FLOAT NULL") == 0 || strcmp(szSqlName, "FLOAT NOT NULL") == 0)
    {
      if(vtMem == "NULL")
        fFloat = 0.0f;
      else
        fFloat = (float)vtMem;
      memcpy(pOutData, &fFloat, nLen);
    }
    else if(vtMem.type().c_type() == typeid(s64) || vtMem.type().c_type() == typeid(u64) || strcmp(szSqlName, "BIGINT NULL") == 0 || strcmp(szSqlName, "BIGINT NOT NULL") == 0)
    {
      if(vtMem == "NULL")
        nInt64 = 0;
      else
        nInt64 = (s64)vtMem;
      memcpy(pOutData, &nInt64, nLen);
    }
    else if(vtMem.type().c_type() == typeid(double) || strcmp(szSqlName, "DOUBLE NULL") == 0 || strcmp(szSqlName, "DOUBLE NOT NULL") == 0)
    {
      if(vtMem == "NULL")
        dDouble = 0.0f;
      else
        dDouble = (double)vtMem;
      memcpy(pOutData, &dDouble, nLen);
    }
		else if(strcmp(szSqlName, "CHAR NULL") == 0 || strcmp(szSqlName, "VARCHAR NULL") == 0 || strcmp(szSqlName, "BLOB NULL") == 0)
		{
			memset(pOutData, 0, nLen);
      // memcpy(pOutData, (LPSTR)(vtMem.data()), nLen);
      if(nLen > (int)vtMemSize)
      {
        memcpy(pOutData, (LPSTR)(vtMem.data()), vtMemSize);
      }
      else
      {
        memcpy(pOutData, (LPSTR)(vtMem.data()), nLen);
      }
		}
		else if(strcmp(szSqlName, "CHAR NOT NULL") == 0 || strcmp(szSqlName, "VARCHAR NOT NULL") == 0 || strcmp(szSqlName, "BLOB NOT NULL") == 0)
		{
			memset(pOutData, 0, nLen);
			// memcpy(pOutData, (LPSTR)(vtMem.data()), nLen);
      if(nLen > (int)vtMemSize)
      {
        memcpy(pOutData, (LPSTR)(vtMem.data()), vtMemSize);
      }
      else
      {
        memcpy(pOutData, (LPSTR)(vtMem.data()), nLen);
      }
    }
		else
		{
			cout << "CAsynObject::PutOutDataMemForVT error type! szSqlName=" << szSqlName << endl << endl;
			return NULL;
		}
		pOutData += nLen;
		return pOutData;
	}
	catch (...)
	{
		return NULL;
	}

	return NULL;
}

