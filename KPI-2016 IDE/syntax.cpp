#include "stdafx.h"

Syntax::Syntax(QTextDocument *parent)
	:QSyntaxHighlighter(parent)
{
	highlightRule rulee;


	// ключевые слова
	keywordFormat.setForeground(Qt::darkBlue);
	keywordFormat.setFontWeight(QFont::Bold);
	QStringList keywordPatterns;
	keywordPatterns << "\\bint\\b" << "\\bstr\\b" << "\\bfunc\\b"
		<< "\\bif\\b" << "\\bwhile\\b" << "\\bbegin\\b"
		<< "\\breturn\\b" << "\\binclude\\b";
	foreach(const QString &pattern, keywordPatterns) {
		rulee.pattern = QRegExp(pattern);
		rulee.format = keywordFormat;
		rule.append(rulee);
	}

	// строчные литералы
	classFormat.setForeground(Qt::darkCyan);
	classFormat.setFontWeight(QFont::ExtraLight);
	rulee.pattern = QRegExp("\".*\"");
	rulee.format = classFormat;
	rule.append(rulee);

	classFormat.setForeground(Qt::darkCyan);
	classFormat.setFontWeight(QFont::ExtraLight);
	rulee.pattern = QRegExp("`.*`");
	rulee.format = classFormat;
	rule.append(rulee);

	classFormat.setForeground(Qt::darkCyan);
	classFormat.setFontWeight(QFont::ExtraLight);
	rulee.pattern = QRegExp("'.*'");
	rulee.format = classFormat;
	rule.append(rulee);

	// однострочный комментарий
	singleLineCommentFormat.setForeground(Qt::darkGreen);
	rulee.pattern = QRegExp("\\\\\\\\[^\n]*");
	rulee.format = singleLineCommentFormat;
	rule.append(rulee);
}

void Syntax::highlightBlock(const QString &text)
{
	foreach(const highlightRule &rulee, rule)
	{
		QRegExp expression(rulee.pattern);
		int index = expression.indexIn(text);
		while (index >= 0)
		{
			int lenght = expression.matchedLength();
			setFormat(index, lenght, rulee.format);
			index = expression.indexIn(text, index + lenght);
		}
	}

	QTextCharFormat multiLineCommentFormat;
	multiLineCommentFormat.setForeground(Qt::darkGreen);
	// Многостроынй комментарий
	QRegExp startExpression("\\\\\\*");
	QRegExp endExpression("\\*\\\\");

	setCurrentBlockState(0);

	int startIndex = 0;
	if (previousBlockState() != 1)
		startIndex = text.indexOf(startExpression);

	while (startIndex >= 0) {
		int endIndex = text.indexOf(endExpression, startIndex);
		int commentLength;
		if (endIndex == -1) {
			setCurrentBlockState(1);
			commentLength = text.length() - startIndex;
		}
		else {
			commentLength = endIndex - startIndex
				+ endExpression.matchedLength();
		}
		setFormat(startIndex, commentLength, multiLineCommentFormat);
		startIndex = text.indexOf(startExpression,
			startIndex + commentLength);
	}
}
