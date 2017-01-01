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
	int getIndent(int);
	QString setIndent(int);
protected:
	void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
	//void keyReleaseEvent(QKeyEvent* e);
	void keyPressEvent(QKeyEvent *event);
	private slots:
	void updateLineNumberAreaWidth(int newBlockCount);
	void highlightCurrentLine();
	void updateLineNumberArea(const QRect &, int);
private:
	std::vector<int> lineNumberIndent/* = new std::vector<int>*/;
	int currentPosssition;
	int lastPossition;
	QWidget *lineNumberArea;
	int prevKey;
};
