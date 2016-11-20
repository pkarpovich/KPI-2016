#pragma once
#include "LT.h"
#define ID_MAXSIZE			5								// макс. кол-во символов в идентификаторе
#define ID_PMAXSIZE			255								// макс. кол-во символов в идентификаторе
#define TI_MAXSIZE			4096							// макс. кол-во строк в таблице идентификаторов
#define TI_INT_DEFAULT		0x00000000						// значение по умолчанию для типа integer
#define TI_STR_DEFAULT		0x00							// значение по умолчанию для типа string
#define TI_NULLIDX			0xffffffff						// нет элемента таблицы индетификаторов
#define TI_STR_MAXSIZE		255
namespace IT												// таблица идетификаторов
{
	enum IDDATATYPE { NO = 0 ,INT = 1, STR = 2, BOOL = 3 };					// типы данных идентификатов: integer, stringяяяя
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, IF = 5, CIRCLE = 6, IP};				// типы идентификиторов: переменная, функция, параметр, литерал, указатель

	struct Entry											// строка таблицы идентификаторов
	{
		int			idfirstLE;								// индекс первой строки в таблице лексем
		char		*id = new char[ID_MAXSIZE];				// идентификатор (автомат. усекаеться до ID_MAXSIZE)
		char		*prefId = new char[ID_MAXSIZE];
		bool		pointer = false;
		IDDATATYPE	iddatatype;								// тип данных
		IDTYPE		idtype;									// тип идентификатора
		union 
		{
			int vint;										// значение integer
			struct
			{
				int len;									// колличество симолов в string 
				char str[TI_STR_MAXSIZE];					// симолы string
			} vstr;											// значение string
			char vbool[5];									// значение bool
		}value;												// значение идентификатора
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