#pragma once

#define GET_ERROR(id) Error::getError(id);
#define ADD_ERROR(id,line,pos,word,type) Error::addError(id,line,pos,word,type);
#define ERROR_THROW_IN Error::getErrorIn();
#define ERROR_ENTRY(id, m) {id, m}
#define ERROR_MAXSIZE_MESSAGE 200
#define ERROR_ENTRY_NODEF(id)	ERROR_ENTRY(-id,"Неопределенная ошибка")
#define ERROR_ENTRY_NODEF10(id)		ERROR_ENTRY_NODEF(id+0),ERROR_ENTRY_NODEF(id+1),ERROR_ENTRY_NODEF(id+2),ERROR_ENTRY_NODEF(id+3), \
									ERROR_ENTRY_NODEF(id+4),ERROR_ENTRY_NODEF(id+5),ERROR_ENTRY_NODEF(id+6),ERROR_ENTRY_NODEF(id+7), \
									ERROR_ENTRY_NODEF(id+8),ERROR_ENTRY_NODEF(id+9)
#define ERROR_ENTRY_NODEF100(id)	ERROR_ENTRY_NODEF10(id+0),ERROR_ENTRY_NODEF10(id+10),ERROR_ENTRY_NODEF10(id+20),ERROR_ENTRY_NODEF10(id+30), \
									ERROR_ENTRY_NODEF10(id+40),ERROR_ENTRY_NODEF10(id+50),ERROR_ENTRY_NODEF10(id+60),ERROR_ENTRY_NODEF10(id+70), \
									ERROR_ENTRY_NODEF10(id+80),ERROR_ENTRY_NODEF10(id+90)
#define ERROR_MAX_ENTRY 1000

namespace Error
{
	enum ErrorType { PARAM = 1, INN = 2, LOG = 3, LT = 4, IT = 5, LA = 6 };	// тип ошибки 
																	//	(1 - в параметрах, 2 - в исходном файлу, 3 - в логе,
																	//   4 - таблице лексем, 5 - таблице индентификаторов,
																	//   6 - в лек анализе)
	
	struct ERROR_MESSAGE							// структура ошибок
	{
		int id;
		char message[ERROR_MAXSIZE_MESSAGE];
	};
	struct ERRORS									// если есть доп. поля
	{
		int count = 0;								// колличество ошибок
		ErrorType type;								// тип ошибки
		int id;										// ид ошибки
		char message[ERROR_MAXSIZE_MESSAGE];		// сообщение ошибки
		struct error
		{
			int line;								// строка в которой ошибка
			int pos;								// позиция ошибки
			char word[255];
		}errors[100];
	};
	ERROR_MESSAGE getError(int id);
	void addError(int id, int line, int col, char word[255], ErrorType type);				// занести новую ошибку в структуру
	ERRORS getErrorIn();											// вывод ошибки, если есть доп поля
}