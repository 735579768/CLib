#pragma once
#include "Access.h"
namespace Ainiku {
	CAccess::CAccess(void)
	{
		//��ʼ��COM
		::CoInitialize(NULL);
		try
		{
			try {
				if (FAILED(m_conn.CreateInstance("ADODB.Connection")))
				{
					::MessageBox(NULL, _T("Create Instance failed!"), _T("����"), MB_ICONEXCLAMATION);
					return;
				}

				CString conn = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=E:/VS/vc++/YuanCheng/YuanCheng/bin/data/data.mdb";
				//CString conn = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=./bin/data/data.mdb";
				//SQL SERVER�����ַ���
				//CString conn="Driver={SQL Server};server=(local);uid=sa;database=pubs";//local���Ը�Ϊ127.0.0.1
				if (FAILED(m_conn->Open((_bstr_t)conn, "", "", -1)))
				{
					::MessageBox(NULL, _T("���ݿ�����ʧ��"), _T("����"), MB_ICONEXCLAMATION);
					return;
				}
			}
			catch (_com_error &e) {
				::MessageBox(NULL, e.Description(), _T("����"), MB_ICONEXCLAMATION);
			}
		}
		catch (...)
		{
			::MessageBox(NULL, _T("���ݿ����ӳ����쳣"), _T("����"), MB_ICONEXCLAMATION);
		}

	}

	CAccess::~CAccess(void)
	{
		//if(m_rs!=NULL)
		m_rs->Close();
		m_rs.Release();
		m_conn->Close();
		m_conn.Release();
		::CoUninitialize();
	}
	_RecordsetPtr CAccess::GetRs(CString strSql)
	{
		try
		{
			m_rs.CreateInstance("ADODB.Recordset");
			m_rs = m_conn->Execute((_bstr_t)strSql, NULL, adCmdText);
		}
		catch (...)
		{
			return NULL;
		}
		return m_rs;
	}
	string CAccess::getByfield(string table, string id, string field) {
		string sql = "select top 1 " + field + " from " + table + " where id=" + id;
		GetRs(CString(sql.c_str()));
		if (m_rs) {
			string str = (char*)(LPCTSTR)(_bstr_t)(m_rs->Fields->GetItem(field.c_str())->Value);
			return str;
		}
		else {
			return NULL;
		}
	}
	bool CAccess::ExecuteSql(CString& strSql)
	{
		try
		{
			m_conn->Execute((_bstr_t)strSql, NULL, adCmdText);
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
}