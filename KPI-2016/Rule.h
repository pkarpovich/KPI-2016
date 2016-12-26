#pragma once
#include "GRB.h"
#define GRB_ERROR_SERIES 600
namespace GRB
{
	Greibach greibach(NS('S'), TS('$'), 9,
		Rule(NS('S'), GRB_ERROR_SERIES, 3,   //  Структура программы
			Rule::Chain(3, TS('%'), TS('K'), NS('S')),
			Rule::Chain(10, TS('f'), TS('t'), TS('v'), TS('('), NS('F'), TS(')'), TS('['), NS('N'), TS(']'), NS('S')),
			Rule::Chain(4, TS('m'), TS('['), NS('N'), TS(']'))
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 1, 2, // параметры ф-ии
			Rule::Chain(4, TS('t'), TS('v'), TS(','), NS('F')),
			Rule::Chain(2, TS('t'), TS('v'))			
		),
		Rule(NS('C'), GRB_ERROR_SERIES + 2, 17, // возможные конструкции в циклах и условиях
			Rule::Chain(7, TS('i'), TS('('), NS('K'), TS(')'), TS('['), NS('C'), TS(']')),
			Rule::Chain(7, TS('c'), TS('('), NS('K'), TS(')'), TS('['), NS('C'), TS(']')),
			Rule::Chain(8, TS('c'), TS('('), NS('K'), TS(')'), TS('['), NS('C'), TS(']'), NS('C')),
			Rule::Chain(8, TS('i'), TS('('), NS('K'), TS(')'), TS('['), NS('C'), TS(']'), NS('C')),
			Rule::Chain(11, TS('i'), TS('('), NS('K'), TS(')'), TS('['), NS('C'), TS(']'), TS('e'), TS('['), NS('C'), TS(']')),
			Rule::Chain(12, TS('i'), TS('('), NS('K'), TS(')'), TS('['), NS('C'), TS(']'), TS('e'), TS('['), NS('C'), TS(']'), NS('C')),
			Rule::Chain(5, TS('v'), TS(':'), NS('E'), TS(';'), NS('C')),
			Rule::Chain(4, TS('v'), TS(':'), NS('E'), TS(';')),
			Rule::Chain(5, TS('v'), TS(':'), NS('E'), TS(';'), TS('e')),
			Rule::Chain(3, TS('v'), TS('d'), TS(';'), NS('C')),
			Rule::Chain(2, TS('v'), TS('d'), TS(';')),
			Rule::Chain(5, TS('p'), NS('E'), TS('n'), TS(';'), NS('C')),
			Rule::Chain(4, TS('p'), NS('E'), TS('n'), TS(';')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('C')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(3, TS('s'), NS('E'), TS(';'), NS('C')),
			Rule::Chain(4, TS('s'), NS('E'), TS(';'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 3, 12,  // возможные конструкции в ф-иях
			Rule::Chain(6, TS('t'), TS('v'), TS(':'), NS('E'), TS(';'), NS('N')),	// объявление переменной
			Rule::Chain(8, TS('c'), TS('('), NS('K'), TS(')'), TS('['), NS('C'), TS(']'), NS('N')),		// цикл
			Rule::Chain(8, TS('i'), TS('('), NS('K'), TS(')'), TS('['), NS('C'), TS(']'), NS('N')),		// условие
			Rule::Chain(12, TS('i'), TS('('), NS('K'), TS(')'), TS('['), NS('C'), TS(']'), TS('e'), TS('['), NS('C'), TS(']'), NS('N')),		// условие
			Rule::Chain(5, TS('v'), TS(':'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), NS('P'), TS(';'), NS('N')),	// вывод на экран
			Rule::Chain(5, TS('p'), NS('P'), TS('n'), TS(';'), NS('N')),
			Rule::Chain(4, TS('s'), NS('E'), TS(';'), NS('N')),	// ввод на экран
			Rule::Chain(6, TS('v'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(4, TS('v'), TS('d'), TS(';'), NS('N')),
			Rule::Chain(3, TS('r'), TS('v'), TS(';')),
			Rule::Chain(3, TS('r'), TS('l'), TS(';'))
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
		),
		Rule(NS('K'), GRB_ERROR_SERIES + 5, 4, // принимаемые параметры ф-ии
			Rule::Chain(3, TS('v'), TS('b'), TS('v')),
			Rule::Chain(3, TS('v'), TS('b'), TS('l')),
			Rule::Chain(3, TS('l'), TS('b'), TS('v')),
			Rule::Chain(3, TS('l'), TS('b'), TS('l'))
		)
	);
}