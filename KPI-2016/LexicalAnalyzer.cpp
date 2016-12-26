#include "stdafx.h"
#include "Automatic.h"
#define It Lex.iT.table
#define Lt Lex.l.table
#define Ls Lex.l.size
#define FName FST_ARRAY[k].automatName

void LA::AddID(IT::Entry iT, bool isDecFunction, char pref[255], char word[255], char decFunction[ID_MAXSIZE])
{
	if (strlen(decFunction) > ID_MAXSIZE)	decFunction[ID_MAXSIZE] = '\0';	// урезаем имя протатипа функции
	if (isDecFunction)
	{
		strcpy_s(iT.id, ID_MAXSIZE, word);
		if (iT.idtype != IT::T_FUNC)
		{
			strcpy_s(iT.prefId, ID_MAXSIZE, decFunction);
			strcat_s(iT.prefId, ID_MAXSIZE, word);
		}
		else	strcpy_s(iT.prefId, ID_MAXSIZE, word);
	}
	else
	{
		strcpy_s(iT.id, ID_MAXSIZE, word);		// копирываем ид
		if (iT.idtype != IT::T_FUNC)
		{
			//strcpy(iT.prefId, "kpi");
			strcpy_s(iT.prefId, ID_MAXSIZE, pref);	// добавляем префикс
			strcat_s(iT.prefId, ID_MAXSIZE+20, word);	// добавляем к префиксу слово
		}
		else
		{
			strcpy_s(iT.prefId, ID_MAXSIZE, "kpi");
			strcat_s(iT.prefId, ID_MAXSIZE, word);
		}
	}
	
}

void LA::AddSTF(LexAnaliz &Lex, char *name, int i, int paramCount)
{
	IT::Entry *it = new IT::Entry;
	AddID(*it, false, "kpi", name, "");
	it->idfirstLE = i;
	it->idtype = IT::T_FUNC;
	it->paramCount = paramCount;
	it->iddatatype = IT::DT_INT;
	IT::Add(Lex.iT, *it);	// добавляем временную таблицу в таблицу иден.
	delete[] it;			// очищаем память
}

int LA::WhereBrace(LexAnaliz Lex, int i)
{
	char lastLexem = Lt[Ls - 1].lexema;
	for (int k = i; k > -1; k--)
	{
		switch (Lt[k].lexema)
		{
		case LEX_FUNCTION: 
			if (It[Lt[k + 2].idxTI].pointer)	return IT::T_FUNC_I;
			return IT::T_FUNC;
		case LEX_BEGIN_FUNCTION:
			return IT::T_MAINFUNC;
		case LEX_RIGHTBRACE:	
			while (Lt[k].lexema != LEX_CONDITION && Lt[k].lexema != LEX_CIRCLE)
			{
				k--;
			};
			break;
		case LEX_CONDITION:		return IT::T_CONDITION;
		case LEX_ELSE: return IT::T_ELSE;
		case LEX_CIRCLE: return IT::T_CIRCLE;
		case LEX_RETURN: return IT::T_FUNC;
		case LEX_VARIABLE: if (It[Lt[k].idxTI].idtype == IT::T_FUNC_I || It[Lt[k].idxTI].idtype == IT::T_FUNC_IP) return IT::T_FUNC_I;
		case LEX_LITERAL: if (It[Lt[k].idxTI].idtype == IT::T_FUNC_IP) return IT::T_FUNC_I; break;
		}
	}
	return 0;
}

void LA::funcParamCount(LexAnaliz &Lex)
{
	int i = Lex.iT.size, count = 0;
	while (It[i--].idtype != IT::T_FUNC)
		if (It[i].idtype == IT::T_FUNC_P)	count++;
	It[i+1].paramCount = count;
}

int LA::WhereI(LexAnaliz Lex, int k)
{
	for (int i = k; i > -1; i--)
	{
		if (Lt[i].lexema == LEX_LEFTBRACE)
		{
			return IT::T_VAR;
		}
		else if (Lt[i].lexema == LEX_LEFTTHESIS)
		{
			if (It[Lt[i - 1].idxTI].pointer)	return IT::T_FUNC_IP;
			if (Lt[i - 1].lexema == LEX_CONDITION || Lt[i - 1].lexema == LEX_CIRCLE ||
				Lt[i - 1].lexema == LEX_VARIABLE)
			{
				switch (Lt[i].braceType)
				{
				case IT::T_CONDITION:	return IT::T_CONDITION_P;
				case IT::T_CIRCLE:		return IT::T_CIRCLE_P;
				case IT::T_FUNC:		return IT::T_FUNC_P;
				case IT::T_FUNC_I:		return IT::T_FUNC_IP;
				default:				return Lt[i].braceType;
				}
			}
			
		}
		else if (Lt[i].lexema == LEX_RIGHTTHESIS)
		{
			while (Lt[i--].lexema != LEX_LEFTTHESIS)
			{
			};
		}
		else if (Lt[i].lexema == LEX_FUNCTION)
		{
			return IT::T_FUNC;
		}
		else if (Lt[i].lexema == LEX_VARIABLE && Lt[i + 1].lexema == LEX_LEFTTHESIS)
		{
			return IT::T_FUNC_I;
		}
	}
	return 0;
}

