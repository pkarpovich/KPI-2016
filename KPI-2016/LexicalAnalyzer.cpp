#include "stdafx.h"
#include "Automatic.h"

void LA::ToUnderCase(char destination[255], char source[255], int Line)
{
	int i;
	for (i = 0; i < strlen(source); i++)
	{
		if (source[i] >= 'A' && source[i] <= 'Z' || source[i] >= 'А' && source[i] <= 'Я')	// если у нас встретилась большая буква
		{
			source[i] += 32;	// заменяем ее на маленькую
			destination[i] = source[i];	// записываем ее в выходную строку
		}
		else	destination[i] = source[i];
	}
	destination[i] = '\0';
}

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
	enum LexAnaliz { INT, STR, F, DEC, SIS, COMMA };
	stack<LexAnaliz> LexStack;						// наш стек, что бы узнавать что было до иден.

	bool isInFunction = 0, isDecFunction = 0;		// узнаем мы в функции, или в протатипе функции

	int Line = 1,									// номер строки
		count_literal = 1;							// счетчик литералов

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
					case FN::FUNCTION: {LexStack.push(LexAnaliz::F); break; }	// если функция
					case FN::BEGIN: {strcpy(nameFunction, "main\0"); break; }	// если у нас main
					case FN::EQUALLU:											// если у нас знак действия
					{
						IT::Entry *it = new IT::Entry;					// временная таблица иден.
						it->idfirstLE = i;
						AddID(*it, false, "", dev.word[i], "");
						IT::Add(Lex.iT, *it);
						delete[] it;
						break;
					}
					case FN::RTHESIS: {LexStack.push(LexAnaliz::SIS); break; }		// если у нас (
					case FN::LTHESIS: {isDecFunction = 0; break; }					// если у нас )
					case FN::COMMA: {LexStack.push(LexAnaliz::COMMA); break; }		// если у нас ,
					case FN::RBRACE: {isInFunction = true; break; }					// если у нас {
					case FN::LBRACE: {strcpy(nameFunction, "main\0"); isInFunction = 0; break; }	// если у нас }
					case FN::IDENTETIF: case FN::FIDENTETIF:										// если у нас иден.
					{
						IT::Entry *it = new IT::Entry;
						if (FST_ARRAY[k].automatName == FN::FIDENTETIF)	// предупреждение если есть большая буква, и автомат. замена этой буквы на маленькую
						{
							NEW_WARNING(300, Line, dev.word[i], 6);
							ToUnderCase(dev.word[i], dev.word[i], Line);
						}
						else if (strlen(dev.word[i]) > ID_MAXSIZE)		// предупреждение если слишком большой иден. и усечения идент.
						{
							NEW_WARNING(301, Line, dev.word[i], 6);
							dev.word[i][ID_MAXSIZE] = '\0';
						}
						memset(it->value.vstr.str, TI_STR_DEFAULT, TI_STR_MAXSIZE); it->value.vstr.len = 0;
						it->value.vint = TI_INT_DEFAULT; // зануляем значение иден.
						while (!LexStack.empty())		// смотрим в стек и узнаем что было до ид.
						{
							switch (LexStack.top())
							{
								case LexAnaliz::INT: {it->iddatatype = IT::INT; if (it->idtype != IT::F) it->idtype = IT::V; break;	}	// если был инт
								case LexAnaliz::STR: {it->iddatatype = IT::STR; if (it->idtype != IT::F) it->idtype = IT::V; break;	}	// если был стр
								case LexAnaliz::F:			// если была функция
								{
									it->idtype = IT::F;
									if (!isInFunction)		// если мы не в функции, значит это имя функции
										strcpy(nameFunction, dev.word[i]);
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
								int pointerID = IT::IsId(Lex.iT, isDecFunction, dev.word[i], nameFunction);
								*it = IT::GetEntry(Lex.iT, pointerID);
								it->pointer = true;
							}
							else // если у нас новая переменная
							{
								AddID(*it, isDecFunction, nameFunction, dev.word[i], decFunction);
								it->idfirstLE = i;
							}
							IT::Add(Lex.iT, *it);	// добавляем временную таблицу в таблицу иден.
							delete[] it;			// очищаем память
							break;
						}
						case FN::LITERAL: case FN::INTLITERAL:			// если у нас литерал
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
	Error::ERRORS error = ERROR_THROW_IN;
	if (error.warning > 0)	Log::WriteWarning(log, error);
	LT::ShowLT(Lex.l, param, log);
	IT::ShowIT(Lex.iT, Lex.l, param, log);
	return Lex;
};