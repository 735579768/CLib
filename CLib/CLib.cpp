// CLib.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#include "CLib.h"

namespace Ainiku {
	// ���ǵ���������һ��ʾ��
	AINIKU_API int nCLib = 0;

	// ���ǵ���������һ��ʾ����
	AINIKU_API int fnCLib(void)
	{
		return 42;
	}
	AINIKU_API char* echo() {
		return "��������������";
	}

	// �����ѵ�����Ĺ��캯����
	// �й��ඨ�����Ϣ������� CLib.h
	CCLib::CCLib()
	{
		return;
	}
}
