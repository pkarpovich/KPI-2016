#include "stdafx.h"
using namespace std;

namespace Error
{
	ERROR_MESSAGE errors[ERROR_MAX_ENTRY] =											// описание ошибок
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "[FATAL] Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "[FATAL] Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "[FATAL] Превышина длина входного параметра"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "[FATAL] Ошибка при открытии файла с исходным кодом(-in)"),
		ERROR_ENTRY(111, "[FATAL] Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "[FATAL] Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "[FATAL] Не удалось составить слово из данных симолов"),
		ERROR_ENTRY(114, "[FATAL] Многострочный комментарий должен быть закрытым"),
		ERROR_ENTRY(115, "[FATAL] Неправильное объявление строчного литерала"),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180),
		ERROR_ENTRY(200, "[LA] Превышен максимальный размер таблицы лексем"),
		ERROR_ENTRY(201, "[LA] Таблица лексем переполненна"),
		ERROR_ENTRY(202, "[LA] Превышен максимальный размер таблицы идентификаторов"),
		ERROR_ENTRY(203, "[LA] Таблица идентификаторов переполненна"),
		ERROR_ENTRY_NODEF(204),	ERROR_ENTRY_NODEF(205),	ERROR_ENTRY_NODEF(206), ERROR_ENTRY_NODEF(207),
		ERROR_ENTRY_NODEF(208), ERROR_ENTRY_NODEF(209),	ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220),
		ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240),	ERROR_ENTRY_NODEF10(250), ERROR_ENTRY_NODEF10(260),
		ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280),	ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY(300, "[MA] Идентификатор не должен начинаться с заглавной буквы"),
		ERROR_ENTRY(301, "[MA] Идентификатор не должен содержать цифру"),
		ERROR_ENTRY(302, "[MA] Идентификатор не должен превышать 10 символов"),
		ERROR_ENTRY(303, "[MA] Повторное наименование функции"),
		ERROR_ENTRY(304, "[MA] Переобъявление идентификатора"),
		ERROR_ENTRY(305, "[MA] Идентификатор не объявлен"),
		ERROR_ENTRY(306, "[MA] Точка входа begin должна быть задана"),
		ERROR_ENTRY(307, "[MA] Недолжно быть более одной точки входа"),
		ERROR_ENTRY(308, "[MA] Деление на ноль запрещенно"),
		ERROR_ENTRY_NODEF(309),
		ERROR_ENTRY_NODEF10(310),ERROR_ENTRY_NODEF10(320),ERROR_ENTRY_NODEF10(330),ERROR_ENTRY_NODEF10(340),
		ERROR_ENTRY_NODEF10(350),ERROR_ENTRY_NODEF10(360),ERROR_ENTRY_NODEF10(370),ERROR_ENTRY_NODEF10(380),
		ERROR_ENTRY_NODEF10(390),
		ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "[SA] Неверная структура программы"), 
		ERROR_ENTRY(601, "[SA] Парметры функции составленны неверно"),
		ERROR_ENTRY(602, "[SA] Структура цикла или условия составленна неверно"),
		ERROR_ENTRY(603, "[SA] Конструкция функции составленны неверно"), 
		ERROR_ENTRY(604, "[SA] Выражение составленно неверно"), 
		ERROR_ENTRY(605, "[SA] Параметры условие или цикла составленны неверно"),
		ERROR_ENTRY_NODEF(606), ERROR_ENTRY_NODEF(607),
		ERROR_ENTRY_NODEF(608), ERROR_ENTRY_NODEF(609), ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630),
		ERROR_ENTRY_NODEF10(640), ERROR_ENTRY_NODEF10(650), ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690), ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800)
	};

	ERRORS error;
	
	ERROR_MESSAGE getError(int id)
	{
		ERROR_MESSAGE em;
		if (0 < id&&id < ERROR_MAX_ENTRY)
		{
			em.id = id;
			strcpy(em.message, errors[id].message);
		}
		else
		{
			em.id = 0;
			strcpy(em.message, errors[0].message);
		}
		return em;
	}
	void addError(int id, int line, int pos, char word[255], ErrorType type)							// заполняем структуру ошибки с доп полями
	{
		if (0 < id&&id < ERROR_MAX_ENTRY)
		{
			error.id = id;
			strcpy(error.message, errors[id].message);
			error.type = type;
		}
		else
		{
			error.id = 0;
			memcpy(error.message, errors[0].message, sizeof(errors[0].message));
		}
		switch (type)
		{
			case Error::INN: {error.errors[error.count].line = line; error.errors[error.count].pos = pos; break; }
			case Error::LA: {error.errors[error.count].line = line; strcpy(error.errors[error.count].word, word); break; }
		}
		error.count++;										// считаем кол - во ошибок
	}

	ERRORS getErrorIn()							// вывод заполненной ошибки
	{
		return error;
	}
}