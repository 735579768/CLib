// Testdll.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace Ainiku;
using namespace std;
int main()
{
	//CString str= Ainiku::getUrl("http://www.zhaokeli.com");
	//setlocale(LC_TIME, "chs");
	//cout << wstring2string(str.GetBuffer(0)).c_str() <<endl;
	CAnkLog::getInstance()->write("��־��¼");
	ofstream ofs( "test", std::ios::binary);//����ofstream����
	ofs.write("aaa",strlen("aaa"));
	ofs.close();
	ANKString str = "aaabbb�Ұ���";
	str.replace("b","a");
	str.replace("�Ұ�","��");
	CString chr = "��";
	//�����ַ���
	cout << str.find(chr) << endl;
	cout << str.getChar() << endl;
	getchar();
    return 0;
}

