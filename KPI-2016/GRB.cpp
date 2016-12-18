#include "stdafx.h"
#include "Rule.h"
namespace GRB
{
#define NS(n) Rule::Chain::N(n)
#define TS(n) Rule::Chain::T(n)
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