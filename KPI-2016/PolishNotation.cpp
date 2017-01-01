#include "stdafx.h"

namespace PN
{
	bool needPN(LA::LexAnaliz Lex, Log::LOG Log, int sn)
	{
		for (int i = 0; i < Lex.l.size; i++)
		{
			if (Lex.l.table[i].sn == sn)
			{
				while (Lex.l.table[i].sn == sn)
				{
					if (Lex.iT.table[Lex.l.table[i].idxTI].idtype == IT::T_FUNC_I)
					{
						PolishNotation(Lex, Log, i+2);
						return true;
					}
					else if (Lex.l.table[i].lexema == LEX_ACTION || Lex.l.table[i].lexema == LEX_INC)
					{
						PolishNotation(Lex, Log, i+2);
						return true;
					}
					else if (Lex.iT.table[Lex.l.table[i].idxTI].idtype == IT::DT_STR)	return false;
					else if (Lex.l.table[i].lexema == LEX_SOUT) return false;
					i++;
				}
				return false;
			}
		}
		return false;
	}

	void PolishNotation(LA::LexAnaliz &Lex, Log::LOG log, int i)
	{
		bool check = false;
		while (!check)
			if (Lex.l.table[--i].lexema == LEX_EQUALLU)				check = true;
		Parm::PARM param;
		param.LT = true;
		stack<LT::Entry> stack;
		LT::Entry temp;		// запрещенная лексема, все лишние элементы будут заменяться на нее
		temp.idxTI = -1; temp.lexema = LEX_FORBIDDEN; temp.sn = -1;	// инициализация запрещенной лексемы
		bool isFunc = 0,	// если в строке есть функция
			isPN = 0,		// выполнение преобразований
			isInvoke = 0;
		int paramCount = 0;	// колличество параметров функции
		int posLT = i;
		int sn = Lex.l.table[i].sn;
		while (Lex.l.table[i].sn == sn)
		{															// если у нас =, print, return, то начинаем ОПЗ
			switch (Lex.l.table[i].lexema)
			{
			case LEX_VARIABLE: case LEX_LITERAL: case LEX_SOUT: case LEX_RETURN:
			{
				if (Lex.iT.table[Lex.l.table[i].idxTI].idtype == IT::T_FUNC_I)
				{
					stack.push(Lex.l.table[i]);
					while (Lex.l.table[++i].lexema != LEX_RIGHTTHESIS)
					{
						if(Lex.l.table[i].lexema == LEX_VARIABLE || Lex.l.table[i].lexema == LEX_LITERAL)
							LT::Swap(Lex.l, ++posLT, Lex.l.table[i]);
					}
					LT::Swap(Lex.l, ++posLT, stack.top());
					stack.pop();
					break;
				}
				if (Lex.iT.table[Lex.l.table[i].idxTI].idtype != IT::T_FUNC)	// сразу мы проверяем что бы у нас небыло имени функции
				{
					LT::Swap(Lex.l, ++posLT, Lex.l.table[i]);	// если это не имя функции то мы отправляем буквы в выходную строку
					if (isFunc)	paramCount++;	// если это параметр, то мы увеличиваем счетчик параметров
				}
				else	// если у нас имя функции, мы его игнорируем
				{
					LT::Swap(Lex.l, ++posLT, Lex.l.table[i]);
					while (Lex.l.table[++i].lexema != ')')
						LT::Swap(Lex.l, ++posLT, Lex.l.table[i]);
					LT::Swap(Lex.l, ++posLT, Lex.l.table[i]);
					isFunc = true;
				}
				break;
			}
			case LEX_LEFTTHESIS: // если у нас (
			{
				stack.push(Lex.l.table[i]); // запихиваем ее в стек
				break;
			}
			case LEX_RIGHTTHESIS:	// если у нас )
			{
				while (stack.top().lexema != LEX_LEFTTHESIS)	// пока не встретим (
				{
					LT::Swap(Lex.l, ++posLT, stack.top());	// выталкиваем со стека в выходную строку
					stack.pop();
				}
				stack.pop();	// уничтожаем )
				if (isFunc)		// если это были парметры функции
				{
					Lex.l.table[i].lexema = LEX_AT; Lex.l.table[i].idxTI = paramCount;	// колличество параметров записываем в номер табл. иден.
					LT::Swap(Lex.l, ++posLT, Lex.l.table[i]); // записываем в выходную строку @
					paramCount = 0; isFunc = false;	// обнуляем флаги
				}
				break;
			}
			case LEX_ACTION: case LEX_INC:	// если у нас знаки действия
			{
				while (!stack.empty() && Lex.l.table[i].priority <= stack.top().priority)
				{
					LT::Swap(Lex.l, ++posLT, stack.top());	// выталкиваем со стека в выходную строку, до тех пор пока условие выплняется
					stack.pop();
				};
				stack.push(Lex.l.table[i]);
				break;
			}
			}
			i++;	// переходим к след лексеме
		}
		while (!stack.empty())	// если наш стек не пустой
		{
			LT::Swap(Lex.l, ++posLT, stack.top());	// выталкиваем все в выходную строку
			stack.pop();
		}
		while (posLT != i && Lex.l.table[posLT + 1].lexema != ';')	// если после ОПЗ размер талицы уменьшился
		{
			temp.sn = Lex.l.table[posLT].sn;
			LT::Swap(Lex.l, ++posLT, temp);	// заменяем удаленные символы запрещенной лексемой
		}
		isPN = true;
	}
}