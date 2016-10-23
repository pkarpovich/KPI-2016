#include "stdafx.h"
using namespace std;

namespace Error
{
	ERROR_MESSAGE errors[ERROR_MAX_ENTRY] =											// описание ошибок
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Превышина длина входного параметра"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом(-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "Не удалось составить слово из данных симолов"), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180),
		ERROR_ENTRY(200, "Превышен максимальный размер таблицы лексем"),
		ERROR_ENTRY(201, "Таблица лексем переполненна"),
		ERROR_ENTRY(202, "Превышен максимальный размер таблицы идентификаторов"),
		ERROR_ENTRY(203, "Таблица идентификаторов переполненна"),
		ERROR_ENTRY_NODEF(204), ERROR_ENTRY_NODEF(205),
		ERROR_ENTRY_NODEF(206), ERROR_ENTRY_NODEF(207), ERROR_ENTRY_NODEF(208), ERROR_ENTRY_NODEF(209),
		ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240),
		ERROR_ENTRY_NODEF10(250), ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280),
		ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY(300, "Идентификатор не должен содержать заглавную букву"),
		ERROR_ENTRY(301, "Идентификатор не должен привышать 5 символов"),
		ERROR_ENTRY_NODEF(302),ERROR_ENTRY_NODEF(303),ERROR_ENTRY_NODEF(304),ERROR_ENTRY_NODEF(305),ERROR_ENTRY_NODEF(306),
		ERROR_ENTRY_NODEF(307),ERROR_ENTRY_NODEF(308),ERROR_ENTRY_NODEF(309),
		ERROR_ENTRY_NODEF10(310),ERROR_ENTRY_NODEF10(320),ERROR_ENTRY_NODEF10(330),ERROR_ENTRY_NODEF10(340),
		ERROR_ENTRY_NODEF10(350),ERROR_ENTRY_NODEF10(360),ERROR_ENTRY_NODEF10(370),ERROR_ENTRY_NODEF10(380),
		ERROR_ENTRY_NODEF10(390),
		ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "Неверная структура программы"), ERROR_ENTRY(601, "Ошибочный оператор"),
		ERROR_ENTRY(602, "Ошибка в выражении"), ERROR_ENTRY(603, "Ошибка в параметрах функции"), 
		ERROR_ENTRY(604, "Ошибка в параметрах вызываемой функции"), ERROR_ENTRY_NODEF(605), ERROR_ENTRY_NODEF(606), ERROR_ENTRY_NODEF(607),
		ERROR_ENTRY_NODEF(608), ERROR_ENTRY_NODEF(609), ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630),
		ERROR_ENTRY_NODEF10(640), ERROR_ENTRY_NODEF10(650), ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690), ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800)
	};

	ERRORS error;
	
	ERRORS getError(int id, int type)								// определяем тип м выводим ошибку если нет доп полей
	{
		switch (type)
		{
		case 1: error.type = ErrorType::PARAM; break;
		case 2: error.type = ErrorType::INN; break;
		case 3: error.type = ErrorType::LOG; break;
		case 4: error.type = ErrorType::LT; break;
		case 5: error.type = ErrorType::IT; break;
		case 6: error.type = ErrorType::LA; break;
		}
		if (0 < id && id < ERROR_MAX_ENTRY)
		{
			error.id = id;
			memcpy(error.message, errors[id].message, sizeof(errors[id].message));
			return error;
		}
		else
		{
			error.id = 0;
			memcpy(error.message, errors[0].message, sizeof(errors[0].message));
			return error;
		}
	}
	void newError(int id, int line, int col, int type)							// заполняем структуру ошибки с доп полями
	{
		switch (type)
		{
		case 1: error.type = ErrorType::PARAM; break;
		case 2: error.type = ErrorType::INN; break;
		case 3: error.type = ErrorType::LOG; break;
		case 4: error.type = ErrorType::LT; break;
		case 5: error.type = ErrorType::IT; break;
		case 6: error.type = ErrorType::LA; break;
		}
		if (0 < id&&id < ERROR_MAX_ENTRY)
		{
			error.id = id;
			memcpy(error.message, errors[id].message, sizeof(errors[id].message));
		}
		else
		{
			error.id = 0;
			memcpy(error.message, errors[0].message, sizeof(errors[0].message));
		}
		if (type == 2)										// если ошибка в исходном файле заполняем строку и позицию
		{
			error.errors_in[error.count].line = line;
			error.errors_in[error.count].pos = col;
		}
		error.count++;										// считаем кол - во ошибок
	}

	void newWarning(int id, int line, char word[255], int type)
	{
		switch (type)
		{
		case 1: error.type = ErrorType::PARAM; break;
		case 2: error.type = ErrorType::INN; break;
		case 3: error.type = ErrorType::LOG; break;
		case 4: error.type = ErrorType::LT; break;
		case 5: error.type = ErrorType::IT; break;
		case 6: error.type = ErrorType::LA; break;
		}
		if (0 < id&&id < ERROR_MAX_ENTRY)
		{
			error.id = id;
			memcpy(error.message, errors[id].message, sizeof(errors[id].message));
		}
		else
		{
			error.id = 0;
			memcpy(error.message, errors[0].message, sizeof(errors[0].message));
		}
		if (type == 6)										// если ошибка в исходном файле заполняем строку и позицию
		{
			error.errors_la[error.warning].line = line;
			error.errors_la[error.warning].id = id;
			memcpy(error.errors_la[error.warning].message, errors[id].message, sizeof(error.message));
			int i;
			for (i = 0; i < strlen(word); i++)
			{
				error.errors_la[error.warning].word[i] = word[i];
			}
			error.errors_la[error.warning].word[i] = '\0';
		}
		error.warning++;										// считаем кол - во ошибок
	}
	ERRORS getErrorIn()							// вывод заполненной ошибки
	{
		return error;
	}
}