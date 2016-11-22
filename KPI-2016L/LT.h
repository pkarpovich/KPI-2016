#pragma once

#define LEXEMA_FIZSIZE		1				// фиксированный размер лексемы
#define LT_MAXSIZE			4096			// максимальное кол-во строк в таблице лексем
#define LT_TI_NULLIDX		0xffffffff		// нет элемента таблицы индетификаторов
#define LEX_INTEGER			't'				// лексема для integer
#define LEX_STRING			't'				// лексема для string
#define LEX_BOOL			't'				// лексема для bool
#define LEX_VARIABLE		'v'				// лексема для индентификатора
#define LEX_LITERAL			'l'				// лексема для литерала
#define LEX_BOOL_LITERAL	'l'				// лексема для bool литерала
#define LEX_FUNCTION		'f'				// лексема для function
#define LEX_BEGIN_FUNCTION	'm'				// Лексема для begin
#define LEX_CIRCLE			'c'				// лексема для циклов
#define LEX_CONDITION		'i'
#define LEX_ELSE			'e'
#define LEX_ENDL			'n'
#define LEX_DECLARE			'd'				// лексема для declare
#define LEX_RETURN			'r'				// лексема для return
#define LEX_SOUT			'p'				// лексема для print
#define LEX_SIN				's'
#define LEX_SEMICOLON		';'				// лексема для ;
#define LEX_COMMA			','				// лексема для ,
#define LEX_LEFTBRACE		'['				// лексема для {
#define LEX_RIGHTBRACE		']'				// лексема для }
#define LEX_LEFTTHESIS		'('				// лексема для (
#define LEX_RIGHTTHESIS		')'				// лексема для )
#define LEX_ACTION			'a'				// лексема дл + - * /
#define LEX_BOOL_ACTION		'b'
#define LEX_MORE			'b'
#define LEX_LESS			'b'
#define LEX_PLUS			'v'				// лексема для +
#define LEX_MINUS			'v'				// лексема для -
#define LEX_STAR			'v'				// лексема для *
#define LEX_DIRSLASH		'v'				// лексема для /
#define LEX_EQUALLU			':'				// лексема для =
#define LEX_FORBIDDEN		'#'				// запрещенная лексема (ей будет заполняться пустое место в таблице лексем)
#define LEX_AT				'@'				// функция в польской записи


namespace LT								// таблица лексем
{
	enum PN { PN_DEF, PN_MINUS = 2, PN_PLUS = 2, PN_STAR = 3, PN_DIRSLASH = 3, PN_LEFTTHESIS = 1 };
	struct Entry							// строка таблицы лексем
	{
		char lexema;						// лексема
		int sn;								// номер строки в исходном тексте
		int idxTI;							// индекс в таблице идентификаторов иди LT_TI_NULLIDX
		int priority;						// приоритет
		int braceType;
		int automat;
	};

	struct LexTable							// экземпляр таблиццы лексем
	{
		int maxsize;						// емкость таблицы лексем < LT_MAXSIZE
		int size;							// текущий размер таблицы лексем < maxsize
		Entry* table;						// массив строк таблицы лексем
	};


	LexTable Create(						// создать таблицу лексем
					int size				// емкость таблицы лексем < LT_MAXSIZE
					);
	void Add(								// добавить строку в таблицу лексем
			LexTable& lextable,				// экземпляр таблицы лексем
			Entry entry						// строка таблицы лексем
			);
	void AddTo(LexTable& lextable, Entry entry, int pos);
	Entry GetEntry(							// получить строку таблицы лексем
					LexTable& lextable,		// экземпляр таблицы лексем
					int n					// номер получаемой строки
					);
	void Swap(LexTable &oldLexTable, int nomber, Entry newTable);		// заменить Entry
	void Delete(LexTable& lextable);		// удалить таблицу лексем
	void ShowLT(LexTable&l, Parm::PARM param, Log::LOG log);
}