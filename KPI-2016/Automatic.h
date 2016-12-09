﻿#pragma once


FST::FST fstTypeInteger("", 4,
	FST::NODE(1, FST::RELATION('i', 1)),
	FST::NODE(1, FST::RELATION('n', 2)),
	FST::NODE(1, FST::RELATION('t', 3)),
	FST::NODE()
);

FST::FST fstTypeString("", 4,
	FST::NODE(1, FST::RELATION('s', 1)),
	FST::NODE(1, FST::RELATION('t', 2)),
	FST::NODE(1, FST::RELATION('r', 3)),
	FST::NODE()
);

FST::FST fstTypeBool("", 5,
	FST::NODE(1, FST::RELATION('b', 1)),
	FST::NODE(1, FST::RELATION('o', 2)),
	FST::NODE(1, FST::RELATION('o', 3)),
	FST::NODE(1, FST::RELATION('l', 4)),
	FST::NODE()
);

FST::FST fstTrueLiteral("", 5,
	FST::NODE(1, FST::RELATION('t', 1)),
	FST::NODE(1, FST::RELATION('r', 2)),
	FST::NODE(1, FST::RELATION('u', 3)),
	FST::NODE(1, FST::RELATION('e', 4)),
	FST::NODE()
);

FST::FST fstFalseLiteral("", 6,
	FST::NODE(1, FST::RELATION('f', 1)),
	FST::NODE(1, FST::RELATION('a', 2)),
	FST::NODE(1, FST::RELATION('l', 3)),
	FST::NODE(1, FST::RELATION('s', 4)),
	FST::NODE(1, FST::RELATION('e', 5)),
	FST::NODE()
);

FST::FST fstKeyFunction("", 5,
	FST::NODE(1, FST::RELATION('f', 1)),
	FST::NODE(1, FST::RELATION('u', 2)),
	FST::NODE(1, FST::RELATION('n', 3)),
	FST::NODE(1, FST::RELATION('c', 4)),
	FST::NODE()
);

FST::FST fstKeyDeclare("", 8,
	FST::NODE(1, FST::RELATION('d', 1)),
	FST::NODE(1, FST::RELATION('e', 2)),
	FST::NODE(1, FST::RELATION('c', 3)),
	FST::NODE(1, FST::RELATION('l', 4)),
	FST::NODE(1, FST::RELATION('a', 5)),
	FST::NODE(1, FST::RELATION('r', 6)),
	FST::NODE(1, FST::RELATION('e', 7)),
	FST::NODE()
);

FST::FST fstEndl("", 5,
	FST::NODE(1, FST::RELATION('e', 1)),
	FST::NODE(1, FST::RELATION('n', 2)),
	FST::NODE(1, FST::RELATION('d', 3)),
	FST::NODE(1, FST::RELATION('l', 4)),
	FST::NODE()
);

FST::FST fstCircleWhile("", 6,
	FST::NODE(1, FST::RELATION('w', 1)),
	FST::NODE(1, FST::RELATION('h', 2)),
	FST::NODE(1, FST::RELATION('i', 3)),
	FST::NODE(1, FST::RELATION('l', 4)),
	FST::NODE(1, FST::RELATION('e', 5)),
	FST::NODE()
);

FST::FST fstProvisionIf("", 3,
	FST::NODE(1, FST::RELATION('i', 1)),
	FST::NODE(1, FST::RELATION('f', 2)),
	FST::NODE()
);

FST::FST fstProvisionElse("", 5,
	FST::NODE(1, FST::RELATION('e', 1)),
	FST::NODE(1, FST::RELATION('l', 2)),
	FST::NODE(1, FST::RELATION('s', 3)),
	FST::NODE(1, FST::RELATION('e', 4)),
	FST::NODE()
);

FST::FST fstKeyBegin("", 6,
	FST::NODE(1, FST::RELATION('b', 1)),
	FST::NODE(1, FST::RELATION('e', 2)),
	FST::NODE(1, FST::RELATION('g', 3)),
	FST::NODE(1, FST::RELATION('i', 4)),
	FST::NODE(1, FST::RELATION('n', 5)),
	FST::NODE()
);

FST::FST fstKeySout("", 5,
	FST::NODE(1, FST::RELATION('s', 1)),
	FST::NODE(1, FST::RELATION('o', 2)),
	FST::NODE(1, FST::RELATION('u', 3)),
	FST::NODE(1, FST::RELATION('t', 4)),
	FST::NODE()
);

FST::FST fstKeySin("", 4,
	FST::NODE(1, FST::RELATION('s', 1)),
	FST::NODE(1, FST::RELATION('i', 2)),
	FST::NODE(1, FST::RELATION('n', 3)),
	FST::NODE()
);

FST::FST fstKeyReturn("", 7,
	FST::NODE(1, FST::RELATION('r', 1)),
	FST::NODE(1, FST::RELATION('e', 2)),
	FST::NODE(1, FST::RELATION('t', 3)),
	FST::NODE(1, FST::RELATION('u', 4)),
	FST::NODE(1, FST::RELATION('r', 5)),
	FST::NODE(1, FST::RELATION('n', 6)),
	FST::NODE()
);

