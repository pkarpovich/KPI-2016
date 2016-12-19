#include "stdafx.h"
using namespace std;

namespace Error
{
	ErrorTable::ErrorTable(int size)
	{
		ErrorTable temp;
		temp.maxSize = size;
		temp.size = 0;
		temp.table = new Entry[size];
		ET(0, "Недопустимый код ошибки");
		ET(1, "[FATAL] Системный сбой");
		ET(100, "[FATAL] Параметр -in должен быть задан");
		ET(104, "[FATAL] Превышина длина входного параметра");
		ET(110, "[FATAL] Ошибка при открытии файла с исходным кодом(-in)");
		ET(111, "[FATAL] Недопустимый символ в исходном файле (-in)");
		ET(112, "[FATAL] Ошибка при создании файла протокола (-log)");
		ET(113, "[FATAL] Не удалось составить слово из данных симолов");
		ET(114, "[FATAL] Многострочный комментарий должен быть закрытым");
		ET(115, "[FATAL] Неправильное объявление строчного литерала");
		ET(200, "[LA] Превышен максимальный размер таблицы лексем");
		ET(201, "[LA] Таблица лексем переполненна");
		ET(202, "[LA] Превышен максимальный размер таблицы идентификаторов");
		ET(203, "[LA] Таблица идентификаторов переполненна");
		ET(300, "[MA] Идентификатор не должен начинаться с заглавной буквы");
		ET(301, "[MA] Идентификатор не должен содержать цифру");
		ET(302, "[MA] Идентификатор не должен превышать 10 символов");
		ET(303, "[MA] Повторное наименование функции");
		ET(304, "[MA] Переобъявление идентификатора");
		ET(305, "[MA] Идентификатор не объявлен");
		ET(306, "[MA] Точка входа begin должна быть задана");
		ET(307, "[MA] Недолжно быть более одной точки входа");
		ET(308, "[MA] Деление на ноль запрещенно");
		ET(309, "[MA] Тип данных STR запрещен в функции");
		ET(310, "[MA] Запрещенно возращать тип данных STR из функции");
		ET(311, "[MA] Запрещенно использовать тип данных STR в параметрах функции");
		ET(312, "[MA] Неверный тип параметра вызываемой функции");
		ET(313, "[MA] Стандартную библиотеку можно подключить только один раз");
		ET(314, "[MA] Неверное число передаваемых параметров");
		ET(315, "[MA] Вычисления могут производится над литералами/идентификаторами данных типа int.")
		ET(600, "[SA] Неверная структура программы");
		ET(601, "[SA] Парметры функции составленны неверно");
		ET(602, "[SA] Структура цикла или условия составленна неверно");
		ET(603, "[SA] Конструкция функции составленны неверно");
		ET(604, "[SA] Выражение составленно неверно");
		ET(605, "[SA] Параметры условие или цикла составленны неверно");
		for (int i = 0; i < temp.size; i++)
		{
			if (strlen(temp.table[i].message) == 0)
			{
				ET(i, "Неопределенная ошибка")
			}
		}
		*this = temp;
		//delete[] &temp;
	};

	void Add(ErrorTable& et, int id, char *message)
	{
		et.table[et.size].id = id;
		et.table[et.size].line = -1;
		et.table[et.size].pos = -1;
		strcpy(et.table[et.size].message, message);
		strcpy(et.table[et.size].word, "null");
		et.size++;
	}

	Entry GetError(ErrorTable et, int id)
	{
		for (int i = 0; i < et.size; i++)	if (et.table[i].id == id)	return et.table[i];
		return et.table[0];
	}

	ErrorTable CompleteError(ErrorTable & et, int id, const int line, const int pos, const char * word)
	{
		for (int i = 0; i < et.size; i++)
		{
			if (et.table[i].id == id)
			{
				et.table[i].line = line;
				et.table[i].pos = pos;
				strcpy(et.table[i].word, word);
				et.errors.push_back(et.table[i]);
				return et;
			}
		}
	};

	void PrintErrors(ErrorTable eT, Log::LOG log)
	{
		int id; char buf[255];
		Error::Entry temp;
		if (log.stream == NULL)	log = Log::getlog(L"KPI.log");
		for (int i = 0; i < eT.errors.size(); i++)
		{
			temp = eT.errors[i];
			sprintf_s(buf, 255, "Ошибка №%d: %s", temp.id, temp.message); DW(true, buf);
			if (temp.line != -1) { sprintf_s(buf, 255, ", строка: %d", temp.line); DW(true, buf); }
			if (temp.pos != -1) { sprintf_s(buf, 255, ", позиция: %d", temp.pos); DW(true, buf); }
			if (strlen(temp.word) != 0) { sprintf_s(buf, 255, ", слово: %s", temp.word); DW(true, buf); }
			DW(true, "\n");
		}
	}
}