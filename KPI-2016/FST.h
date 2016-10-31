#include "stdafx.h"

#define FN FST::AUTOMAT_NAME

namespace FST
{
	enum AUTOMAT_NAME {INT, STR, BOOL, FUNCTION, DECLARE, BEGIN, SOUT, RETURN, ACTION, BOOLACTION, EQUALLU, LTHESIS, RTHESIS, SEMILICON, COMMA, LBRACE, RBRACE,
	FALSELITERAL, TRUELITERAL,IDENTETIF, FIDENTETIF, FALSENUMIDENTETIF, LITERAL, INTLITERAL, WCIRCLE, MORE, LESS, CONDITIONIF, SIN};

	struct RELATION
	{
		char symbol; // символ перехода
		short nnode; // номер смежной вершины
		RELATION(char c = 0x00 /*символ перехода*/, short ns = NULL /*новое состояние*/);
	};

	struct NODE
	{
		short n_relation; // ко-во рёбер
		RELATION *relations; // рёбра
		NODE(); // по умолчанию
		NODE(short n /*кол-во рёбер*/, RELATION rel, ... /*рёбра*/);  // параметрический
	};

	struct FST
	{
		char *string; /*цепочка*/
		short position; /*позиция в цпочке*/
		short nstates; /*кол-во состояний*/
		NODE *nodes; /*граф перехода*/
		short *rstates; /*возможные состояния*/
		FST(char *s/*цепочка*/, short ns/*кол-во состояний*/, NODE n, .../*список состояний*/);
	};

	struct Automatic
	{
		FST automat;
		char lexema;
		AUTOMAT_NAME automatName;
	};

	bool step(FST &fst, short *&rstates); // разбор одного символа
	bool execute(FST &fsts /*конечный автомат*/);  //распонование цепочки
	void newFST(FST& f, char* newStr);
	bool newLexem(FST &fst, char *newLexem, int lineCode, char lexem, LT::Entry& e, LT::LexTable& l, IT::IdTable iT);
}