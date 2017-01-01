#include "stdafx.h"

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
	lineNumberArea = new LineNumberArea(this);
	Setting settings = new Setting;
	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(updateLineNumberArea(QRect, int)));
	updateLineNumberAreaWidth(0);
	highlightCurrentLine();
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));		
}



int CodeEditor::lineNumberAreaWidth()
{
	int digits = 1;
	int max = qMax(1, blockCount());
	while (max >= 10) {
		max /= 10;
		++digits;
	}

	int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;
	return 15;
}



void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}



void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
	if (dy)		lineNumberArea->scroll(0, dy);
	else		lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
	if (rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth(0);
}



void CodeEditor::resizeEvent(QResizeEvent *e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();
	lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

QString CodeEditor::setIndent(int size)
{
	QString buf("");
	int count = size / 4;
	for (int i = 0; i < count; i++)		buf.push_back("    ");
	return buf;
}

int CodeEditor::getIndent(int line)
{
	if (line == 0)	return 0;
	for (int i = 1; i < this->lineNumberIndent.size() + 1; i++)
	{
		if (i == line)	return this->lineNumberIndent[i - 1];
	}
	return 0;
}

void CodeEditor::keyPressEvent(QKeyEvent *event)
{
	int ident;
	switch (event->key())
	{
	case Qt::Key_BracketRight:
	{
		if (this->prevKey == Qt::Key_Enter || this->prevKey == Qt::Key_Return)
		{
			for (int i = 0; i < 4; i++)	QPlainTextEdit::textCursor().deletePreviousChar();
			this->insertPlainText("]");
		}
		else this->insertPlainText("]"); break;
	}
	case Qt::Key_Enter: case Qt::Key_Return:
	{
		this->insertPlainText("\n");
		auto it = this->lineNumberIndent.begin() + (this->currentPosssition);
		if (this->prevKey == Qt::Key_BracketLeft)	ident = getIndent(this->currentPosssition) + 4;
		else if (this->prevKey == Qt::Key_BracketRight && this->currentPosssition - 1 == this->lastPossition)
			ident = getIndent(this->currentPosssition) - 4;
		else	ident = getIndent(this->currentPosssition);
		this->lineNumberIndent.insert(it, ident);
		this->insertPlainText(setIndent(ident));
		break;
	}
	default:QPlainTextEdit::keyPressEvent(event);
	}
	this->prevKey = event->key();
	this->lastPossition = this->currentPosssition;
}

void CodeEditor::highlightCurrentLine()
{
	QList<QTextEdit::ExtraSelection> extraSelections;

	if (!isReadOnly()) {
		QTextEdit::ExtraSelection selection;

		QColor lineColor = QColor(Qt::yellow).lighter(160);

		selection.format.setBackground(lineColor);
		selection.format.setProperty(QTextFormat::FullWidthSelection, true);
		selection.cursor = textCursor();
		selection.cursor.clearSelection();
		this->currentPosssition = textCursor().block().blockNumber() - 1;
		extraSelections.append(selection);
	}

	setExtraSelections(extraSelections);
}



void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
	QPainter painter(lineNumberArea);
	Setting settings = new Setting;
	//painter.fillRect(event->rect(), Qt::gray);

		QTextBlock block = firstVisibleBlock();
		int blockNumber = block.blockNumber();
		int top = (int)blockBoundingGeometry(block).translated(contentOffset()).top();
		int bottom = top + (int)blockBoundingRect(block).height();
		if (settings.isLineNumber == true)
		{
		while (block.isValid() && top <= event->rect().bottom()) {
			if (block.isVisible() && bottom >= event->rect().top()) {
				QString number = QString::number(blockNumber + 1).rightJustified(2, '0');;
				painter.setPen(Qt::darkBlue);
				painter.drawText(0, top, lineNumberArea->width() - 2, fontMetrics().height(),
					Qt::AlignRight, number);
			}

			block = block.next();
			top = bottom;
			bottom = top + (int)blockBoundingRect(block).height();
			++blockNumber;
	}
	}	
}