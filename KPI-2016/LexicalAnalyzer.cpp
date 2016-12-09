﻿#include "stdafx.h"
#include "Automatic.h"

void LA::AddID(IT::Entry iT, bool isDecFunction, char pref[255], char word[255], char decFunction[ID_MAXSIZE])
{
	if (strlen(decFunction) > ID_MAXSIZE)	decFunction[ID_MAXSIZE] = '\0';	// урезаем имя протатипа функции
	if (isDecFunction)
	{
		strcpy(iT.id, word);
		if (iT.idtype != IT::T_FUNC)
		{
			strcpy(iT.prefId, decFunction);
			strcat(iT.prefId, word);
		}
		else	strcpy(iT.prefId, word);		
	}
	else
	{
		strcpy(iT.id, word);		// копирываем ид
		if (iT.idtype != IT::T_FUNC)
		{
			strcpy(iT.prefId, pref);	// добавляем префикс
			strcat(iT.prefId, word);	// добавляем к префиксу слово
		}
		else	strcpy(iT.prefId, word);
	}
	
}

int LA::WhereBrace(LexAnaliz lex, int i)
{
	for (int k = i; k > -1; k--)
	{
		switch (lex.l.table[k].lexema)
		{
		case LEX_BEGIN_FUNCTION: case LEX_FUNCTION: 
			if (lex.iT.table[lex.l.table[k + 2].idxTI].pointer)	return IT::T_FUNC_I;
			return IT::T_FUNC;
		case LEX_RIGHTBRACE:	
			while (lex.l.table[k--].lexema != LEX_CONDITION && lex.l.table[k--].lexema != LEX_CIRCLE)
			{};
			break;
		case LEX_CONDITION:		return IT::T_CONDITION;
		case LEX_CIRCLE: return IT::T_CIRCLE;
		}
	}
	return 0;
}

int LA::WhereI(LexAnaliz lex, int i)
{
	for (int k = i; k > -1; k--)
	{
		if (lex.l.table[k].lexema == LEX_LEFTBRACE)
		{
			return IT::T_VAR;
		}
		else if (lex.l.table[k].lexema == LEX_LEFTTHESIS)
		{
			if (lex.iT.table[lex.l.table[k - 1].idxTI].pointer)	return IT::T_FUNC_IP;
			if (lex.l.table[k - 1].lexema == LEX_CONDITION || lex.l.table[k - 1].lexema == LEX_CIRCLE ||
				lex.l.table[k - 1].lexema == LEX_VARIABLE)
			{
				switch (lex.l.table[k].braceType)
				{
				case IT::T_CONDITION:	return IT::T_CONDITION_P;
				case IT::T_CIRCLE:		return IT::T_CIRCLE_P;
				case IT::T_FUNC:		return IT::T_FUNC_P;
				case IT::T_FUNC_I:		return IT::T_FUNC_IP;
				default:				return lex.l.table[k].braceType;
				}
			}
			
		}
		else if (lex.l.table[k].lexema == LEX_RIGHTTHESIS)
		{
			while (lex.l.table[k--].lexema != LEX_LEFTTHESIS)
			{
			};
		}
		else if (lex.l.table[k].lexema == LEX_FUNCTION)
		{
			return IT::T_FUNC;
		}
		else if (lex.l.table[k].lexema == LEX_VARIABLE && lex.l.table[k + 1].lexema == LEX_LEFTTHESIS)
		{
			return IT::T_FUNC_I;
		}
	}
	return 0;
}

