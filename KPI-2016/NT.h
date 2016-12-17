#pragma once

namespace NT
{
	enum typeNible { PRINT, INIT, LEX_INIT, RETURN, PLUS, MINUS, MUL, PUSH, POP, DIV, IF, MORE, LESS, END_IF, ELSE, END_ELSE, CIRCLE,
	END_CIRCLE, FUNC, PARAM_INIT, PARAM_SECOND_INIT, START_FUNC, END_FUNC, END_MAIN_FUNC, BEGIN, FUNC_INVOKE, FANC_PARAM,PUSH_INVOKE,
	KPI_LIB, STR_PUSH};

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
		Nible() = default;
		Nible(int);
		int maxSize;
		int size;
		set<typeNible> component;
		Entry* table;
	};
	void Add(Nible& table, Entry entry);
	void Delete(Nible& table, Entry entry);
	void Print(Nible table, Parm::PARM param, Log::LOG log);
	int lastNible(Nible& table, typeNible TN);

	Nible genNible(LA::LexAnaliz lex, Log::LOG log, Parm::PARM param);
	Entry setNible(int TN, int TD, const char* p2 = "null", const char* p3 = "null", const char* p4 = "null");

	bool operator == (Entry e1, Entry e2);
}