FST::FST fstInclude("", 8,
	FST::NODE(1, FST::RELATION('i', 1)),
	FST::NODE(1, FST::RELATION('n', 2)),
	FST::NODE(1, FST::RELATION('c', 3)),
	FST::NODE(1, FST::RELATION('l', 4)),
	FST::NODE(1, FST::RELATION('u', 5)),
	FST::NODE(1, FST::RELATION('d', 6)),
	FST::NODE(1, FST::RELATION('e', 7)),
	FST::NODE()
);

FST::FST fstKPI("", 7,
	FST::NODE(1, FST::RELATION('K', 1)),
	FST::NODE(1, FST::RELATION('P', 2)),
	FST::NODE(1, FST::RELATION('I', 3)),
	FST::NODE(1, FST::RELATION('l', 4)),
	FST::NODE(1, FST::RELATION('i', 5)),
	FST::NODE(1, FST::RELATION('b', 6)),
	FST::NODE()
);

FST::FST fstMore("", 2,
	FST::NODE(1, FST::RELATION('>', 1)),
	FST::NODE()
);

FST::FST fstLess("", 2,
	FST::NODE(1, FST::RELATION('<', 1)),
	FST::NODE()
);

FST::FST fstV("", 2,
	FST::NODE(5, FST::RELATION('-', 1), FST::RELATION('+', 1), FST::RELATION('/', 1), FST::RELATION('*', 1)),
	FST::NODE()
);

FST::FST fstBoolActio("", 2,
	FST::NODE(3, FST::RELATION('>', 1), FST::RELATION('<', 1), FST::RELATION('=', 1)),
	FST::NODE()
);


FST::FST fstEqually("", 2,
	FST::NODE(1, FST::RELATION(':', 1)),
	FST::NODE()
);

FST::FST fstLeftThesis("", 2,
	FST::NODE(1, FST::RELATION('(', 1)),
	FST::NODE()
);

FST::FST fstRightThesis("", 2,
	FST::NODE(1, FST::RELATION(')', 1)),
	FST::NODE()
);

FST::FST fstSemiColon("", 2,
	FST::NODE(1, FST::RELATION(';', 1)),
	FST::NODE()
);

FST::FST fstComma("", 2,
	FST::NODE(1, FST::RELATION(',', 1)),
	FST::NODE()
);

FST::FST fstLeftBrace("", 2,
	FST::NODE(1, FST::RELATION('[', 1)),
	FST::NODE()
);

