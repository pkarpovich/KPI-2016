#pragma once

namespace NT
{
	enum typeNible { PRINT, INIT, LEX_INIT, RETURN, PLUS, MINUS, MUL, INT_D, INT_E, DIV, IF, MORE, LESS, ENDIF, ELSE, ENDELSE, CIRCLE,
	ENDCIRCLE, FUNC, PARAM_INIT, PARAM_SECOND_INIT, STARTFUNC, ENDFUNC, ENDMAINFUNC, BEGIN, FUNCINVOKE, FANCPARAM,PUSHINVOKE,
	KPILIB};

	struct Entry
	{
		int TN;
		int TD;
		char* p2 = new char[50];
		char* p3 = new char[50];
		char* p4 = new char[50];
	};

	struct Nible
	{
		int maxSize;
		int size;
		set<typeNible> component;
		Entry* table;
	};

	Nible Create(int size);
	void Add(Nible& table, Entry entry);
	void Delete(Nible& table, Entry entry);
	void Print(Nible table);
	int lastNible(Nible& table, typeNible TN);

	Nible genNible(LA::LexAnaliz lex, Log::LOG log);
	Entry setNible(int TN, int TD, const char* p2 = "null", const char* p3 = "null", const char* p4 = "null");

	bool operator == (Entry e1, Entry e2);
}