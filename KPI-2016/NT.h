#pragma once
#define NIBLE_MAX_SIZE 50


namespace NT
{
	enum typeNible { PRINT, INIT, LEX_INIT, RETURN, PLUS, MINUS, MUL, PUSH, POP, DIV, IF, MORE_OR_EQUALLY, MORE, LESS_OR_EQUALLY, LESS, EQUALITY, NO_EQUALITY,
	END_IF, ELSE, END_ELSE, CIRCLE, END_CIRCLE, FUNC, PARAM_INIT, PARAM_SECOND_INIT, START_FUNC, END_FUNC, END_MAIN_FUNC, BEGIN, FUNC_INVOKE, FANC_PARAM,PUSH_INVOKE,
	KPI_LIB, STR_PUSH, INC, DEC
	};

	struct Entry
	{
		int TN;
		int TD;
		char* p2 = new char[NIBLE_MAX_SIZE];
		char* p3 = new char[NIBLE_MAX_SIZE];
		char* p4 = new char[NIBLE_MAX_SIZE];
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
	void Add(Nible&, Entry);
	void Delete(Nible&, Entry);
	void Print(Nible, Parm::PARM, Log::LOG);
	int lastNible(Nible&, typeNible);

	Nible genNible(LA::LexAnaliz, Log::LOG, Parm::PARM);
	Entry setNible(int TN, const int TD = 0, const char* p2 = "null", const char* p3 = "null", const char* p4 = "null");

	bool operator == (Entry e1, Entry e2);
}