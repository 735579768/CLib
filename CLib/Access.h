/**ʹ�÷���
 *		_RecordsetPtr rs= db->GetRs("select * from list");
		if(rs){
			while (!rs->rsEOF)
			{
				CString idstr=(LPCTSTR)(_bstr_t)(rs->Fields->GetItem("id")->Value);
				CString ipstr=(LPCTSTR)(_bstr_t)(rs->Fields->GetItem("ip")->Value);
			}
 */
#ifndef __LIB_ACCESS_H__
#define __LIB_ACCESS_H__
#include "stdafx.h"
#include <string>
//#import "C://Program Files//Common Files//System//ado//msado15.dll" 
#import "C:\\Program Files\\Common Files\\System\\ado\\msado15.dll" no_namespace rename("EOF","rsEOF")
namespace Ainiku
{
	using namespace std;
	class AINIKU_API CAccess
	{
	public:
		CAccess(void);
		//�õ����ݼ�
		_RecordsetPtr GetRs(CString strSql);
		//ִ��SQL���
		bool ExecuteSql(CString& strSql);
		//ͨ��idȡ������¼��һ���ֶ�
		string getByfield(string table, string id, string field);
	public:
		~CAccess(void);
	private:
		_ConnectionPtr m_conn;
		_RecordsetPtr m_rs;

	};
}

#endif