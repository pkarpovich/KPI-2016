#ifndef IDE_H
#define IDE_H

#include <QtWidgets/QMainWindow>
#include "ui_ide.h"
#include <qdialog.h>
#include <qpushbutton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qtextedit.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qtextstream.h>
#include <qsyntaxhighlighter.h>
#include <qregexp.h>
#include <qprocess.h>
#include <qtextcodec.h>
#include <QKeyEvent>

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

class TextEdit :public QWidget
{
	Q_OBJECT
public:
	TextEdit(QWidget *parent = 0);
	private slots:
	void open();
	void save();
	void compil();
private:
	QTextEdit *_textEdit;
	QPushButton *_close;
	QPushButton *_open;
	QPushButton *_save;
	QPushButton *_undo;
	QPushButton *_redo;
	QPushButton *_compil;

	Syntax *syntax;
protected:
	virtual void keyPressEvent(QKeyEvent *event);
};

#endif // IDE_H
