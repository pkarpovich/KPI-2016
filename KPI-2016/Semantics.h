#pragma once

namespace MA
{
	void isIndef(Error::ErrorTable&, LA::LexAnaliz, char*, char*);			// �� ��������� �� �������������
	void isRedefinition(Error::ErrorTable&, LA::LexAnaliz, char*, char*);	// ���������������
	void isBigId(Error::ErrorTable&, int , char *);							// ������� ������� ��� �������
	void isZeroDivision(Error::ErrorTable&, LA::LexAnaliz, char*);			// ������� �� ����no
	void isStrFunc(Error::ErrorTable&, LA::LexAnaliz);						// ���������� ������������ ��� � �������
	void isTrueParamCount(Error::ErrorTable&, LA::LexAnaliz);				// ���������� ���-�� ���������� � ���. �������
	void isStrAction(Error::ErrorTable&, LA::LexAnaliz);
	void isSoBigValue(Error::ErrorTable&, LA::LexAnaliz,char*);
}