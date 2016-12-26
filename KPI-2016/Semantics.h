#pragma once

namespace MA
{
	void isIndef(Error::ErrorTable&, LA::LexAnaliz, char*, char*);			// не определен но используеться
	void isRedefinition(Error::ErrorTable&, LA::LexAnaliz, char*, char*);	// переопределение
	void isBigId(Error::ErrorTable&, int , char *);							// слишком большое имя функции
	void isZeroDivision(Error::ErrorTable&, LA::LexAnaliz, char*);			// деление на нольno
	void isStrFunc(Error::ErrorTable&, LA::LexAnaliz);						// запрещенно использовать стр в функции
	void isTrueParamCount(Error::ErrorTable&, LA::LexAnaliz);				// правильное кол-во параметров в выз. функции
	void isStrAction(Error::ErrorTable&, LA::LexAnaliz);
	void isSoBigValue(Error::ErrorTable&, LA::LexAnaliz,char*);
}