LA::LexAnaliz LA::LexicalAnaliz(In::Devide dev, Log::LOG log, Parm::PARM param)
{
	LA::LexAnaliz Lex;								// структура в которой будут хранится заполненная таблица лексем и иден.
	LT::Entry e;									// временная лексема
	Lex.l = LT::Create(LT_MAXSIZE);					// создаем таблицу лексем
	Lex.iT = IT::Create(TI_MAXSIZE);				// создаем таблицу иден.
	stack<FST::AUTOMAT_NAME> LexStack;				// наш стек, что бы узнавать что было до иден.
	stack<int> stack;

	bool isInFunction = 0, isDecFunction = 0, isDec = 0, isCircle = 0, isInitialization = 0;		// узнаем мы в функции, или в протатипе функции
	bool isFuncParam = 0;

	int Line = 1,									// номер строки
		count_literal = 1,							// счетчик литералов
		beginCount = 0;								// проверка на begin

	char *nameFunction = new char[ID_MAXSIZE];	// имя функции
	char *decFunction = new char[ID_MAXSIZE];	// имя протатипа функции
	for (int i = 0; i <= dev.count_word; i++)
	{
		for (int k = 0; k < _countof(FST_ARRAY); k++)
		{
			if (*dev.word[i] != DEVIDE_LINE)	// если у нас не конец строки
			{
				if (FST::newLexem(FST_ARRAY[k].automat, dev.word[i], Line, FST_ARRAY[k].lexema, e, Lex.l, Lex.iT, FST_ARRAY[k].priotiry, FST_ARRAY[k].automatName))
				{
					switch (FST_ARRAY[k].automatName)
					{
					case FN::INT: case FN::STR: case FN::BOOL: case FN::FUNCTION: case FN::COMMA:
						LexStack.push(FST_ARRAY[k].automatName);	break;
					case FN::LBRACE: case FN::LTHESIS: case FN::RBRACE: case FN::RTHESIS:
						LexStack.push(FST_ARRAY[k].automatName);
						Lex.l.table[Lex.l.size - 1].braceType = WhereBrace(Lex, Lex.l.size - 2); break;
					case FN::KPILIB: 
					{
						IT::Entry *it = new IT::Entry;
						AddID(*it, false, "", "sqrt", decFunction);
						it->idfirstLE = i;
						it->idtype = IT::T_FUNC;
						IT::Add(Lex.iT, *it);	// добавляем временную таблицу в таблицу иден.
						delete[] it;			// очищаем память
						IT::Entry *itt = new IT::Entry;
						AddID(*itt, false, "", "xpow", decFunction);
						itt->idfirstLE = i;
						itt->idtype = IT::T_FUNC;
						IT::Add(Lex.iT, *itt);	// добавляем временную таблицу в таблицу иден.
						delete[] itt;			// очищаем память
						break;
					}
					case FN::BEGIN: {strcpy(nameFunction, "begin\0"); beginCount++; break; }	// если у нас main
					case FN::EQUALLU: isInitialization = true; break;
					case FN::FALSENUMIDENTETIF: {ADD_ERROR(301, Line, 0, dev.word[i], Error::LA); throw ERROR_THROW_IN}
					case FN::FIDENTETIF: {ADD_ERROR(300, Line, 0, dev.word[i], Error::LA); throw ERROR_THROW_IN}
					case FN::IDENTETIF:										// если у нас иден.
					{
						IT::Entry *it = new IT::Entry;
						it->idtype = WhereI(Lex, Lex.l.size - 2);
						/*switch (WhereI(Lex,Lex.l.size)
						{
						
						default:
							break;
						}*/
						if (strlen(dev.word[i]) > ID_MAXSIZE)		// предупреждение если слишком большой иден. и усечения идент.
						{
							ADD_ERROR(302, Line, 0, dev.word[i], Error::LA);
							dev.word[i][ID_MAXSIZE] = '\0';
						}
						while (!LexStack.empty())		// смотрим в стек и узнаем что было до ид.
						{
							switch (LexStack.top())
							{
							case FN::INT: {it->iddatatype = IT::DT_INT; isDec = true; break; }	// если был инт
							case FN::STR: {it->iddatatype = IT::DT_STR; isDec = true; break; }	// если был стр
							case FN::BOOL: {it->iddatatype = IT::DT_BOOL;isDec = true; break; }	// если был стр
							case FN::FUNCTION:			// если была функция
							{
								//it->idtype = IT::T_FUNC;
								//if (WhereI(Lex, Lex.l.size) == IT::T_FUNC)	strcpy(decFunction, dev.word[i]);
								/*else*/	strcpy(nameFunction, dev.word[i]);
								break;
							}
							//case FN::COMMA: case FN::LTHESIS: it->idtype = IT::T_FUNC_P; break; 	// если был параметр
							
							}
								LexStack.pop();	// удаляем из стека
							}
						/*if (WhereI(Lex, Lex.l.size - 2) == IT::T_FUNC)
						{
							it->idtype = IT::T_FUNC_P;
						}*/
							if (IT::IsId(Lex.iT, isDecFunction, dev.word[i], nameFunction) != TI_NULLIDX)	// проверяем на указатель
							{
								int pointerID = IT::IsId(Lex.iT, isDecFunction, dev.word[i], nameFunction);
								if (it->idtype == IT::T_CIRCLE_P)
								{
									*it = IT::GetEntry(Lex.iT, pointerID);
									it->pointer = true;
									it->idtype = IT::T_CIRCLE_P;
								}
								else if (it->idtype == IT::T_CONDITION_P)
								{
									*it = IT::GetEntry(Lex.iT, pointerID);
									it->pointer = true;
									it->idtype = IT::T_CONDITION_P;
								}
								else
								{
									*it = IT::GetEntry(Lex.iT, pointerID);
									it->pointer = true;
									if (it->idtype == IT::T_FUNC_P)
										it->idtype = WhereI(Lex, Lex.l.size - 2);
									if (it->idtype == IT::T_FUNC)
										it->idtype = IT::T_FUNC_I;

								}
								
								//if(isFuncParam) it->idtype = IT::T_CONDITION_P;
							}
							else // если у нас новая переменная
							{
								/*if (!isDec)
								{
									ADD_ERROR(305, Line, 0, dev.word[i], Error::LA);
									throw ERROR_THROW_IN
								}*/
								AddID(*it, isDecFunction, nameFunction, dev.word[i], decFunction);
								it->idfirstLE = i;
							}
							IT::Add(Lex.iT, *it);	// добавляем временную таблицу в таблицу иден.
							delete[] it;			// очищаем память
							isDec = 0;
							break;
						}
					case FN::LITERAL: case FN::INTLITERAL:	case FN::FALSELITERAL: case FN::TRUELITERAL:		// если у нас литерал
						{
							IT::Entry *it = new IT::Entry;
							char literal[] = { 'L', '0' + (count_literal / 10), '0' + (count_literal++ % 10), '\0' };	// счетчик(имя) литерала
							AddID(*it, false, "", literal, "");
							it->idfirstLE = i;
							if (Lex.l.table[Lex.l.size - 2].lexema == '(' || Lex.l.table[Lex.l.size - 2].lexema == ',' ||
								Lex.l.table[Lex.l.size - 2].lexema == 'b')
								it->idtype = WhereI(Lex, Lex.l.size - 2);
							else	it->idtype = IT::T_LITERAL;
							strcpy(it->value.val, dev.word[i]);
							switch (FST_ARRAY[k].automatName)
							{
							case FN::INTLITERAL: case FN::FALSELITERAL: case FN::TRUELITERAL:	it->iddatatype = IT::DT_INT; break;
							case FN::LITERAL:	it->iddatatype = IT::DT_STR;	it->value.len = strlen(dev.word[i]); break;
							}
							IT::Add(Lex.iT, *it);
							delete[] it;
							break;
						}
					}
					break;
				}
			}
			else		// очищаем наш стек если у нас конец строки 
			{
				isInitialization = false;
				if (!LexStack.empty())	while (!LexStack.empty())	LexStack.pop();
				Line++;
				break;
			}
		}	
	}
	if(beginCount == 0) throw GET_ERROR(306, 6)
	else if(beginCount > 1) throw GET_ERROR(307, 6);
	Error::ERRORS error = ERROR_THROW_IN;
	if (error.count > 0)	Log::WriteErrors(log, error);
	LT::ShowLT(Lex.l, param, log);
	IT::ShowIT(Lex.iT, Lex.l, param, log);
	return Lex;
};