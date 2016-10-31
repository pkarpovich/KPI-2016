#include "stdafx.h"
#include "Automatic.h"

void LA::AddID(IT::Entry iT, bool isDecFunction, char pref[255], char word[255], char decFunction[ID_MAXSIZE])
{
	if (strlen(decFunction) > ID_MAXSIZE)	decFunction[ID_MAXSIZE] = '\0';	// урезаем имя протатипа функции
	if (isDecFunction)
	{
		strcpy(iT.id, word);
		if (iT.idtype != IT::F)
		{
			strcpy(iT.prefId, decFunction);
			strcat(iT.prefId, word);
		}
		else	strcpy(iT.prefId, word);		
	}
	else
	{
		strcpy(iT.id, word);		// копирываем ид
		if (iT.idtype != IT::F)
		{
			strcpy(iT.prefId, pref);	// добавляем префикс
			strcat(iT.prefId, word);	// добавляем к префиксу слово
		}
		else	strcpy(iT.prefId, word);
	}
	
}

LA::LexAnaliz LA::LexicalAnaliz(In::Devide dev, Log::LOG log, Parm::PARM param)
{
	LA::LexAnaliz Lex;								// структура в которой будут хранится заполненная таблица лексем и иден.
	LT::Entry e;									// временная лексема
	Lex.l = LT::Create(LT_MAXSIZE);					// создаем таблицу лексем
	Lex.iT = IT::Create(TI_MAXSIZE);				// создаем таблицу иден.
	enum LexAnaliz { INT, STR, BOOL, F, DEC, SIS, COMMA, IF, CIRCLE };
	stack<LexAnaliz> LexStack;						// наш стек, что бы узнавать что было до иден.

	bool isInFunction = 0, isDecFunction = 0, isDec = 0, isCircle = 0;		// узнаем мы в функции, или в протатипе функции

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
				bool rc = FST::newLexem(FST_ARRAY[k].automat, dev.word[i], Line, FST_ARRAY[k].lexema, e, Lex.l, Lex.iT);
				if (rc)
				{
					switch (FST_ARRAY[k].automatName)
					{
					case FN::INT: {LexStack.push(LexAnaliz::INT);	break; }	// если инт
					case FN::STR: {LexStack.push(LexAnaliz::STR);	break; }	// если стринг
					case FN::BOOL: {LexStack.push(LexAnaliz::BOOL); break; }
					case FN::FUNCTION: {LexStack.push(LexAnaliz::F); break; }	// если функция
					case FN::BEGIN: {strcpy(nameFunction, "begin\0"); beginCount++; break; }	// если у нас main
					case FN::ACTION:											// если у нас знак действия
					{
						IT::Entry *it = new IT::Entry;					// временная таблица иден.
						it->idfirstLE = i;
						AddID(*it, false, "", dev.word[i], "");
						IT::Add(Lex.iT, *it);
						delete[] it;
						break;
					}
					case FN::LTHESIS: {LexStack.push(LexAnaliz::SIS); break; }		// если у нас (
					case FN::RTHESIS: {isDecFunction = 0; break; }					// если у нас )
					case FN::COMMA: {LexStack.push(LexAnaliz::COMMA); break; }		// если у нас ,
					case FN::LBRACE: {isInFunction = true; break; }					// если у нас {
					case FN::WCIRCLE: case FN::CONDITIONIF: {isCircle = true; break;}
					case FN::RBRACE: 
					{
						if (isCircle == true)	isCircle = false;
						else
						{
							strcpy(nameFunction, "begin\0");
							isInFunction = 0;
						}
						break;
					}	// если у нас }
					case FN::FALSENUMIDENTETIF: {ADD_ERROR(301, Line, 0, dev.word[i], Error::LA); throw ERROR_THROW_IN}
					case FN::FIDENTETIF: {ADD_ERROR(300, Line, 0, dev.word[i], Error::LA); throw ERROR_THROW_IN}
					case FN::IDENTETIF:										// если у нас иден.
					{
						IT::Entry *it = new IT::Entry;
						if (strlen(dev.word[i]) > ID_MAXSIZE)		// предупреждение если слишком большой иден. и усечения идент.
						{
							ADD_ERROR(302, Line, 0, dev.word[i], Error::LA);
							dev.word[i][ID_MAXSIZE] = '\0';
						}
						memset(it->value.vstr.str, TI_STR_DEFAULT, TI_STR_MAXSIZE); it->value.vstr.len = 0;
						it->value.vint = TI_INT_DEFAULT; // зануляем значение иден.
						while (!LexStack.empty())		// смотрим в стек и узнаем что было до ид.
						{
							switch (LexStack.top())
							{
							case LexAnaliz::INT: {it->iddatatype = IT::INT; if (it->idtype != IT::F) it->idtype = IT::V; isDec = true; break;}	// если был инт
								case LexAnaliz::STR: {it->iddatatype = IT::STR; if (it->idtype != IT::F) it->idtype = IT::V; isDec = true; break;}	// если был стр
								case LexAnaliz::BOOL: {it->iddatatype = IT::BOOL; if (it->idtype != IT::F) it->idtype = IT::V; isDec = true; break;}	// если был стр
								case LexAnaliz::F:			// если была функция
								{
									it->idtype = IT::F;
									if (!isInFunction)		// если мы не в функции, значит это имя функции
									{
										strcpy(nameFunction, dev.word[i]);
										if (IT::IsId(Lex.iT, isDecFunction, nameFunction, "") != TI_NULLIDX && Lex.iT.size != 0)
										{
											ADD_ERROR(303, Line, 0, dev.word[i], Error::LA);
											throw ERROR_THROW_IN
										}
									}
									else					// а если мы в функции, значит это прототип функции
									{
										strcpy(decFunction, dev.word[i]);
										isDecFunction = true;
									}
									break;
								}
								case LexAnaliz::COMMA: case LexAnaliz::SIS: it->idtype = IT::P; break; 	// если был параметр
								}
								LexStack.pop();	// удаляем из стека
							}
							if (IT::IsId(Lex.iT, isDecFunction, dev.word[i], nameFunction) != TI_NULLIDX)	// проверяем на указатель
							{
								if (isDec == true)
								{
									ADD_ERROR(304, Line, 0, dev.word[i], Error::LA);
									throw ERROR_THROW_IN
								}
								int pointerID = IT::IsId(Lex.iT, isDecFunction, dev.word[i], nameFunction);
								*it = IT::GetEntry(Lex.iT, pointerID);
								it->pointer = true;
							}
							else // если у нас новая переменная
							{
								if (!isDec)
								{
									ADD_ERROR(305, Line, 0, dev.word[i], Error::LA);
									throw ERROR_THROW_IN
								}
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
							it->idtype = IT::L;
							if (FST_ARRAY[k].automatName == FN::LITERAL)	// стринг
							{
								strcpy(it->value.vstr.str, dev.word[i]);
								it->value.vstr.len = strlen(dev.word[i]) - 2;			// т.к  '
								it->iddatatype = IT::STR;
							}
							else if (FST_ARRAY[k].automatName == FN::FALSELITERAL || FST_ARRAY[k].automatName == FN::TRUELITERAL)
							{
								strcpy(it->value.vbool, dev.word[i]);
								it->iddatatype = IT::BOOL;
							}
							else			// инт
							{
								it->value.vint = atoi(dev.word[i]);
								it->iddatatype = IT::INT;
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