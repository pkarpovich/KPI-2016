#include "ide.h"

TextEdit::TextEdit(QWidget *parent)
	:QWidget(parent)
{
	resize(800, 500);
	setWindowTitle("KPI-2016");

	this->_textEdit = new QTextEdit;
	this->_close = new QPushButton("Close");
	this->_save = new QPushButton("Save");
	this->_open = new QPushButton("Open");
	this->_undo = new QPushButton("Undo");
	this->_redo = new QPushButton("Redo");
	this->_compil = new QPushButton("Compil");
	syntax = new Syntax(this->_textEdit->document());

	QHBoxLayout *menu = new QHBoxLayout;
	menu->addWidget(this->_open);	menu->addWidget(this->_save);
	menu->addWidget(this->_undo);	menu->addWidget(this->_redo);
	menu->addWidget(this->_compil);
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addLayout(menu);
	layout->addWidget(this->_textEdit);
	layout->addWidget(this->_close);
	setLayout(layout);

	connect(this->_close, SIGNAL(clicked()), qApp, SLOT(quit()));
	connect(this->_save, SIGNAL(clicked()), this, SLOT(save()));
	connect(this->_open, SIGNAL(clicked()), this, SLOT(open()));
	connect(this->_undo, SIGNAL(clicked()), this->_textEdit, SLOT(undo()));
	connect(this->_redo, SIGNAL(clicked()), this->_textEdit, SLOT(redo()));
	connect(this->_compil, SIGNAL(clicked()), this, SLOT(compil()));
};

void TextEdit::keyPressEvent(QKeyEvent * event)
{
	switch (event->key())
	{
	case Qt::Key_F5:
		if (event->modifiers() & Qt::CTRL)	compil();
		break;
	case Qt::Key_Q:
		if (event->modifiers() & Qt::CTRL) close();
	}
}

void TextEdit::compil()
{
	QString inPath = QTextCodec::codecForLocale()->toUnicode(
		"C:\\Users\\taller\\OneDrive\\Документы\\Visual Studio 2015\\Projects\\KPI-2016\\KPI-2016\\in.txt");
	QFile inFile(inPath);
	if (!inFile.open(QIODevice::WriteOnly))
	{
		QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
		return;
	}
	QTextStream stream(&inFile);
	stream << this->_textEdit->toPlainText();
	stream.flush(); inFile.close();
	QProcess *process = new QProcess(this);
	QString path = QTextCodec::codecForLocale()->toUnicode(
		"C:\\Users\\taller\\OneDrive\\Документы\\Visual Studio 2015\\Projects\\KPI-2016\\Debug\\KPI-2016.exe");
	process->startDetached(path,QStringList() << "-in:../KPI-2016/in.txt" << "-out:code.asm");
}

void TextEdit::open()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "",
		tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

	if (fileName != "")
	{
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly))
		{
			QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
			return;
		}
		QTextStream in(&file);
		this->_textEdit->setText(in.readAll());
		file.close();
	}
}

void TextEdit::save()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "",
		tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

	if (fileName != "")
	{
		QFile file(fileName);
		if (!file.open(QIODevice::WriteOnly))
		{
			QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
			return;
		}
		else
		{
			QTextStream stream(&file);
			stream << this->_textEdit->toPlainText();
			stream.flush();
			file.close();
		}
	}
}

Syntax::Syntax(QTextDocument *parent)
	:QSyntaxHighlighter(parent)
{
	highlightRule rulee;

	keywordFormat.setForeground(Qt::darkBlue);
	keywordFormat.setFontWeight(QFont::Bold);
	QStringList keywordPatterns;
	keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
		<< "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
		<< "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
		<< "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
		<< "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
		<< "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
		<< "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
		<< "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
		<< "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
		<< "\\bvoid\\b" << "\\bvolatile\\b";
	foreach(const QString &pattern, keywordPatterns) {
		rulee.pattern = QRegExp(pattern);
		rulee.format = keywordFormat;
		rule.append(rulee);
	}

	classFormat.setFontWeight(QFont::Bold);
	classFormat.setBackground(Qt::darkMagenta);
	rulee.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
	rulee.format = classFormat;
	rule.append(rulee);

	singleLineCommentFormat.setForeground(Qt::darkGreen);
	rulee.pattern = QRegExp("//[^\n]*");
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