LA::LexAnaliz LA::LexicalAnaliz(Div::Divide dev, Log::LOG log, Parm::PARM param)
{
	LA::LexAnaliz Lex;								// структура в которой будут хранится заполненная таблица лексем и иден.
	LT::Entry e;									// временная лексема
	Lex.l = LT::Create(LT_MAXSIZE);					// создаем таблицу лексем
	Lex.iT = IT::Create(TI_MAXSIZE);				// создаем таблицу иден.
	stack<FST::AUTOMAT_NAME> LexStack;				// наш стек, что бы узнавать что было до иден.
	stack<int> stack;
	Error::ErrorTable eT(ERROR_MAX_ENTRY);

	bool isInFunction = 0, isDecFunction = 0, isDec = 0, isCircle = 0, isInitialization = 0;		// узнаем мы в функции, или в протатипе функции
	bool isFuncParam = 0;

	int Line = 1,									// номер строки
		count_literal = 1,							// счетчик литералов
		beginCount = 0,								// проверка на begin
		libCount = 0;

	char *nameFunction = new char[ID_MAXSIZE];	// имя функции
	char *decFunction = new char[ID_MAXSIZE];	// имя протатипа функции
	for (int i = 0; i <= dev.count_word; i++)
	{
 		for (int k = 0; k < _countof(FST_ARRAY); k++)
		{
			if (*dev.word[i] != DEVIDE_LINE)	// если у нас не конец строки
			{
				if (FST::newLexem(FST_ARRAY[k].automat, dev.word[i], Line, FST_ARRAY[k].lexema,
					e, Lex.l, Lex.iT, FST_ARRAY[k].priotiry, FName))
				{
					switch (FName)
					{
					case FN::INT: case FN::STR: case FN::FUNCTION: case FN::COMMA:
						LexStack.push(FName);break;
					case FN::LBRACE: case FN::LTHESIS: case FN::RBRACE: case FN::RTHESIS:
						LexStack.push(FName);
						Lt[Ls - 1].braceType = WhereBrace(Lex, Ls - 2);
						if (Lt[Ls - 1].braceType == IT::T_FUNC_I && FName == FN::RTHESIS)
							MA::isTrueParamCount(eT, Lex);
						if (Lt[Ls - 1].braceType == IT::T_FUNC && FName == FN::LBRACE)
							LA::funcParamCount(Lex);
						break;
					case FN::KPILIB:libCount++; if (libCount > 1)	throw GET_ERROR(313);
						AddSTF(Lex, "sqrt", i, 1); AddSTF(Lex, "xpow", i, 2); break;	// подкл. стандартных функций
					case FN::BEGIN: strcpy_s(nameFunction, ID_MAXSIZE, "begin\0"); beginCount++; break;	// если у нас main
					case FN::EQUALLU: isInitialization = true; break;
					case FN::FALSENUMIDENTETIF: GET_ERROR(301, Line, -1, dev.word[i]); break;
					case FN::FIDENTETIF: GET_ERROR(300, Line, -1, dev.word[i]); break;
					case FN::IDENTETIF:										// если у нас иден.
					{
						IT::Entry *it = new IT::Entry;
						it->idtype = WhereI(Lex, Ls - 2);
						MA::isBigId(eT, Line, dev.word[i]);
						MA::isIndef(eT, Lex, dev.word[i], nameFunction);
						MA::isRedefinition(eT, Lex, dev.word[i], nameFunction);
						while (!LexStack.empty())		// смотрим в стек и узнаем что было до ид.
						{
							switch (LexStack.top())
							{
							case FN::INT: it->iddatatype = IT::DT_INT; isDec = true; break; 	// если был инт
							case FN::STR: it->iddatatype = IT::DT_STR; isDec = true; break; 	// если был стр
							case FN::FUNCTION: strcpy_s(nameFunction, ID_MAXSIZE, dev.word[i]); break;	// если была функция
							}
							LexStack.pop();	// удаляем из стека
						}
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
										it->idtype = WhereI(Lex, Ls - 2);
									if (it->idtype == IT::T_FUNC)
										it->idtype = IT::T_FUNC_I;

								}
							}
							else // если у нас новая переменная
							{
								AddID(*it, isDecFunction, nameFunction, dev.word[i], decFunction);
								it->idfirstLE = i;
							}
							IT::Add(Lex.iT, *it);	// добавляем временную таблицу в таблицу иден.
							MA::isStrFunc(eT, Lex);
							delete[] it;			// очищаем память
							isDec = 0;
							break;
						}
					case FN::LITERAL: case FN::INTLITERAL:		// если у нас литерал
						{
							IT::Entry *it = new IT::Entry;
							char literal[255];	sprintf_s(literal, 10, "L%02d", count_literal++);
							MA::isZeroDivision(eT, Lex, dev.word[i]);
							AddID(*it, false, "", literal, "");
							it->idfirstLE = i;
							if (It[Lt[Ls - 3].idxTI].idtype == IT::T_FUNC_I ||
								Lt[Ls - 2].lexema == ',' ||
								Lt[Ls - 2].lexema == 'b')
							{
								it->idtype = WhereI(Lex, Ls - 2);
							}
							else	it->idtype = IT::T_LITERAL;
							strcpy_s(it->value.val, TI_STR_MAXSIZE, dev.word[i]);
							switch (FName)
							{
							case FN::INTLITERAL: it->iddatatype = IT::DT_INT; break;
							case FN::LITERAL:	
								it->iddatatype = IT::DT_STR;	
								it->value.len = strlen(dev.word[i]);
								break;
							}
							IT::Add(Lex.iT, *it);
							MA::isStrFunc(eT, Lex);
							MA::isStrAction(eT, Lex);
							MA::isSoBigValue(eT, Lex, dev.word[i]);
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
	if (beginCount == 0) throw GET_ERROR(306)
	else if (beginCount > 1) throw GET_ERROR(307)
	if (eT.errors.size() > 0) throw GET_ERROR(-1);
	LT::ShowLT(Lex.l, param, log);
	IT::ShowIT(Lex.iT, Lex.l, param, log);
	return Lex;
};