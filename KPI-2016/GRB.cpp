#include "stdafx.h"
#define GRB_ERROR_SERIES 600
namespace GRB
{
#define NS(n) Rule::Chain::N(n)
#define TS(n) Rule::Chain::T(n)

	Greibach greibach(NS('S'), TS('$'), 8,
		Rule(NS('S'), GRB_ERROR_SERIES, 5,   //  Структура программы
			Rule::Chain(3, TS('%'), TS('K'), NS('S')),
			Rule::Chain(10, TS('f'), TS('t'), TS('v'), TS('('), NS('F'), TS(')'), TS('['), NS('N'), TS(']'), NS('S')),
			Rule::Chain(11, TS('f'), TS('t'), TS('v'), TS('('), NS('F'), TS(')'), TS('['), NS('N'), TS(']'), TS(';'), NS('S')),
			Rule::Chain(4, TS('m'), TS('['), NS('N'), TS(']')),
			Rule::Chain(5, TS('m'), TS('['), NS('N'), TS(']'), TS(';'))
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 1, 2, // параметры ф-ии
			Rule::Chain(2, TS('t'), TS('v')),
			Rule::Chain(4, TS('t'), TS('v'), TS(','), NS('F'))
		),
		Rule(NS('C'), GRB_ERROR_SERIES + 2, 9, // возможные конструкции в циклах и условиях
			Rule::Chain(5, TS('v'), TS(':'), NS('E'), TS(';'), NS('C')),
			Rule::Chain(4, TS('v'), TS(':'), NS('E'), TS(';')),
			Rule::Chain(5, TS('v'), TS(':'), NS('E'), TS(';'), TS('e')),
			Rule::Chain(5, TS('p'), NS('E'), TS('n'), TS(';'), NS('C')),
			Rule::Chain(4, TS('p'), NS('E'), TS('n'), TS(';')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('C')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(3, TS('s'), NS('E'), TS(';'), NS('C')),
			Rule::Chain(4, TS('s'), NS('E'), TS(';'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 3, 10,  // возможные конструкции в ф-иях
			Rule::Chain(6, TS('t'), TS('v'), TS(':'), NS('E'), TS(';'), NS('N')),	// объявление переменной
			Rule::Chain(8, TS('c'), TS('('), NS('E'), TS(')'), TS('['), NS('C'), TS(']'), NS('N')),		// цикл
			Rule::Chain(8, TS('i'), TS('('), NS('E'), TS(')'), TS('['), NS('C'), TS(']'), NS('N')),		// условие
			Rule::Chain(12, TS('i'), TS('('), NS('E'), TS(')'), TS('['), NS('C'), TS(']'), TS('e'), TS('['), NS('C'), TS(']'), NS('N')),		// условие
			Rule::Chain(5, TS('v'), TS(':'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), NS('P'), TS(';'), NS('N')),	// вывод на экран
			Rule::Chain(5, TS('p'), NS('P'), TS('n'), TS(';'), NS('N')),
			Rule::Chain(4, TS('s'), NS('E'), TS(';'), NS('N')),	// ввод на экран
			Rule::Chain(6, TS('v'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 4, 8, // ошибка в выражении
			Rule::Chain(2, TS('v'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(1, TS('v')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('v'), TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('v'), TS('('), NS('W'), TS(')'), NS('M'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 4, 4, // принимаемые параметры ф-ии
			Rule::Chain(3, TS('v'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(1, TS('v'))
		),
		Rule(NS('P'), GRB_ERROR_SERIES + 4, 2, // принимаемые параметры ф-ии
			Rule::Chain(1, TS('v')),
			Rule::Chain(1, TS('l'))
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 2, 2, // знаки
			Rule::Chain(2, TS('a'), NS('E')),
			Rule::Chain(2, TS('b'), NS('E'))
		)
	);

	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
	{			//конструктор цепочки - правой части правила(кол-во символов в цепочке, терминал или нетерминал...)
		nt = new GRBALPHABET[size = psize]; //цепочка терминалов
		int* p = (int*)&s; //присваиваем символ указателю p
		for (short i(0); i < psize; ++i)
			nt[i] = (GRBALPHABET)p[i]; //заполняем цепочку терминалов
	};
	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...) //конструктор правила
	{
		nn = pnn; //нетерминал
		iderror = piderror; // номер ошибки
		chains = new Chain[size = psize]; //место для цепочки
		Chain* p = &c;
		for (int i(0); i < size; i++)
			chains[i] = p[i]; //заполняем множество цепочек
	};
	Greibach::Greibach(GRBALPHABET pstatrN, GRBALPHABET pstbottom, short psize, Rule r, ...)
	{
		startN = pstatrN; //стартовый символ
		stbottomT = pstbottom; //дно стека
		rules = new Rule[size = psize]; //выделяем память
		Rule* p = &r;
		for (int i(0); i < size; i++) //заполняем правила
			rules[i] = p[i];
	};

	Greibach getGreibach() { return greibach; };//получить грамматику
	short Greibach::getRule(GRBALPHABET pnn, Rule& prule) //получить правило
	{
		short rc = -1, k = 0;
		while (k < size && rules[k].nn != pnn)
			k++; //пока К меньше количества правил и пока левый символ правила не равен парметру ф-ции
		if (k < size)
			prule = rules[rc = k]; //возвращаемое правило граматики равно правилу с индексом К
		return rc; //возвращается номер правила или -1
	};

	Rule Greibach::getRule(short n) //получить правило по номеру
	{
		Rule rc; //создаём правило rc
		if (n < size) 
			rc = rules[n]; //присваиваем правилу rc правило n
		return rc; //возвращаем созданное правило
	};

	char* Rule::getCRule(char* b, short nchain) // получить правило в виде N->цепочка
	{
		char bchain[200]; //строка
		b[0] = Chain::alphabet_to_char(nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00; //терминал -> 
		chains[nchain].getCChain(bchain); //получает правую сторонц правила
		strcat(b, bchain); //добавляем строку 
		return b;
	};

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{							//получить следующую за j подходящую цепочку, вернуть её номер или -1 
		short rc = -1;
		while (j < size && chains[j].nt[0] != t) ++j;
		rc = (j < size ? j : -1);
		if (rc >= 0) pchain = chains[rc];
		return rc;
	};

	char* Rule::Chain::getCChain(char* b) // получить правую сторону правила
	{
		for (int i(0); i < size; i++) b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	};

}