/**使用方法
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
		//得到数据集
		_RecordsetPtr GetRs(CString strSql);
		//执行SQL语句
		bool ExecuteSql(CString& strSql);
		//通过id取单个记录的一个字段
		string getByfield(string table, string id, string field);
	public:
		~CAccess(void);
	private:
		_ConnectionPtr m_conn;
		_RecordsetPtr m_rs;

	};
}

#endif