#pragma once
#include "LT.h"
#define ID_MAXSIZE			10								// макс. кол-во символов в идентификаторе
#define ID_PMAXSIZE			255								// макс. кол-во символов в идентификаторе
#define TI_MAXSIZE			4096							// макс. кол-во строк в таблице идентификаторов
#define TI_INT_DEFAULT		0x00000000						// значение по умолчанию для типа integer
#define TI_STR_DEFAULT		0x00							// значение по умолчанию для типа string
#define TI_NULLIDX			0xffffffff						// нет элемента таблицы индетификаторов
#define TI_STR_MAXSIZE		255
namespace IT												// таблица идетификаторов
{
	enum IDDATATYPE { DT_NO, DT_INT, DT_STR, DT_BOOL };					// типы данных идентификатов: integer, stringяяяя
	enum IDTYPE { T_NO, T_VAR, T_FUNC, T_FUNC_P, T_FUNC_I, T_FUNC_IP, T_LITERAL, T_CONDITION, T_CONDITION_P, T_ELSE, T_CIRCLE, T_CIRCLE_P,
	T_MAINFUNC};				// типы идентификиторов: переменная, функция, параметр, литерал, указатель

	struct Entry											// строка таблицы идентификаторов
	{
		int			idfirstLE;								// индекс первой строки в таблице лексем
		char		*id = new char[ID_MAXSIZE];				// идентификатор (автомат. усекаеться до ID_MAXSIZE)
		char		*prefId = new char[ID_MAXSIZE];
		bool		pointer = false;
		int			iddatatype;								// тип данных
		int			idtype;									// тип идентификатора
		struct 
		{
			char *val = new char[255];						// значение integer
			int len;
		}value;												// значение идентификатора
		Entry();
	};

	struct IdTable											// экземпляр таблицы идентификаторов
	{				
		int maxsize;										// емкость таблицы  идентификаторов < TI_MAXSIZE
		int size;											// текущий размер таблицы идентификаторов < maxsize
		Entry* table;										// массив строк таблицы идентификаторов
	};
	IdTable Create(											// создать таблицу идентификаторов
					int size								// емкость таблицы идентификаторов < TI_MAXSIZE
					);

	void Add(												// добавить строку таблицы идентификаторов 
			IdTable& idtable,								// экземпляр таблицы идентификаторов
			Entry entry										// строка таблицы идентификаторов
			);

	Entry GetEntry(											// получить строку таблицы идентификаторов
					IdTable &idtable,						// экземпляр таблицы идентификаторов
					int n									// номер получаемой строки
					);

	int IsId(					// возврат: номер строки (если есть), TI_NULLIDX(если нет)
		IdTable & idtable,		// таблица иден.
		bool isDecFunction,		// прототип функции или нет
		char word[ID_MAXSIZE],	// имя переменной
		char nameFunction[ID_MAXSIZE]	// имя функции(префикс)
	);
	

	void Delete(IdTable& ittable);							// удалить таблицу лексем (освободить память)
	void ShowIT(IdTable& iT, LT::LexTable l, Parm::PARM param, Log::LOG log);
}