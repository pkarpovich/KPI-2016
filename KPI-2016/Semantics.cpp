#include "stdafx.h"
namespace MA
{
	Error::ErrorTable eT(1000);
	void isIndef(LA::LexAnaliz Lex, char *word, char *nameFunc)	
	{
		if (IT::IsId(Lex.iT, false, word, nameFunc) == TI_NULLIDX)
			if (Lex.l.table[Lex.l.size - 2].lexema != LEX_INTEGER)
				throw GET_ERROR(305, Lex.l.table[Lex.l.size - 1].sn, -1, word);
	}
	void isRedefinition(LA::LexAnaliz Lex, char *word, char *nameFunc)
	{
		if (IT::IsId(Lex.iT, false, word, nameFunc) != TI_NULLIDX)
			if (Lex.l.table[Lex.l.size - 2].lexema == LEX_INTEGER)
				throw GET_ERROR(304, Lex.l.table[Lex.l.size - 1].sn, -1, word);
	}
	void isBigId(int line, char *word)
	{
		if(strlen(word) > ID_MAXSIZE)	throw GET_ERROR(302, line, -1, word);
	}
	void isZeroDivision(LA::LexAnaliz Lex, char *literal)
	{
		if(strcmp(literal,"0") == 0 && Lex.l.table[Lex.l.size - 2].automat == FST::DIRSLASH)
			throw GET_ERROR(308, Lex.l.table[Lex.l.size - 2].sn);
	}
	void isStrFunc(LA::LexAnaliz Lex)
	{
		if (Lex.iT.table[Lex.iT.size - 1].iddatatype == IT::DT_STR)
		{
			if(Lex.iT.table[Lex.iT.size - 1].idtype == IT::T_FUNC)
				throw GET_ERROR(309, Lex.l.table[Lex.l.size - 1].sn, -1, Lex.iT.table[Lex.iT.size - 1].id);
			if(Lex.iT.table[Lex.iT.size - 1].idtype == IT::T_FUNC_P)
				throw GET_ERROR(311, Lex.l.table[Lex.l.size - 1].sn, -1, Lex.iT.table[Lex.iT.size - 1].id);
			if(Lex.l.table[Lex.l.size-2].lexema == LEX_RETURN && Lex.iT.table[Lex.iT.size - 1].iddatatype == IT::DT_STR)
				throw GET_ERROR(310, Lex.l.table[Lex.l.size - 1].sn, -1, Lex.iT.table[Lex.iT.size - 1].id);
			if(Lex.iT.table[Lex.iT.size - 1].idtype == IT::T_FUNC_IP)
				throw GET_ERROR(312, Lex.l.table[Lex.l.size - 1].sn, -1, Lex.iT.table[Lex.iT.size - 1].id);
		}
	}
	void isTrueParamCount(LA::LexAnaliz Lex)
	{
		int i = Lex.iT.size, count = 0;
		while (Lex.iT.table[i--].idtype != IT::T_FUNC_I)
		{
			if (Lex.iT.table[i].idtype == IT::T_FUNC_IP)	count++;
		}
		if (count != Lex.iT.table[IT::IsId(Lex.iT, false, Lex.iT.table[i + 1].id, "")].paramCount)
			throw GET_ERROR(314, Lex.l.table[Lex.l.size - 1].sn, -1, Lex.iT.table[i + 1].id);
	}
	void isStrAction(LA::LexAnaliz Lex)
	{
		if (Lex.iT.table[Lex.iT.size - 1].iddatatype == IT::DT_STR)
		{
			if (Lex.l.table[Lex.l.size - 2].lexema == LEX_ACTION)
				throw GET_ERROR(315, Lex.l.table[Lex.l.size - 1].sn, -1, Lex.iT.table[Lex.iT.size - 1].id);
		}
	}
}