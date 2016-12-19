#pragma once

namespace MA
{
	void isIndef(LA::LexAnaliz, char*, char*);			// не определен но используеться
	void isRedefinition(LA::LexAnaliz, char*, char*);	// переопределение
	void isBigId(int , char *);							// слишком большое имя функции
	void isZeroDivision(LA::LexAnaliz, char*);			// деление на нольno
	void isStrFunc(LA::LexAnaliz);						// запрещенно использовать стр в функции
	void isTrueParamCount(LA::LexAnaliz);				// правильное кол-во параметров в выз. функции
	void isStrAction(LA::LexAnaliz);
}