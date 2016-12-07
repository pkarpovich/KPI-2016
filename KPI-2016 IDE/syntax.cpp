#include "stdafx.h"

Syntax::Syntax(QTextDocument *parent)
	:QSyntaxHighlighter(parent)
{
	highlightRule rulee;

	keywordFormat.setForeground(Qt::darkBlue);
	keywordFormat.setFontWeight(QFont::Bold);
	QStringList keywordPatterns;
	keywordPatterns << "\\bif\\b" << "\\belse\\b" << "\\bwhile\\b"
		<< "\\bbegin\\b" << "\\breturn\\b";
	foreach(const QString &pattern, keywordPatterns) {
		rulee.pattern = QRegExp(pattern);
		rulee.format = keywordFormat;
		rule.append(rulee);
	}

	classFormat.setFontWeight(QFont::Bold);
	classFormat.setForeground(Qt::darkMagenta);
	rulee.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
	rulee.format = classFormat;
	rule.append(rule);

	classFormat.setForeground(Qt::darkYellow);
	rulee.pattern = QRegExp("([^\"] + )\"/gi");
	rulee.format = classFormat;
	rule.append(rule);

	singleLineCommentFormat.setForeground(Qt::red);
	rulee.pattern = QRegExp("//[^\n]*");
	rulee.format = singleLineCommentFormat;
	rule.append(rule);

	multiLineCommentFormat.setForeground(Qt::red);

	functionFormat.setFontItalic(true);
	functionFormat.setForeground(Qt::blue);
	rulee.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
	rulee.format = functionFormat;
	rule.append(rule);
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

	QRegExp startExpression("/\\*");
	QRegExp endExpression("\\*/");

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
