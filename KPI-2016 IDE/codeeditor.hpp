#pragma once
#include "stdafx.h"

class CodeEditor : public QPlainTextEdit
{
	Q_OBJECT

public:
	CodeEditor(QWidget *parent = 0);
	QString tab = "";
	void lineNumberAreaPaintEvent(QPaintEvent *event);
	int lineNumberAreaWidth();

protected:
	void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
protected:
	void keyReleaseEvent(QKeyEvent* e);
	private slots:
	void updateLineNumberAreaWidth(int newBlockCount);
	void highlightCurrentLine();
	void updateLineNumberArea(const QRect &, int);
private:
	QWidget *lineNumberArea;
};