FST::FST fstRightBrace("", 2,
	FST::NODE(1, FST::RELATION(']', 1)),
	FST::NODE()
);
FST::FST fstIdentif("", 3,
	FST::NODE(78,
		FST::RELATION('a', 0), FST::RELATION('a', 1), FST::RELATION('a', 2),
		FST::RELATION('b', 0), FST::RELATION('b', 1), FST::RELATION('b', 2),
		FST::RELATION('c', 0), FST::RELATION('c', 1), FST::RELATION('c', 2),
		FST::RELATION('d', 0), FST::RELATION('d', 1), FST::RELATION('d', 2),
		FST::RELATION('e', 0), FST::RELATION('e', 1), FST::RELATION('e', 2),
		FST::RELATION('f', 0), FST::RELATION('f', 1), FST::RELATION('f', 2),
		FST::RELATION('g', 0), FST::RELATION('g', 1), FST::RELATION('g', 2),
		FST::RELATION('h', 0), FST::RELATION('h', 1), FST::RELATION('h', 2),
		FST::RELATION('i', 0), FST::RELATION('i', 1), FST::RELATION('i', 2),
		FST::RELATION('j', 0), FST::RELATION('j', 1), FST::RELATION('j', 2),
		FST::RELATION('k', 0), FST::RELATION('k', 1), FST::RELATION('k', 2),
		FST::RELATION('l', 0), FST::RELATION('l', 1), FST::RELATION('l', 2),
		FST::RELATION('m', 0), FST::RELATION('m', 1), FST::RELATION('m', 2),
		FST::RELATION('n', 0), FST::RELATION('n', 1), FST::RELATION('n', 2),
		FST::RELATION('o', 0), FST::RELATION('o', 1), FST::RELATION('o', 2),
		FST::RELATION('p', 0), FST::RELATION('p', 1), FST::RELATION('p', 2),
		FST::RELATION('q', 0), FST::RELATION('q', 1), FST::RELATION('q', 2),
		FST::RELATION('r', 0), FST::RELATION('r', 1), FST::RELATION('r', 2),
		FST::RELATION('s', 0), FST::RELATION('s', 1), FST::RELATION('s', 2),
		FST::RELATION('t', 0), FST::RELATION('t', 1), FST::RELATION('t', 2),
		FST::RELATION('u', 0), FST::RELATION('u', 1), FST::RELATION('u', 2),
		FST::RELATION('v', 0), FST::RELATION('v', 1), FST::RELATION('v', 2),
		FST::RELATION('w', 0), FST::RELATION('w', 1), FST::RELATION('w', 2),
		FST::RELATION('x', 0), FST::RELATION('x', 1), FST::RELATION('x', 2),
		FST::RELATION('y', 0), FST::RELATION('y', 1), FST::RELATION('y', 2),
		FST::RELATION('z', 0), FST::RELATION('z', 1), FST::RELATION('z', 2)),
	FST::NODE(104,
		FST::RELATION('A', 1), FST::RELATION('A', 2), FST::RELATION('a', 1), FST::RELATION('a', 2),
		FST::RELATION('B', 1), FST::RELATION('B', 2), FST::RELATION('b', 1), FST::RELATION('b', 2),
		FST::RELATION('C', 1), FST::RELATION('C', 2), FST::RELATION('c', 1), FST::RELATION('c', 2),
		FST::RELATION('D', 1), FST::RELATION('D', 2), FST::RELATION('d', 1), FST::RELATION('d', 2),
		FST::RELATION('E', 1), FST::RELATION('E', 2), FST::RELATION('e', 1), FST::RELATION('e', 2),
		FST::RELATION('F', 1), FST::RELATION('F', 2), FST::RELATION('f', 1), FST::RELATION('f', 2),
		FST::RELATION('G', 1), FST::RELATION('G', 2), FST::RELATION('g', 1), FST::RELATION('g', 2),
		FST::RELATION('H', 1), FST::RELATION('H', 2), FST::RELATION('h', 1), FST::RELATION('h', 2),
		FST::RELATION('I', 1), FST::RELATION('I', 2), FST::RELATION('i', 1), FST::RELATION('i', 2),
		FST::RELATION('J', 1), FST::RELATION('J', 2), FST::RELATION('j', 1), FST::RELATION('j', 2),
		FST::RELATION('K', 1), FST::RELATION('K', 2), FST::RELATION('k', 1), FST::RELATION('k', 2),
		FST::RELATION('L', 1), FST::RELATION('L', 2), FST::RELATION('l', 1), FST::RELATION('l', 2),
		FST::RELATION('M', 1), FST::RELATION('M', 2), FST::RELATION('m', 1), FST::RELATION('m', 2),
		FST::RELATION('N', 1), FST::RELATION('N', 2), FST::RELATION('n', 1), FST::RELATION('n', 2),
		FST::RELATION('O', 1), FST::RELATION('O', 2), FST::RELATION('o', 1), FST::RELATION('o', 2),
		FST::RELATION('P', 1), FST::RELATION('P', 2), FST::RELATION('p', 1), FST::RELATION('p', 2),
		FST::RELATION('Q', 1), FST::RELATION('Q', 2), FST::RELATION('q', 1), FST::RELATION('q', 2),
		FST::RELATION('R', 1), FST::RELATION('R', 2), FST::RELATION('r', 1), FST::RELATION('r', 2),
		FST::RELATION('S', 1), FST::RELATION('S', 2), FST::RELATION('s', 1), FST::RELATION('s', 2),
		FST::RELATION('T', 1), FST::RELATION('T', 2), FST::RELATION('t', 1), FST::RELATION('t', 2),
		FST::RELATION('U', 1), FST::RELATION('U', 2), FST::RELATION('u', 1), FST::RELATION('u', 2),
		FST::RELATION('V', 1), FST::RELATION('V', 2), FST::RELATION('v', 1), FST::RELATION('v', 2),
		FST::RELATION('W', 1), FST::RELATION('W', 2), FST::RELATION('w', 1), FST::RELATION('w', 2),
		FST::RELATION('X', 1), FST::RELATION('X', 2), FST::RELATION('x', 1), FST::RELATION('x', 2),
		FST::RELATION('Y', 1), FST::RELATION('Y', 2), FST::RELATION('y', 1), FST::RELATION('y', 2),
		FST::RELATION('Z', 1), FST::RELATION('Z', 2), FST::RELATION('z', 1), FST::RELATION('z', 2)),
	FST::NODE()
);
FST::FST fstFalseIdentif("", 3,
	FST::NODE(52,
		FST::RELATION('A', 0), FST::RELATION('A', 1),
		FST::RELATION('B', 0), FST::RELATION('B', 1),
		FST::RELATION('C', 0), FST::RELATION('C', 1),
		FST::RELATION('D', 0), FST::RELATION('D', 1),
		FST::RELATION('E', 0), FST::RELATION('E', 1),
		FST::RELATION('F', 0), FST::RELATION('F', 1),
		FST::RELATION('G', 0), FST::RELATION('G', 1),
		FST::RELATION('H', 0), FST::RELATION('H', 1),
		FST::RELATION('I', 0), FST::RELATION('I', 1),
		FST::RELATION('J', 0), FST::RELATION('J', 1),
		FST::RELATION('K', 0), FST::RELATION('K', 1),
		FST::RELATION('L', 0), FST::RELATION('L', 1),
		FST::RELATION('M', 0), FST::RELATION('M', 1),
		FST::RELATION('N', 0), FST::RELATION('N', 1),
		FST::RELATION('O', 0), FST::RELATION('O', 1),
		FST::RELATION('P', 0), FST::RELATION('P', 1),
		FST::RELATION('Q', 0), FST::RELATION('Q', 1),
		FST::RELATION('R', 0), FST::RELATION('R', 1),
		FST::RELATION('S', 0), FST::RELATION('S', 1),
		FST::RELATION('T', 0), FST::RELATION('T', 1),
		FST::RELATION('U', 0), FST::RELATION('U', 1),
		FST::RELATION('V', 0), FST::RELATION('V', 1),
		FST::RELATION('W', 0), FST::RELATION('W', 1),
		FST::RELATION('X', 0), FST::RELATION('X', 1),
		FST::RELATION('Y', 0), FST::RELATION('Y', 1),
		FST::RELATION('Z', 0), FST::RELATION('Z', 1)),
	FST::NODE(124,
		FST::RELATION('a', 1), FST::RELATION('a', 2),
		FST::RELATION('b', 1), FST::RELATION('b', 2),
		FST::RELATION('c', 1), FST::RELATION('c', 2),
		FST::RELATION('d', 1), FST::RELATION('d', 2),
		FST::RELATION('e', 1), FST::RELATION('e', 2),
		FST::RELATION('f', 1), FST::RELATION('f', 2),
		FST::RELATION('g', 1), FST::RELATION('g', 2),
		FST::RELATION('h', 1), FST::RELATION('h', 2),
		FST::RELATION('i', 1), FST::RELATION('i', 2),
		FST::RELATION('j', 1), FST::RELATION('j', 2),
		FST::RELATION('k', 1), FST::RELATION('k', 2),
		FST::RELATION('l', 1), FST::RELATION('l', 2),
		FST::RELATION('m', 1), FST::RELATION('m', 2),
		FST::RELATION('n', 1), FST::RELATION('n', 2),
		FST::RELATION('o', 1), FST::RELATION('o', 2),
		FST::RELATION('p', 1), FST::RELATION('p', 2),
		FST::RELATION('q', 1), FST::RELATION('q', 2),
		FST::RELATION('r', 1), FST::RELATION('r', 2),
		FST::RELATION('s', 1), FST::RELATION('s', 2),
		FST::RELATION('t', 1), FST::RELATION('t', 2),
		FST::RELATION('u', 1), FST::RELATION('u', 2),
		FST::RELATION('v', 1), FST::RELATION('v', 2),
		FST::RELATION('w', 1), FST::RELATION('w', 2),
		FST::RELATION('x', 1), FST::RELATION('x', 2),
		FST::RELATION('y', 1), FST::RELATION('y', 2),
		FST::RELATION('z', 1), FST::RELATION('z', 2),
		FST::RELATION('A', 1), FST::RELATION('A', 2),
		FST::RELATION('B', 1), FST::RELATION('B', 2),
		FST::RELATION('C', 1), FST::RELATION('C', 2),
		FST::RELATION('D', 1), FST::RELATION('D', 2),
		FST::RELATION('E', 1), FST::RELATION('E', 2),
		FST::RELATION('F', 1), FST::RELATION('F', 2),
		FST::RELATION('G', 1), FST::RELATION('G', 2),
		FST::RELATION('H', 1), FST::RELATION('H', 2),
		FST::RELATION('I', 1), FST::RELATION('I', 2),
		FST::RELATION('J', 1), FST::RELATION('J', 2),
		FST::RELATION('K', 1), FST::RELATION('K', 2),
		FST::RELATION('L', 1), FST::RELATION('L', 2),
		FST::RELATION('M', 1), FST::RELATION('M', 2),
		FST::RELATION('N', 1), FST::RELATION('N', 2),
		FST::RELATION('O', 1), FST::RELATION('O', 2),
		FST::RELATION('P', 1), FST::RELATION('P', 2),
		FST::RELATION('Q', 1), FST::RELATION('Q', 2),
		FST::RELATION('R', 1), FST::RELATION('R', 2),
		FST::RELATION('S', 1), FST::RELATION('S', 2),
		FST::RELATION('T', 1), FST::RELATION('T', 2),
		FST::RELATION('U', 1), FST::RELATION('U', 2),
		FST::RELATION('V', 1), FST::RELATION('V', 2),
		FST::RELATION('W', 1), FST::RELATION('W', 2),
		FST::RELATION('X', 1), FST::RELATION('X', 2),
		FST::RELATION('Y', 1), FST::RELATION('Y', 2),
		FST::RELATION('Z', 1), FST::RELATION('Z', 2),
		FST::RELATION('0', 1), FST::RELATION('0', 2),
		FST::RELATION('1', 1), FST::RELATION('1', 2),
		FST::RELATION('2', 1), FST::RELATION('2', 2),
		FST::RELATION('3', 1), FST::RELATION('3', 2),
		FST::RELATION('4', 1), FST::RELATION('4', 2),
		FST::RELATION('5', 1), FST::RELATION('5', 2),
		FST::RELATION('6', 1), FST::RELATION('6', 2),
		FST::RELATION('7', 1), FST::RELATION('7', 2),
		FST::RELATION('8', 1), FST::RELATION('8', 2),
		FST::RELATION('9', 1), FST::RELATION('9', 2)),
	FST::NODE()
);

