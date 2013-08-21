#include "Header.h"
#include "DBADO.h"

// 构造函数
CDBADO::CDBADO()
: m_Query(m_pConnection)
{
	m_pConnection = NULL;
	m_pAsynObjectList = NULL;
}

// 析构函数
CDBADO::~CDBADO()
{
}

// 创建数据库访问
BOOL CDBADO::Create(void)
{
	if (m_pConnection != NULL)
	{
		return FALSE;
	}

	try
	{
		// 创建一个mysql链接
		m_pConnection = new Connection(false);
		// 只支持存储过程调用
		m_pConnection->set_option(new mysqlpp::MultiStatementsOption(CLIENT_MULTI_STATEMENTS));
		// 设置字符集
		m_pConnection->set_option(new mysqlpp::SetCharsetNameOption("GBK"));
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

// 关闭数据库访问
void CDBADO::Close(void)
{
	// 与mysql server断开链接
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

// 连接数据库
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
		g_pDBEngine->PrintInfoLog("连接数据库DataSource = %s, DBName=%s成功\n", szDataSource, szDBName);
		m_Query = m_pConnection->query();
	}
	catch (BadQuery& er)
	{
		g_pDBEngine->PrintInfoLog("连接数据库失败!\n  错误=%s\n", er.what());
		return FALSE;
	}
	catch(...)
	{
		return FALSE;
	}

	return TRUE;
}

// 断开数据库连接
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

// 数据库是否已经连接
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
		// 执行一个简单SQL语句, 以便明确是否出现错误
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
		// 断开当前连接
		Disconnect();
		return FALSE;
	}

	return TRUE;
}

// 设置当前存储过程名
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

// 清除当前命令的所有参数 
BOOL CDBADO::ClearParam(void)
{
	try
	{
		// 重置QUERY
		m_Query.reset();
		m_dwCurResultIndex = 0;
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

// 添加一个参数到当前命令中
BOOL CDBADO::AddParam(SQLTypeAdapter& staParam, DataTypeEnum type, u32 dwParamIndex, u32 dwTotalParam)
{
	if(0 == dwTotalParam || dwParamIndex > dwTotalParam)
	{
		return FALSE;
	}

	try
	{
		// 不是第一个参数
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
		// 是最后一个参数
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

// 执行命令并返回记录集
int CDBADO::OpenRecordset(void)
{
	try
	{
		if (FALSE == CloseRecordset())
		{
      g_pDBEngine->PrintInfoLog("OpenRecordset时，CloseRecordset返回FALSE");
			return -1;
		}

		m_StoreQueryResult = m_Query.store();

		if (m_Query.errnum() > 0)
		{
			g_pDBEngine->PrintInfoLog("执行存储错误!\n  存储过程名=%s\n  错误描述=%s\n",
				(m_Query.str()).c_str(), m_Query.error());
			// 如果当前连接已断开则要进行重连, 直到连上为止
			if (FALSE == IsConnected())
			{
				// 报警: 数据库断开
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

				// 报警: 数据库恢复正常
				if (m_pAsynObjectList != NULL)
				{
					m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
				}

				// 再次调用本函数执行未完成的命令
				// returna OpenRecordset();
        return 0;
			}
			return -1;
		}
	}
	catch (BadQuery& er)
	{
		g_pDBEngine->PrintInfoLog("执行存储异常!存储过程名=%s\n  错误=%s\n",
			(m_Query.str()).c_str(), er.what());

		// 如果当前连接已断开则要进行重连, 直到连上为止
		if (FALSE == IsConnected())
		{
			// 报警: 数据库断开
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

			// 报警: 数据库恢复正常
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
			}

			// 再次调用本函数执行未完成的命令
			// return OpenRecordset();
      return 0;
		}

		return -1;
	}
	catch (...)
	{
		// 如果当前连接已断开则要进行重连, 直到连上为止
		if (FALSE == IsConnected())
		{
			// 报警: 数据库断开
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

			// 报警: 数据库恢复正常
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
			}

			// 再次调用本函数执行未完成的命令
			// return OpenRecordset();
      return 0;
		}

		return -1;
	}

	return 1;
}

// 关闭结果集
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

// 结果集是否已打开
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

// 获取结果集中结果的个数
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

// 下一条结果
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

// 获取结果集结束标志
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

// 执行命令不返回记录集
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
			g_pDBEngine->PrintInfoLog("执行存储错误!\n  存储过程名=%s\n  错误描述=%s\n",
				(m_Query.str()).c_str(), m_Query.error());
			// 如果当前连接已断开则要进行重连, 直到连上为止
			if (FALSE == IsConnected())
			{
				// 报警: 数据库断开
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

				// 报警: 数据库恢复正常
				if (m_pAsynObjectList != NULL)
				{
					m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
				}

				// 再次调用本函数执行未完成的命令
				// return OpenNoRecordset();
        return 0;
			}
			return -1;
		}
	}
	catch (BadQuery& er)
	{
		g_pDBEngine->PrintInfoLog("执行存储异常!\n  存储过程名=%s\n  错误=%s\n",
			(m_Query.str()).c_str(), er.what());

		// 如果当前连接已断开则要进行重连, 直到连上为止
		if (FALSE == IsConnected())
		{
			// 报警: 数据库断开
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

			// 报警: 数据库恢复正常
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
			}

			// 再次调用本函数执行未完成的命令
			// return OpenNoRecordset();
      return 0;
		}

		return -1;
	}
	catch (...)
	{
		// 如果当前连接已断开则要进行重连, 直到连上为止
		if (FALSE == IsConnected())
		{
			// 报警: 数据库断开
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

			// 报警: 数据库恢复正常
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
			}

			// 再次调用本函数执行未完成的命令
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
		g_pDBEngine->PrintInfoLog("执行存储失败!\n  存储过程名=%s\n  描述=%s\n  错误=%s\n  代码=%08lx\n  错误源=%s",
			(LPSTR)m_Command->CommandText, (LPSTR)e.Description(), (LPSTR)e.ErrorMessage(),
			e.Error(), (LPSTR)e.Source());

		// 如果当前连接已断开则要进行重连, 直到连上为止
		if (FALSE == IsConnected())
		{
			// 报警: 数据库断开
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_DISCONNECTED);
			}

			while (FALSE == IsConnected())
			{
				Connect();
				Sleep(1000);
			}

			// 报警: 数据库恢复正常
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
			}

			// 再次调用本函数执行未完成的命令
			return OpenNoRecordset();
		}

		return FALSE;
	}
	catch (...)
	{
		// 如果当前连接已断开则要进行重连, 直到连上为止
		if (FALSE == IsConnected())
		{
			// 报警: 数据库断开
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_DISCONNECTED);
			}

			while (FALSE == IsConnected())
			{
				Connect();
				Sleep(1000);
			}

			// 报警: 数据库恢复正常
			if (m_pAsynObjectList != NULL)
			{
				m_pAsynObjectList->OnWarning(DBWARN_CONNECTED);
			}

			// 再次调用本函数执行未完成的命令
			return OpenNoRecordset();
		}

		return FALSE;
	}
	*/

	return 1;
}

// 获取命令执行后参数的值
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

// 获取命令执行后域的值
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

// 设置所属异步队列指针
void CDBADO::SetAsynObjectList(CAsynObjectList *pAsynObjectList)
{
	m_pAsynObjectList = pAsynObjectList;
}

// 转义字符串
u32 CDBADO::EscapeString(char* szEscaped, const char* szOriginal, u32 dwLen)
{
	return m_Query.escape_string(szEscaped, szOriginal, dwLen);
}
