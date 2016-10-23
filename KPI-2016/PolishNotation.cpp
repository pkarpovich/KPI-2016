#include "stdafx.h"

int PN::getPriority(char symbol)
{
	switch (symbol)
	{
		case '*': case '/': return 3;
		case '+': case '-': return 2;
		case '(': case ')': return 1;
	}
}

void PN::PolishNotation(LA::LexAnaliz &Lex, Log::LOG log)
{
	stack<LT::Entry> stack;
	LT::Entry temp;		// запрещенная лексема, все лишние элементы будут заменяться на нее
	temp.idxTI = -1; temp.lexema = LEX_FORBIDDEN; temp.sn = -1;	// инициализация запрещенной лексемы
	bool isFunc = 0,	// если в строке есть функция
		 isPN = 0;		// выполнение преобразований 
	int paramCount = 0;	// колличество параметров функции
	for (int i = 0; i < Lex.l.size; i++)
	{															// если у нас =, print, return, то начинаем ОПЗ
		if (Lex.l.table[i].lexema == LEX_EQUALLU || Lex.l.table[i].lexema == LEX_SOUT || Lex.l.table[i].lexema == LEX_RETURN)
		{
			int posLT = ++i;	// позиция в таблице лексем, т.к размер после ОПЗ может измениться
			while (Lex.l.table[i].lexema != LEX_SEMICOLON)	// до тех пор, пока не встретим ;
			{
				switch (Lex.l.table[i].lexema)
				{
					case LEX_VARIABLE: case LEX_LITERAL: case LEX_SOUT: case LEX_RETURN:	// если у нас =, print, return
					{
						if (Lex.iT.table[Lex.l.table[i].idxTI].idtype != IT::F)	// сразу мы проверяем что бы у нас небыло имени функции
						{
							LT::Swap(Lex.l, posLT++, Lex.l.table[i]);	// если это не имя функции то мы отправляем буквы в выходную строку
							if(isFunc)	paramCount++;	// если это параметр, то мы увеличиваем счетчик параметров
						}							
						else	// если у нас имя функции, мы его игнорируем
						{
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
							LT::Swap(Lex.l, posLT++, stack.top());	// выталкиваем со стека в выходную строку
							stack.pop();
						}
						stack.pop();	// уничтожаем )
						if (isFunc)		// если это были парметры функции
						{
							Lex.l.table[i].lexema = LEX_AT; Lex.l.table[i].idxTI = paramCount;	// колличество параметров записываем в номер табл. иден.
							LT::Swap(Lex.l, posLT++, Lex.l.table[i]); // записываем в выходную строку @
							paramCount = 0; isFunc = false;	// обнуляем флаги
						}						
						break;
					}
					case LEX_ACTION:	// если у нас знаки действия
					{
						if (stack.empty())	// если у наш стек пустой
						{
							stack.push(Lex.l.table[i]);	// записываем наш знак туда
						}
						else
						{		// если приоритет лексемы меньше приоритета лексемы в стеке
							while ((getPriority(Lex.l.table[i].lexema) <= getPriority(stack.top().lexema)))	
							{
								LT::Swap(Lex.l, posLT++, stack.top());	// выталкиваем со стека в выходную строку, до тех пор пока условие выплняется
								stack.pop();
							};	// если наш стек пуст или приоритет лексемы больше приоритета лексемы в стеке
							if (stack.empty() || ((getPriority(Lex.l.table[i].lexema) > getPriority(stack.top().lexema))))
							{
								stack.push(Lex.l.table[i]);	// запихиваем лексему в стек
							}
							break;
						}
					}
				}
				i++;	// переходим к след лексеме
			}
			while (!stack.empty())	// если наш стек не пустой
			{
				LT::Swap(Lex.l, posLT++, stack.top());	// выталкиваем все в выходную строку
				stack.pop();
			}
			while (posLT != i)	// если после ОПЗ размер талицы уменьшился
			{
				temp.sn = Lex.l.table[posLT].sn;
				LT::Swap(Lex.l, posLT++, temp);	// заменяем удаленные символы запрещенной лексемой
			}
			isPN = true;
		}
	}
	if (isPN == true)
	{
		cout << "Польская запись построенна." << endl;
		(*log.stream) << "Польская запись построенна." << endl;
	}
}