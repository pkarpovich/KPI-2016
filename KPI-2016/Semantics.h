#pragma once

namespace MA
{
	void isIndef(LA::LexAnaliz, char*, char*);			// �� ��������� �� �������������
	void isRedefinition(LA::LexAnaliz, char*, char*);	// ���������������
	void isBigId(int , char *);							// ������� ������� ��� �������
	void isZeroDivision(LA::LexAnaliz, char*);			// ������� �� ����no
	void isStrFunc(LA::LexAnaliz);						// ���������� ������������ ��� � �������
	void isTrueParamCount(LA::LexAnaliz);				// ���������� ���-�� ���������� � ���. �������
	void isStrAction(LA::LexAnaliz);
}