FST::FST fstFalseNumIdentif("", 2,
	FST::NODE(124,
		FST::RELATION('a', 0), FST::RELATION('a', 1),
		FST::RELATION('b', 0), FST::RELATION('b', 1),
		FST::RELATION('c', 0), FST::RELATION('c', 1),
		FST::RELATION('d', 0), FST::RELATION('d', 1),
		FST::RELATION('e', 0), FST::RELATION('e', 1),
		FST::RELATION('f', 0), FST::RELATION('f', 1),
		FST::RELATION('g', 0), FST::RELATION('g', 1),
		FST::RELATION('h', 0), FST::RELATION('h', 1),
		FST::RELATION('i', 0), FST::RELATION('i', 1),
		FST::RELATION('j', 0), FST::RELATION('j', 1),
		FST::RELATION('k', 0), FST::RELATION('k', 1),
		FST::RELATION('l', 0), FST::RELATION('l', 1),
		FST::RELATION('m', 0), FST::RELATION('m', 1),
		FST::RELATION('n', 0), FST::RELATION('n', 1),
		FST::RELATION('o', 0), FST::RELATION('o', 1),
		FST::RELATION('p', 0), FST::RELATION('p', 1),
		FST::RELATION('q', 0), FST::RELATION('q', 1),
		FST::RELATION('r', 0), FST::RELATION('r', 1),
		FST::RELATION('s', 0), FST::RELATION('s', 1),
		FST::RELATION('t', 0), FST::RELATION('t', 1),
		FST::RELATION('u', 0), FST::RELATION('u', 1),
		FST::RELATION('v', 0), FST::RELATION('v', 1),
		FST::RELATION('w', 0), FST::RELATION('w', 1),
		FST::RELATION('x', 0), FST::RELATION('x', 1),
		FST::RELATION('y', 0), FST::RELATION('y', 1),
		FST::RELATION('z', 0), FST::RELATION('z', 1),
		FST::RELATION('A', 0), FST::RELATION('A', 1),
		FST::RELATION('B', 0), FST::RELATION('B', 1),
		FST::RELATION('C', 0), FST::RELATION('C', 1),
		FST::RELATION('D', 0), FST::RELATION('D', 1),
		FST::RELATION('E', 0), FST::RELATION('E', 1),
		FST::RELATION('F', 0), FST::RELATION('F', 1),
		FST::RELATION('G', 0), FST::RELATION('G', 1),
		FST::RELATION('H', 0), FST::RELATION('H', 1),
		FST::RELATION('I', 0), FST::RELATION('I', 1),
		FST::RELATION('J', 0), FST::RELATION('J', 1),
		FST::RELATION('K', 0), FST::RELATION('K', 1),
		FST::RELATION('L', 0), FST::RELATION('L', 1),
		FST::RELATION('M', 0), FST::RELATION('M', 1),
		FST::RELATION('N', 0), FST::RELATION('N', 1),
		FST::RELATION('O', 0), FST::RELATION('O', 1),
		FST::RELATION('P', 0), FST::RELATION('P', 1),
		FST::RELATION('Q', 0), FST::RELATION('Q', 1),
		FST::RELATION('R', 0), FST::RELATION('R', 1),
		FST::RELATION('S', 0), FST::RELATION('S', 1),
		FST::RELATION('T', 0), FST::RELATION('T', 1),
		FST::RELATION('U', 0), FST::RELATION('U', 1),
		FST::RELATION('V', 0), FST::RELATION('V', 1),
		FST::RELATION('W', 0), FST::RELATION('W', 1),
		FST::RELATION('X', 0), FST::RELATION('X', 1),
		FST::RELATION('Y', 0), FST::RELATION('Y', 1),
		FST::RELATION('Z', 0), FST::RELATION('Z', 1),
		FST::RELATION('0', 0), FST::RELATION('0', 1),
		FST::RELATION('1', 0), FST::RELATION('1', 1), 
		FST::RELATION('2', 0), FST::RELATION('2', 1), 
		FST::RELATION('3', 0), FST::RELATION('3', 1), 
		FST::RELATION('4', 0), FST::RELATION('4', 1), 
		FST::RELATION('5', 0), FST::RELATION('5', 1), 
		FST::RELATION('6', 0), FST::RELATION('6', 1), 
		FST::RELATION('7', 0), FST::RELATION('7', 1), 
		FST::RELATION('8', 0), FST::RELATION('8', 1), 
		FST::RELATION('9', 0), FST::RELATION('9', 1)),
	FST::NODE()
);


