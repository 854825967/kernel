#include "Header.h"
#include "DBADO.h"

// ���캯��
CDBADO::CDBADO()
: m_Query(m_pConnection)
{
	m_pConnection = NULL;
	m_pAsynObjectList = NULL;
}

// ��������
CDBADO::~CDBADO()
{
}

// �������ݿ����
BOOL CDBADO::Create(void)
{
	if (m_pConnection != NULL)
	{
		return FALSE;
	}

	try
	{
		// ����һ��mysql����
		m_pConnection = new Connection(false);
		// ֻ֧�ִ洢���̵���
		m_pConnection->set_option(new mysqlpp::MultiStatementsOption(CLIENT_MULTI_STATEMENTS));
		// �����ַ���
		m_pConnection->set_option(new mysqlpp::SetCharsetNameOption("GBK"));
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

// �ر����ݿ����
void CDBADO::Close(void)
{
	// ��mysql server�Ͽ�����
	Disconnect();
	m_pAsynObjectList = NULL;
	try
	{
		if( NULL != m_pConnection )
		{
			delete m_pConnection;
			m_pConnection = NULL;
		}
	}
	catch (...)
	{
	}
}

// �������ݿ�
BOOL CDBADO::Connect(LPSTR szDataSource, s32 nServerPort, LPSTR szDBName, LPSTR szUser, LPSTR szPwd)
{
	try
	{
		if (NULL == m_pConnection || m_pConnection->connected())
		{
			return FALSE;
		}

		if (!(m_pConnection->connect(szDBName, szDataSource, szUser, szPwd, nServerPort)))
		{
      g_pDBEngine->PrintInfoLog("connect error = %s", m_pConnection->error());
			return FALSE;
		}
		m_strDataSource = szDataSource;
		m_nPort = nServerPort;
		m_strDBName = szDBName;
		m_strUserName = szUser;
		m_strPwd = szPwd;
		g_pDBEngine->PrintInfoLog("�������ݿ�DataSource = %s, DBName=%s�ɹ�\n", szDataSource, szDBName);
		m_Query = m_pConnection->query();
	}
	catch (BadQuery& er)
	{
		g_pDBEngine->PrintInfoLog("�������ݿ�ʧ��!\n  ����=%s\n", er.what());
		return FALSE;
	}
	catch(...)
	{
		return FALSE;
	}

	return TRUE;
}

// �Ͽ����ݿ�����
BOOL CDBADO::Disconnect(void)
{
	try
	{
		if (NULL != m_pConnection && m_pConnection->connected())
		{
			m_pConnection->disconnect();
		}
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

// ���ݿ��Ƿ��Ѿ�����
BOOL CDBADO::IsConnected(void)
{
	try
	{
		if (NULL == m_pConnection || !(m_pConnection->connected()))
		{
			return FALSE;
		}
	}
	catch (...)
	{
		return FALSE;
	}

	try
	{
		// ִ��һ����SQL���, �Ա���ȷ�Ƿ���ִ���
    m_Query.reset();
    m_Query << "call test();";
    m_Query.store();
    if(m_Query.errnum() > 0) {
      Disconnect();
      return FALSE;
    } else {
      if(m_Query.more_results()) {
        m_Query.store_next();
      }
    }
    /*
    m_Query = m_pConnection->query();
		if(m_Query.exec("select 1") == false) {
      Disconnect();
      return FALSE;
    }
    */
	}
	catch (...)
	{
		// �Ͽ���ǰ����
		Disconnect();
		return FALSE;
	}

	return TRUE;
}

// ���õ�ǰ�洢������
BOOL CDBADO::SetSPName(LPCSTR szSPName)
{
	if (NULL == szSPName)
	{
		return FALSE;
	}

	try
	{
		// exp:call PrGs_Test(
		m_Query << "call " << szSPName << "(";
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

// �����ǰ��������в��� 
BOOL CDBADO::ClearParam(void)
{
	try
	{
		// ����QUERY
		m_Query.reset();
		m_dwCurResultIndex = 0;
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

// ���һ����������ǰ������
BOOL CDBADO::AddParam(SQLTypeAdapter& staParam, DataTypeEnum type, u32 dwParamIndex, u32 dwTotalParam)
{
	if(0 == dwTotalParam || dwParamIndex > dwTotalParam)
	{
		return FALSE;
	}

	try
	{
		// ���ǵ�һ������
		if( dwParamIndex > 1 )
		{
			m_Query << ", ";
		}
		if(type == adChar || type == adVarChar || type == adBinary || type == adVarBinary )
		{
			m_Query << "\"";
		}
		m_Query << staParam;
		if(type == adChar || type == adVarChar || type == adBinary || type == adVarBinary )
		{
			m_Query << "\"";
		}
		// �����һ������
		if( dwParamIndex == dwTotalParam )
		{
			m_Query << ")";
		}
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

// ִ��������ؼ�¼��
int CDBADO::OpenRecordset(void)
{
	try
	{
		if (FALSE == CloseRecordset())
		{
      g_pDBEngine->PrintInfoLog("OpenRecordsetʱ��CloseRecordset����FALSE");
			return -1;
		}

		m_StoreQueryResult = m_Query.store();

		if (m_Query.errnum() > 0)
		{
			g_pDBEngine->PrintInfoLog("ִ�д洢����!\n  �洢������=%s\n  ��������=%s\n",
				(m_Query.str()).c_str(), m_Query.error());
			// �����ǰ�����ѶϿ���Ҫ��������, ֱ������Ϊֹ
			if (FALSE == IsConnected())
			{
				// ����: ���ݿ�Ͽ�
				if (m_pAsynObjectList != NULL)
				{
					m_pAsynObjectList->OnWarning(DBWARN_DISCONNECTED);
				}

				while (FALSE == IsConnected())
				{
          m_pConnection->set_option(new mysqlpp::SetCharsetNameOption("GBK"));
          m_pConnection->set_option(new mysqlpp::MultiStatementsOption(CLIENT_MULTI_STATEMENTS));
					Connect((LPSTR)(m_strDataSource.c_str()), m_nPort, (LPSTR)(m_strDBName.c_str()), (LPSTR)(m_strUserName.c_str()), (LPSTR)(m_strPwd.c_str()));
					sleep(1);
				}

				// ����: ���ݿ�ָ�����
				if (m_pAsynObjectList != NULL)
				{
					m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
				}

				// �ٴε��ñ�����ִ��δ��ɵ�����
				// returna OpenRecordset();
        return 0;
			}
			return -1;
		}
	}
	catch (BadQuery& er)
	{
		g_pDBEngine->PrintInfoLog("ִ�д洢�쳣!�洢������=%s\n  ����=%s\n",
			(m_Query.str()).c_str(), er.what());

		// �����ǰ�����ѶϿ���Ҫ��������, ֱ������Ϊֹ
		if (FALSE == IsConnected())
		{
			// ����: ���ݿ�Ͽ�
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_DISCONNECTED);
			}

			while (FALSE == IsConnected())
			{
        m_pConnection->set_option(new mysqlpp::SetCharsetNameOption("GBK"));
        m_pConnection->set_option(new mysqlpp::MultiStatementsOption(CLIENT_MULTI_STATEMENTS));
				Connect((LPSTR)(m_strDataSource.c_str()), m_nPort, (LPSTR)(m_strDBName.c_str()), (LPSTR)(m_strUserName.c_str()), (LPSTR)(m_strPwd.c_str()));
				sleep(1);
			}

			// ����: ���ݿ�ָ�����
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
			}

			// �ٴε��ñ�����ִ��δ��ɵ�����
			// return OpenRecordset();
      return 0;
		}

		return -1;
	}
	catch (...)
	{
		// �����ǰ�����ѶϿ���Ҫ��������, ֱ������Ϊֹ
		if (FALSE == IsConnected())
		{
			// ����: ���ݿ�Ͽ�
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_DISCONNECTED);
			}

			while (FALSE == IsConnected())
			{
        m_pConnection->set_option(new mysqlpp::SetCharsetNameOption("GBK"));
        m_pConnection->set_option(new mysqlpp::MultiStatementsOption(CLIENT_MULTI_STATEMENTS));
				Connect((LPSTR)(m_strDataSource.c_str()), m_nPort, (LPSTR)(m_strDBName.c_str()), (LPSTR)(m_strUserName.c_str()), (LPSTR)(m_strPwd.c_str()));
				sleep(1);
			}

			// ����: ���ݿ�ָ�����
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
			}

			// �ٴε��ñ�����ִ��δ��ɵ�����
			// return OpenRecordset();
      return 0;
		}

		return -1;
	}

	return 1;
}

// �رս����
BOOL CDBADO::CloseRecordset(void)
{
	try
	{
		while(m_Query.more_results())
		{
			m_Query.store_next();
		}
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

// ������Ƿ��Ѵ�
BOOL CDBADO::IsRecordsetOpened(void)
{
	try
	{
		if (m_StoreQueryResult.num_rows() <= 0)
		{
			return FALSE;
		}
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

// ��ȡ������н���ĸ���
int CDBADO::GetRecordCount(void)
{
	try
	{
		return m_StoreQueryResult.num_rows();
	}
	catch (...)
	{
		return -1;
	}

	return -1;
}

// ��һ�����
BOOL CDBADO::RecordsetNext(void)
{
	try
	{
		m_dwCurResultIndex++;
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

// ��ȡ�����������־
BOOL CDBADO::IsRecordsetEOF(void)
{
	try
	{
		return (m_StoreQueryResult.num_rows() <= m_dwCurResultIndex);
	}
	catch (...)
	{
		return FALSE;
	}

	return FALSE;
}

// ִ��������ؼ�¼��
int CDBADO::OpenNoRecordset(void)
{
	try
	{
		if (FALSE == CloseRecordset())
		{
			return -1;
		}

		m_StoreQueryResult = m_Query.store();
		if (m_Query.errnum() > 0)
		{
			g_pDBEngine->PrintInfoLog("ִ�д洢����!\n  �洢������=%s\n  ��������=%s\n",
				(m_Query.str()).c_str(), m_Query.error());
			// �����ǰ�����ѶϿ���Ҫ��������, ֱ������Ϊֹ
			if (FALSE == IsConnected())
			{
				// ����: ���ݿ�Ͽ�
				if (m_pAsynObjectList != NULL)
				{
					m_pAsynObjectList->OnWarning(DBWARN_DISCONNECTED);
				}

				while (FALSE == IsConnected())
				{
          m_pConnection->set_option(new mysqlpp::SetCharsetNameOption("GBK"));
          m_pConnection->set_option(new mysqlpp::MultiStatementsOption(CLIENT_MULTI_STATEMENTS));
					Connect((LPSTR)(m_strDataSource.c_str()), m_nPort, (LPSTR)(m_strDBName.c_str()), (LPSTR)(m_strUserName.c_str()), (LPSTR)(m_strPwd.c_str()));
					sleep(1);
				}

				// ����: ���ݿ�ָ�����
				if (m_pAsynObjectList != NULL)
				{
					m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
				}

				// �ٴε��ñ�����ִ��δ��ɵ�����
				// return OpenNoRecordset();
        return 0;
			}
			return -1;
		}
	}
	catch (BadQuery& er)
	{
		g_pDBEngine->PrintInfoLog("ִ�д洢�쳣!\n  �洢������=%s\n  ����=%s\n",
			(m_Query.str()).c_str(), er.what());

		// �����ǰ�����ѶϿ���Ҫ��������, ֱ������Ϊֹ
		if (FALSE == IsConnected())
		{
			// ����: ���ݿ�Ͽ�
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_DISCONNECTED);
			}

			while (FALSE == IsConnected())
			{
        m_pConnection->set_option(new mysqlpp::SetCharsetNameOption("GBK"));
        m_pConnection->set_option(new mysqlpp::MultiStatementsOption(CLIENT_MULTI_STATEMENTS));
				Connect((LPSTR)(m_strDataSource.c_str()), m_nPort, (LPSTR)(m_strDBName.c_str()), (LPSTR)(m_strUserName.c_str()), (LPSTR)(m_strPwd.c_str()));
				sleep(1);
			}

			// ����: ���ݿ�ָ�����
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
			}

			// �ٴε��ñ�����ִ��δ��ɵ�����
			// return OpenNoRecordset();
      return 0;
		}

		return -1;
	}
	catch (...)
	{
		// �����ǰ�����ѶϿ���Ҫ��������, ֱ������Ϊֹ
		if (FALSE == IsConnected())
		{
			// ����: ���ݿ�Ͽ�
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_DISCONNECTED);
			}

			while (FALSE == IsConnected())
			{
        m_pConnection->set_option(new mysqlpp::SetCharsetNameOption("GBK"));
        m_pConnection->set_option(new mysqlpp::MultiStatementsOption(CLIENT_MULTI_STATEMENTS));
				Connect((LPSTR)(m_strDataSource.c_str()), m_nPort, (LPSTR)(m_strDBName.c_str()), (LPSTR)(m_strUserName.c_str()), (LPSTR)(m_strPwd.c_str()));
				sleep(1);
			}

			// ����: ���ݿ�ָ�����
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
			}

			// �ٴε��ñ�����ִ��δ��ɵ�����
			// return OpenNoRecordset();
      return 0;
		}

		return -1;
	}
	/*
	try
	{
		m_Command->Execute(NULL, NULL, adExecuteNoRecords);
	}
	catch (_com_error &e)
	{
		g_pDBEngine->PrintInfoLog("ִ�д洢ʧ��!\n  �洢������=%s\n  ����=%s\n  ����=%s\n  ����=%08lx\n  ����Դ=%s",
			(LPSTR)m_Command->CommandText, (LPSTR)e.Description(), (LPSTR)e.ErrorMessage(),
			e.Error(), (LPSTR)e.Source());

		// �����ǰ�����ѶϿ���Ҫ��������, ֱ������Ϊֹ
		if (FALSE == IsConnected())
		{
			// ����: ���ݿ�Ͽ�
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_DISCONNECTED);
			}

			while (FALSE == IsConnected())
			{
				Connect();
				Sleep(1000);
			}

			// ����: ���ݿ�ָ�����
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
			}

			// �ٴε��ñ�����ִ��δ��ɵ�����
			return OpenNoRecordset();
		}

		return FALSE;
	}
	catch (...)
	{
		// �����ǰ�����ѶϿ���Ҫ��������, ֱ������Ϊֹ
		if (FALSE == IsConnected())
		{
			// ����: ���ݿ�Ͽ�
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_DISCONNECTED);
			}

			while (FALSE == IsConnected())
			{
				Connect();
				Sleep(1000);
			}

			// ����: ���ݿ�ָ�����
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
			}

			// �ٴε��ñ�����ִ��δ��ɵ�����
			return OpenNoRecordset();
		}

		return FALSE;
	}
	*/

	return 1;
}

// ��ȡ����ִ�к������ֵ
BOOL CDBADO::GetParamValue(LPSTR szName, String &vtValue)
{
	if (NULL == szName)
	{
		return FALSE;
	}

	try
	{
		//vtValue.Clear();
		//vtValue = m_Command->Parameters->Item[szName]->Value;
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

// ��ȡ����ִ�к����ֵ
BOOL CDBADO::GetFieldValue(LPSTR szName, String &vtValue)
{
	if (NULL == szName)
	{
		return FALSE;
	}
	try
	{
		vtValue = m_StoreQueryResult[m_dwCurResultIndex][szName];
	}
	catch(...)
	{
		return FALSE;
	}
	return TRUE;
}

// ���������첽����ָ��
void CDBADO::SetAsynObjectList(CAsynObjectList *pAsynObjectList)
{
	m_pAsynObjectList = pAsynObjectList;
}

// ת���ַ���
u32 CDBADO::EscapeString(char* szEscaped, const char* szOriginal, u32 dwLen)
{
	return m_Query.escape_string(szEscaped, szOriginal, dwLen);
}
