#include "stdafx.h"


LineNumberArea::LineNumberArea(CodeEditor *editor) : QWidget(editor) {
	this->_codeEditor = editor;
}

QSize LineNumberArea::sizeHint() const
{
	return QSize(this->_codeEditor->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event) {
	this->_codeEditor->lineNumberAreaPaintEvent(event);
}