FST::FST fstIntegerLiteral("", 2,
	FST::NODE(21,
		FST::RELATION('0', 0), FST::RELATION('0', 1),
		FST::RELATION('1', 0), FST::RELATION('1', 1),
		FST::RELATION('2', 0), FST::RELATION('2', 1),
		FST::RELATION('3', 0), FST::RELATION('3', 1),
		FST::RELATION('4', 0), FST::RELATION('4', 1),
		FST::RELATION('5', 0), FST::RELATION('5', 1),
		FST::RELATION('6', 0), FST::RELATION('6', 1),
		FST::RELATION('7', 0), FST::RELATION('7', 1),
		FST::RELATION('8', 0), FST::RELATION('8', 1),
		FST::RELATION('9', 0), FST::RELATION('9', 1)),
	FST::NODE()
);

FST::FST fstLiteral("", 4,
	FST::NODE(1, FST::RELATION('\'', 1)),					
	FST::NODE(266,											
		FST::RELATION('1', 1), FST::RELATION('1', 2),
		FST::RELATION('1', 1), FST::RELATION('1', 2),
		FST::RELATION('2', 1), FST::RELATION('2', 2),
		FST::RELATION('3', 1), FST::RELATION('3', 2),
		FST::RELATION('4', 1), FST::RELATION('4', 2),
		FST::RELATION('5', 1), FST::RELATION('5', 2),
		FST::RELATION('6', 1), FST::RELATION('6', 2),
		FST::RELATION('7', 1), FST::RELATION('7', 2),
		FST::RELATION('8', 1), FST::RELATION('8', 2),
		FST::RELATION('9', 1), FST::RELATION('9', 2),
		FST::RELATION('a', 1), FST::RELATION('a', 2), FST::RELATION('A', 1), FST::RELATION('A', 2),
		FST::RELATION('b', 1), FST::RELATION('b', 2), FST::RELATION('B', 1), FST::RELATION('B', 2),
		FST::RELATION('c', 1), FST::RELATION('c', 2), FST::RELATION('C', 1), FST::RELATION('C', 2),
		FST::RELATION('d', 1), FST::RELATION('d', 2), FST::RELATION('D', 1), FST::RELATION('D', 2),
		FST::RELATION('e', 1), FST::RELATION('e', 2), FST::RELATION('E', 1), FST::RELATION('E', 2),
		FST::RELATION('f', 1), FST::RELATION('f', 2), FST::RELATION('F', 1), FST::RELATION('F', 2),
		FST::RELATION('g', 1), FST::RELATION('g', 2), FST::RELATION('G', 1), FST::RELATION('G', 2),
		FST::RELATION('h', 1), FST::RELATION('h', 2), FST::RELATION('H', 1), FST::RELATION('H', 2),
		FST::RELATION('i', 1), FST::RELATION('i', 2), FST::RELATION('I', 1), FST::RELATION('I', 2),
		FST::RELATION('j', 1), FST::RELATION('j', 2), FST::RELATION('J', 1), FST::RELATION('J', 2),
		FST::RELATION('k', 1), FST::RELATION('k', 2), FST::RELATION('K', 1), FST::RELATION('K', 2),
		FST::RELATION('l', 1), FST::RELATION('l', 2), FST::RELATION('L', 1), FST::RELATION('L', 2),
		FST::RELATION('m', 1), FST::RELATION('m', 2), FST::RELATION('M', 1), FST::RELATION('M', 2),
		FST::RELATION('n', 1), FST::RELATION('n', 2), FST::RELATION('N', 1), FST::RELATION('N', 2),
		FST::RELATION('o', 1), FST::RELATION('o', 2), FST::RELATION('O', 1), FST::RELATION('O', 2),
		FST::RELATION('p', 1), FST::RELATION('p', 2), FST::RELATION('P', 1), FST::RELATION('P', 2),
		FST::RELATION('q', 1), FST::RELATION('q', 2), FST::RELATION('Q', 1), FST::RELATION('Q', 2),
		FST::RELATION('r', 1), FST::RELATION('r', 2), FST::RELATION('R', 1), FST::RELATION('R', 2),
		FST::RELATION('s', 1), FST::RELATION('s', 2), FST::RELATION('S', 1), FST::RELATION('S', 2),
		FST::RELATION('t', 1), FST::RELATION('t', 2), FST::RELATION('T', 1), FST::RELATION('T', 2),
		FST::RELATION('u', 1), FST::RELATION('u', 2), FST::RELATION('U', 1), FST::RELATION('U', 2),
		FST::RELATION('v', 1), FST::RELATION('v', 2), FST::RELATION('V', 1), FST::RELATION('V', 2),
		FST::RELATION('w', 1), FST::RELATION('w', 2), FST::RELATION('W', 1), FST::RELATION('W', 2),
		FST::RELATION('x', 1), FST::RELATION('x', 2), FST::RELATION('X', 1), FST::RELATION('X', 2),
		FST::RELATION('y', 1), FST::RELATION('y', 2), FST::RELATION('Y', 1), FST::RELATION('Y', 2),
		FST::RELATION('z', 1), FST::RELATION('z', 2), FST::RELATION('Z', 1), FST::RELATION('Z', 2),
		FST::RELATION('а', 1), FST::RELATION('а', 2), FST::RELATION('А', 1), FST::RELATION('А', 2),
		FST::RELATION('б', 1), FST::RELATION('б', 2), FST::RELATION('Б', 1), FST::RELATION('Б', 2),
		FST::RELATION('в', 1), FST::RELATION('в', 2), FST::RELATION('В', 1), FST::RELATION('В', 2),
		FST::RELATION('г', 1), FST::RELATION('г', 2), FST::RELATION('Г', 1), FST::RELATION('Г', 2),
		FST::RELATION('д', 1), FST::RELATION('д', 2), FST::RELATION('Д', 1), FST::RELATION('Д', 2),
		FST::RELATION('е', 1), FST::RELATION('е', 2), FST::RELATION('Е', 1), FST::RELATION('Е', 2),
		FST::RELATION('ё', 1), FST::RELATION('ё', 2), FST::RELATION('Ё', 1), FST::RELATION('Ё', 2),
		FST::RELATION('ж', 1), FST::RELATION('ж', 2), FST::RELATION('Ж', 1), FST::RELATION('Ж', 2),
		FST::RELATION('з', 1), FST::RELATION('з', 2), FST::RELATION('З', 1), FST::RELATION('З', 2),
		FST::RELATION('и', 1), FST::RELATION('и', 2), FST::RELATION('И', 1), FST::RELATION('И', 2),
		FST::RELATION('й', 1), FST::RELATION('й', 2), FST::RELATION('Й', 1), FST::RELATION('Й', 2),
		FST::RELATION('к', 1), FST::RELATION('к', 2), FST::RELATION('К', 1), FST::RELATION('К', 2),
		FST::RELATION('л', 1), FST::RELATION('л', 2), FST::RELATION('Л', 1), FST::RELATION('Л', 2),
		FST::RELATION('м', 1), FST::RELATION('м', 2), FST::RELATION('М', 1), FST::RELATION('М', 2),
		FST::RELATION('н', 1), FST::RELATION('н', 2), FST::RELATION('Н', 1), FST::RELATION('Н', 2),
		FST::RELATION('о', 1), FST::RELATION('о', 2), FST::RELATION('О', 1), FST::RELATION('О', 2),
		FST::RELATION('п', 1), FST::RELATION('п', 2), FST::RELATION('П', 1), FST::RELATION('П', 2),
		FST::RELATION('р', 1), FST::RELATION('р', 2), FST::RELATION('Р', 1), FST::RELATION('Р', 2),
		FST::RELATION('с', 1), FST::RELATION('с', 2), FST::RELATION('С', 1), FST::RELATION('С', 2),
		FST::RELATION('т', 1), FST::RELATION('т', 2), FST::RELATION('Т', 1), FST::RELATION('Т', 2),
		FST::RELATION('у', 1), FST::RELATION('у', 2), FST::RELATION('У', 1), FST::RELATION('У', 2),
		FST::RELATION('ф', 1), FST::RELATION('ф', 2), FST::RELATION('Ф', 1), FST::RELATION('Ф', 2),
		FST::RELATION('х', 1), FST::RELATION('х', 2), FST::RELATION('Х', 1), FST::RELATION('Х', 2),
		FST::RELATION('ц', 1), FST::RELATION('ц', 2), FST::RELATION('Ц', 1), FST::RELATION('Ц', 2),
		FST::RELATION('ч', 1), FST::RELATION('ч', 2), FST::RELATION('Ч', 1), FST::RELATION('Ч', 2),
		FST::RELATION('ш', 1), FST::RELATION('ш', 2), FST::RELATION('Ш', 1), FST::RELATION('Ш', 2),
		FST::RELATION('щ', 1), FST::RELATION('щ', 2), FST::RELATION('Щ', 1), FST::RELATION('Щ', 2),
		FST::RELATION('ъ', 1), FST::RELATION('ъ', 2), FST::RELATION('Ъ', 1), FST::RELATION('Ъ', 2),
		FST::RELATION('ы', 1), FST::RELATION('ы', 2), FST::RELATION('Ы', 1), FST::RELATION('Ы', 2),
		FST::RELATION('ь', 1), FST::RELATION('ь', 2), FST::RELATION('Ь', 1), FST::RELATION('Ь', 2),
		FST::RELATION('э', 1), FST::RELATION('э', 2), FST::RELATION('Э', 1), FST::RELATION('Э', 2),
		FST::RELATION('ю', 1), FST::RELATION('ю', 2), FST::RELATION('Ю', 1), FST::RELATION('Ю', 2),
		FST::RELATION('я', 1), FST::RELATION('я', 2), FST::RELATION('Я', 1), FST::RELATION('Я', 2),
		FST::RELATION('!', 1), FST::RELATION('!', 2),
		FST::RELATION('?', 1), FST::RELATION('?', 2),
		FST::RELATION(',', 1), FST::RELATION(',', 2),
		FST::RELATION('.', 1), FST::RELATION('.', 2),
		FST::RELATION(' ', 1), FST::RELATION(' ', 2)),
	FST::NODE(1, FST::RELATION('\'', 3)),
	FST::NODE()												
);
FST::FST fstPlus("", 2,
	FST::NODE(1, FST::RELATION('+', 1)),
	FST::NODE()
);
FST::FST fstMinus("", 2,
	FST::NODE(1, FST::RELATION('-', 1)),
	FST::NODE()
);
FST::FST fstStar("", 2,
	FST::NODE(1, FST::RELATION('*', 1)),
	FST::NODE()
);

