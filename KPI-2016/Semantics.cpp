#include "stdafx.h"
namespace MA
{

	void isIndef(Error::ErrorTable &eT, LA::LexAnaliz Lex, char *word, char *nameFunc)
	{
		if (IT::IsId(Lex.iT, false, word, nameFunc) == TI_NULLIDX)
			if (Lex.l.table[Lex.l.size - 2].lexema != LEX_INTEGER)
				GET_ERROR(305, Lex.l.table[Lex.l.size - 1].sn, -1, word);
	}
	void isRedefinition(Error::ErrorTable &eT, LA::LexAnaliz Lex, char *word, char *nameFunc)
	{
		if (IT::IsId(Lex.iT, false, word, nameFunc) != TI_NULLIDX)
			if (Lex.l.table[Lex.l.size - 2].lexema == LEX_INTEGER)
				GET_ERROR(304, Lex.l.table[Lex.l.size - 1].sn, -1, word);
	}
	void isBigId(Error::ErrorTable &eT, int line, char *word)
	{
		if(strlen(word) > ID_MAXSIZE)	throw GET_ERROR(302, line, -1, word);
	}
	void isZeroDivision(Error::ErrorTable &eT, LA::LexAnaliz Lex, char *literal)
	{
		if(strcmp(literal,"0") == 0 && Lex.l.table[Lex.l.size - 2].automat == FST::DIRSLASH)
			GET_ERROR(308, Lex.l.table[Lex.l.size - 2].sn);
	}
	void isStrFunc(Error::ErrorTable &eT, LA::LexAnaliz Lex)
	{
		if (Lex.iT.table[Lex.iT.size - 1].iddatatype == IT::DT_STR)
		{
			if(Lex.iT.table[Lex.iT.size - 1].idtype == IT::T_FUNC)
				GET_ERROR(309, Lex.l.table[Lex.l.size - 1].sn, -1, Lex.iT.table[Lex.iT.size - 1].id);
			if(Lex.iT.table[Lex.iT.size - 1].idtype == IT::T_FUNC_P)
				GET_ERROR(311, Lex.l.table[Lex.l.size - 1].sn, -1, Lex.iT.table[Lex.iT.size - 1].id);
			if(Lex.l.table[Lex.l.size-2].lexema == LEX_RETURN && Lex.iT.table[Lex.iT.size - 1].iddatatype == IT::DT_STR)
				GET_ERROR(310, Lex.l.table[Lex.l.size - 1].sn, -1, Lex.iT.table[Lex.iT.size - 1].id);
			if(Lex.iT.table[Lex.iT.size - 1].idtype == IT::T_FUNC_IP)
				GET_ERROR(312, Lex.l.table[Lex.l.size - 1].sn, -1, Lex.iT.table[Lex.iT.size - 1].id);
		}
	}
	void isTrueParamCount(Error::ErrorTable &eT, LA::LexAnaliz Lex)
	{
		int i = Lex.iT.size, count = 0;
		while (Lex.iT.table[i--].idtype != IT::T_FUNC_I)
		{
			if (Lex.iT.table[i].idtype == IT::T_FUNC_IP)	count++;
		}
		if (count != Lex.iT.table[IT::IsId(Lex.iT, false, Lex.iT.table[i + 1].id, "")].paramCount)
			GET_ERROR(314, Lex.l.table[Lex.l.size - 1].sn, -1, Lex.iT.table[i + 1].id);
	}
	void isStrAction(Error::ErrorTable &eT, LA::LexAnaliz Lex)
	{
		if (Lex.iT.table[Lex.iT.size - 1].iddatatype == IT::DT_STR)
		{
			if (Lex.l.table[Lex.l.size - 2].lexema == LEX_ACTION)
				GET_ERROR(315, Lex.l.table[Lex.l.size - 1].sn, -1, Lex.iT.table[Lex.iT.size - 1].id);
		}
	}
	void isSoBigValue(Error::ErrorTable &eT, LA::LexAnaliz Lex, char *val)
	{
		int buf;
		if (Lex.iT.table[Lex.iT.size - 1].iddatatype == IT::DT_STR)
		{
			if(strlen(val) > 50) GET_ERROR(316, Lex.l.table[Lex.l.size - 1].sn, -1, Lex.iT.table[Lex.iT.size - 1].id);
		}
		else
		{
			buf = atoi(val);
			if (buf > 1000000) GET_ERROR(316, Lex.l.table[Lex.l.size - 1].sn, -1, Lex.iT.table[Lex.iT.size - 1].id);
		}
	}
}