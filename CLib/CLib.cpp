// CLib.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "CLib.h"


// ���ǵ���������һ��ʾ��
CLIB_API int nCLib=0;

// ���ǵ���������һ��ʾ����
CLIB_API int fnCLib(void)
{
    return 42;
}
CLIB_API char* echo() {
	return "��������������";
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� CLib.h
CCLib::CCLib()
{
    return;
}
