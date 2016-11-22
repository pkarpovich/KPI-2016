#pragma once
#include "stdafx.h"

namespace LA
{
	struct LexAnaliz	// структура в которой будут хранится две таблицы
	{
		LT::LexTable l;
		IT::IdTable iT;
	};

	
	LexAnaliz LexicalAnaliz(In::Devide dev, Log::LOG log, Parm::PARM param);	// лексический анализ
	void AddID(IT::Entry iT, bool isDecFunction, char pref[255], char word[255], char decFunction[ID_MAXSIZE]);	//доб. имени идент.
	int WhereI(LexAnaliz lex, int i);
	void ToUnderCase(char destination[255], char source[255], int Line);	// конвертация большой буквы в меленькую
}