﻿#include "stdafx.h"

namespace PN
{
	bool needPN(LA::LexAnaliz Lex, Log::LOG Log, int sn)
	{
		for (int i = 0; i < Lex.l.size; i++)
		{
			if (Lex.l.table[i].sn == sn)
			{
				while (Lex.l.table[i++].sn == sn)
				{
					if (Lex.iT.table[Lex.l.table[i].idxTI].idtype == IT::T_FUNC_I)
					{
						PolishNotation(Lex, Log, i+2);
						return true;
					}
					else if (Lex.l.table[i].lexema == LEX_ACTION)
					{
						PolishNotation(Lex, Log, i+2);
						return true;
					}						
				}
				return false;
			}
		}
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
			isPN = 0;		// выполнение преобразований 
		int paramCount = 0;	// колличество параметров функции
		int posLT = i;
		int sn = Lex.l.table[i].sn;
		while (Lex.l.table[i].sn == sn)
		{															// если у нас =, print, return, то начинаем ОПЗ
			switch (Lex.l.table[i].lexema)
			{
			case LEX_VARIABLE: case LEX_LITERAL: case LEX_SOUT: case LEX_RETURN:
			{
				if (Lex.iT.table[Lex.l.table[i].idxTI].idtype != IT::T_FUNC && Lex.iT.table[Lex.l.table[i].idxTI].idtype != IT::T_FUNC_I)	// сразу мы проверяем что бы у нас небыло имени функции
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
			case LEX_ACTION:	// если у нас знаки действия
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
		if (isPN == true)
		{
			cout << "Польская запись построенна." << endl;
			(*log.stream) << "Польская запись построенна." << endl;
		}
	}
}
//void PN::PolishNotation(LA::LexAnaliz &Lex, Log::LOG log)
//{
//	Parm::PARM param;
//	param.LT = true;
//	stack<LT::Entry> stack;
//	LT::Entry temp;		// запрещенная лексема, все лишние элементы будут заменяться на нее
//	temp.idxTI = -1; temp.lexema = LEX_FORBIDDEN; temp.sn = -1;	// инициализация запрещенной лексемы
//	LT::Entry genTemp;
//	genTemp.idxTI = -1; genTemp.lexema = '}'; genTemp.sn = -1;
//	bool isFunc = 0,	// если в строке есть функция
//		 isPN = 0;		// выполнение преобразований 
//	int paramCount = 0;	// колличество параметров функции
//	int oldPos;
//	for (int i = 0; i < Lex.l.size; i++)
//	{															// если у нас =, print, return, то начинаем ОПЗ
//		if (Lex.l.table[i].lexema == LEX_EQUALLU || Lex.l.table[i].lexema == LEX_SOUT || Lex.l.table[i].lexema == LEX_RETURN)
//		{
//			int posLT = ++i;	// позиция в таблице лексем, т.к размер после ОПЗ может измениться
//			genTemp.sn = Lex.l.table[i].sn;
//			//oldPos = i - 1;
//			//++i;
//			while (Lex.l.table[i].lexema != LEX_SEMICOLON && Lex.l.table[i].lexema != LEX_ENDL)	// до тех пор, пока не встретим ;
//			{
//				switch (Lex.l.table[i].lexema)
//				{
//				case LEX_VARIABLE: case LEX_LITERAL: case LEX_SOUT: case LEX_RETURN:	// если у нас =, print, return
//					{
//						if (Lex.iT.table[Lex.l.table[i].idxTI].idtype != IT::F)	// сразу мы проверяем что бы у нас небыло имени функции
//						{
//							LT::Swap(Lex.l, posLT++, Lex.l.table[i]);	// если это не имя функции то мы отправляем буквы в выходную строку
//							if(isFunc)	paramCount++;	// если это параметр, то мы увеличиваем счетчик параметров
//						}							
//						else	// если у нас имя функции, мы его игнорируем
//						{
//							isFunc = true;
//						}
//						break;
//					}
//					case LEX_LEFTTHESIS: // если у нас (
//					{
//						stack.push(Lex.l.table[i]); // запихиваем ее в стек
//						break;
//					}	
//					case LEX_RIGHTTHESIS:	// если у нас )
//					{
//						while (stack.top().lexema != LEX_LEFTTHESIS)	// пока не встретим (
//						{
//							LT::Swap(Lex.l, posLT++, stack.top());	// выталкиваем со стека в выходную строку
//							stack.pop();
//						}
//						stack.pop();	// уничтожаем )
//						if (isFunc)		// если это были парметры функции
//						{
//							Lex.l.table[i].lexema = LEX_AT; Lex.l.table[i].idxTI = paramCount;	// колличество параметров записываем в номер табл. иден.
//							LT::Swap(Lex.l, posLT++, Lex.l.table[i]); // записываем в выходную строку @
//							paramCount = 0; isFunc = false;	// обнуляем флаги
//						}						
//						break;
//					}
//					case LEX_ACTION:	// если у нас знаки действия
//					{
//						//if (stack.empty())	// если у наш стек пустой
//						//{
//							//stack.push(Lex.l.table[i]);	// записываем наш знак туда
//						//}
//						//else
//						//{		// если приоритет лексемы меньше приоритета лексемы в стеке
//
//						while (!stack.empty() && (getPriority(*Lex.iT.table[Lex.l.table[i].idxTI].id) <= getPriority(*Lex.iT.table[stack.top().idxTI].id)))
//							{
//								LT::Swap(Lex.l, posLT++, stack.top());	// выталкиваем со стека в выходную строку, до тех пор пока условие выплняется
//								stack.pop();
//							};	// если наш стек пуст или приоритет лексемы больше приоритета лексемы в стеке
//							//if (!stack.empty() || ((getPriority(*Lex.iT.table[Lex.l.table[i].idxTI].id) > getPriority(*Lex.iT.table[stack.top().idxTI].id))))
//							//{
//								stack.push(Lex.l.table[i]);	// запихиваем лексему в стек
//							//}
//							break;
//						//}
//					}
//				}
//				i++;	// переходим к след лексеме
//			}
//			while (!stack.empty())	// если наш стек не пустой
//			{
//				LT::Swap(Lex.l, posLT++, stack.top());	// выталкиваем все в выходную строку
//				stack.pop();
//			}
//			while (posLT != i)	// если после ОПЗ размер талицы уменьшился
//			{
//				temp.sn = Lex.l.table[posLT].sn;
//				LT::Swap(Lex.l, posLT++, temp);	// заменяем удаленные символы запрещенной лексемой
//			}
//			isPN = true;
//			//LT::AddTo(Lex.l, genTemp, oldPos);
//		}
//	}
//	if (isPN == true)
//	{
//		cout << "Польская запись построенна." << endl;
//		(*log.stream) << "Польская запись построенна." << endl;
//	}
//}