FST::FST fstDirslash("", 2,
	FST::NODE(1, FST::RELATION('/', 1)),
	FST::NODE()
);

FST::Automatic FST_ARRAY[] = {
	{ fstTypeInteger,  LEX_INTEGER, FN::INT, LT::PN_DEF },
	{ fstTypeString , LEX_STRING, FN::STR, LT::PN_DEF },
	{ fstTypeBool, LEX_BOOL, FN::BOOL, LT::PN_DEF },
	{ fstInclude , LEX_INCLUDE, FN::INCLUDE, LT::PN_DEF },
	{ fstKPI , LEX_KPI_LIB, FN::KPILIB, LT::PN_DEF },
	{ fstKeyFunction , LEX_FUNCTION, FN::FUNCTION, LT::PN_DEF },
	{ fstKeyDeclare, LEX_DECLARE,FN::DECLARE, LT::PN_DEF },
	{ fstEndl, LEX_ENDL, FN::ENDL, LT::PN_DEF },
	{ fstKeyBegin , LEX_BEGIN_FUNCTION, FN::BEGIN, LT::PN_DEF },
	{ fstCircleWhile , LEX_CIRCLE, FN::WCIRCLE, LT::PN_DEF },
	{ fstProvisionIf, LEX_CONDITION, FN::CONDITIONIF, LT::PN_DEF },
	{ fstProvisionElse, LEX_ELSE, FN::CONDITIONELSE, LT::PN_DEF },
	{ fstKeySout , LEX_SOUT, FN::SOUT, LT::PN_DEF },
	{ fstKeySin, LEX_SIN, FN::SIN, LT::PN_DEF },
	{ fstKeyReturn, LEX_RETURN, FN::RETURN, LT::PN_DEF },
	{ fstPlus, LEX_ACTION, FN::PLUS, LT::PN_PLUS},
	{ fstMinus, LEX_ACTION, FN::MINUS, LT::PN_MINUS },
	{ fstStar, LEX_ACTION, FN::STAR, LT::PN_STAR },
	{ fstDirslash, LEX_ACTION, FN::DIRSLASH, LT::PN_DIRSLASH },
	{ fstMore, LEX_MORE , FN::MORE, LT::PN_DEF },
	{ fstLess, LEX_MORE , FN::LESS, LT::PN_DEF },
	{ fstV, LEX_ACTION , FN::ACTION, LT::PN_DEF },
	{ fstEqually, LEX_EQUALLU, FN::EQUALLU, LT::PN_DEF },
	{ fstLeftThesis, LEX_LEFTTHESIS, FN::LTHESIS , LT::PN_LEFTTHESIS },
	{ fstRightThesis, LEX_RIGHTTHESIS,FN::RTHESIS , LT::PN_LEFTTHESIS },
	{ fstSemiColon, LEX_SEMICOLON,FN::SEMILICON, LT::PN_DEF },
	{ fstComma, LEX_COMMA,FN::COMMA, LT::PN_DEF },
	{ fstLeftBrace, LEX_LEFTBRACE,FN::LBRACE, LT::PN_DEF },
	{ fstRightBrace , LEX_RIGHTBRACE,FN::RBRACE, LT::PN_DEF },
	{ fstFalseLiteral, LEX_BOOL_LITERAL, FN::FALSELITERAL, LT::PN_DEF },
	{ fstTrueLiteral, LEX_BOOL_LITERAL, FN::TRUELITERAL, LT::PN_DEF },
	{ fstLiteral, LEX_LITERAL,FN::LITERAL, LT::PN_DEF },
	{ fstIntegerLiteral, LEX_LITERAL,FN::INTLITERAL, LT::PN_DEF },
	{ fstIdentif, LEX_VARIABLE,FN::IDENTETIF, LT::PN_DEF },
	{ fstFalseIdentif, LEX_VARIABLE,FN::FIDENTETIF, LT::PN_DEF },
	{ fstFalseNumIdentif, LEX_VARIABLE, FN::FALSENUMIDENTETIF, LT::PN_DEF }
};