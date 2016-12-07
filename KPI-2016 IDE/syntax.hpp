#pragma once
#include "stdafx.h"

class Syntax :public QSyntaxHighlighter
{
	Q_OBJECT
public:
	Syntax(QTextDocument *parent = 0);
protected:
	void highlightBlock(const QString &text);
private:
	struct highlightRule
	{
		QRegExp pattern;
		QTextCharFormat format;
	};
	QVector<highlightRule> rule;

	QRegExp commentStartExpression;
	QRegExp commentEndExpression;

	QTextCharFormat keywordFormat;
	QTextCharFormat classFormat;
	QTextCharFormat singleLineCommentFormat;
	QTextCharFormat multiLineCommentFormat;
	QTextCharFormat quotationFormat;
	QTextCharFormat functionFormat;
};