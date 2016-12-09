#include "stdafx.h"

IDE::IDE(QWidget *parent)
	:QWidget(parent)
{
	resize(800, 500);
	setWindowTitle("KPI-2016 IDE");

	this->_close = new QPushButton("Close");
	this->_save = new QPushButton("Save");
	this->_open = new QPushButton("Open");
	this->_undo = new QPushButton("Undo");
	this->_redo = new QPushButton("Redo");
	this->_compil = new QPushButton("Compil");
	this->_searchShow = new QPushButton("Search");
	this->_replaceShow = new QPushButton("Replace");
	this->_settingShow = new QPushButton("Setting");
	this->_textEdit = new CodeEditor;
	syntax = new Syntax(this->_textEdit->document());
	setting = new Setting;

	QHBoxLayout *menu = new QHBoxLayout;
	menu->addWidget(this->_open);	menu->addWidget(this->_save);
	menu->addWidget(this->_undo);	menu->addWidget(this->_redo);
	menu->addWidget(this->_compil); menu->addWidget(this->_searchShow);
	menu->addWidget(this->_replaceShow);
	menu->addWidget(this->_settingShow);
	menu->addWidget(this->_close); 
	QVBoxLayout *layout = new QVBoxLayout;
	// панель поиска
	this->_searchInput = new QLineEdit;
	this->_searchButton = new QPushButton("Search");
	this->_searchBar = new QWidget;
	QHBoxLayout *searchLayout = new QHBoxLayout(this->_searchBar);
	searchLayout->addWidget(this->_searchInput); searchLayout->addWidget(this->_searchButton);
	this->_searchBar->hide();
	/////////////////////////////////////////////////////////////////////////////////////////
	// панель замены
	this->_replaceWord = new QLineEdit;
	this->_replacingWord = new QLineEdit;
	this->_replaceButton = new QPushButton("Replace");
	this->_replaceBar = new QWidget;
	QHBoxLayout *replaceLayout = new QHBoxLayout(this->_replaceBar);
	replaceLayout->addWidget(this->_replaceWord); replaceLayout->addWidget(this->_replacingWord);
	replaceLayout->addWidget(this->_replaceButton);
	this->_replaceBar->hide();
	/////////////////////////////////////////////////////////////////////////////////////////


	layout->addLayout(menu);
	layout->addWidget(this->_textEdit);
	layout->addWidget(_searchBar);
	layout->addWidget(_replaceBar);
	//layout->addWidget(this->_close);
	setLayout(layout);
	

	connect(this->_searchShow, SIGNAL(clicked()), this, SLOT(searchBar()));
	connect(this->_replaceShow, SIGNAL(clicked()), this, SLOT(replaceBar()));
	connect(this->_close, SIGNAL(clicked()), qApp, SLOT(quit()));
	connect(this->_save, SIGNAL(clicked()), this, SLOT(save()));
	connect(this->_open, SIGNAL(clicked()), this, SLOT(open()));
	connect(this->_undo, SIGNAL(clicked()), this->_textEdit, SLOT(undo()));
	connect(this->_redo, SIGNAL(clicked()), this->_textEdit, SLOT(redo()));
	connect(this->_compil, SIGNAL(clicked()), this, SLOT(compil()));
	connect(this->_searchButton, SIGNAL(clicked()), this, SLOT(findButton()));
	connect(this->_replaceButton, SIGNAL(clicked()), this, SLOT(replaceButton()));
	connect(this->_settingShow, SIGNAL(clicked()), this->setting, SLOT(show()));
};

void IDE::keyPressEvent(QKeyEvent * event)
{
	//CodeEditor::keyReleaseEvent(event);
	//QPlainTextEdit::keyReleaseEvent(event);	//QTextEdit::keyReleaseEvent(event);
	switch (event->key())
	{
	case Qt::Key_F5:
		if (event->modifiers() & Qt::CTRL)	compil();
		break;
	case Qt::Key_Q:
		if (event->modifiers() & Qt::CTRL) close();
		break;
	case Qt::Key_F:
		if (event->modifiers() & Qt::CTRL) searchBar();
		break;
	case Qt::Key_H:
		if (event->modifiers() & Qt::CTRL) replaceBar();
		break;
	case Qt::Key_W:
		if (event->modifiers() & Qt::CTRL)
			this->_textEdit->insertPlainText("    ");
		break;
	}
}

void IDE::compil()
{
	Setting setting = new Setting;
	QString inPath = QTextCodec::codecForLocale()->toUnicode(
		"C:\\Users\\taller\\OneDrive\\ƒокументы\\Visual Studio 2015\\Projects\\KPI-2016\\KPI-2016\\in.txt");
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
	QString path = setting._kpiPatch;
	QStringList *param = new QStringList;
	*param << "-in:../KPI-2016/in.txt" << "-out:"+setting._exePatch;
	if (setting.isLT) *param << "-LT";
	if (setting.isIT) *param << "-IT";
	if (setting.isSA) *param << "-SA";
	process->startDetached(path,*param);
}

void IDE::open()
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
		//this->_textEdit->setText(in.readAll());
		file.close();
	}
}

void IDE::save()
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

void IDE::searchBar()
{
	if (!_replaceBar->isHidden()) _replaceBar->hide();
	if (_searchBar->isHidden())	_searchBar->show();
	else _searchBar->hide();
}

void IDE::replaceBar()
{
	if (!_searchBar->isHidden()) _searchBar->hide();
	if (_replaceBar->isHidden())	_replaceBar->show();
	else _replaceBar->hide();
}

void IDE::findButton()
{
	QString searchString = this->_searchInput->text();
	QTextDocument *document = this->_textEdit->document();

	bool found = false;

	if (this->_isFirstTime == false)
		document->undo();

	if (searchString.isEmpty()) {
		QMessageBox::information(this, tr("Empty Search Field"),
			"The search field is empty. Please enter a word and click Find.");
	}
	else {

		QTextCursor highlightCursor(document);
		QTextCursor cursor(document);

		cursor.beginEditBlock();

		QTextCharFormat plainFormat(highlightCursor.charFormat());
		QTextCharFormat colorFormat = plainFormat;
		colorFormat.setForeground(Qt::red);

		while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
			highlightCursor = document->find(searchString, highlightCursor, QTextDocument::FindWholeWords);

			if (!highlightCursor.isNull()) {
				found = true;
				highlightCursor.movePosition(QTextCursor::WordRight,
					QTextCursor::KeepAnchor);
				highlightCursor.mergeCharFormat(colorFormat);
			}
		}

		cursor.endEditBlock();
		this->_isFirstTime = false;

		if (found == false) {
			QMessageBox::information(this, tr("Word Not Found"),
				"Sorry, the word cannot be found.");
		}
	}
}

void IDE::replaceButton()
{
	QString document = this->_textEdit->toPlainText();
	QString replaceWord = this->_replaceWord->text();
	QString replacingWord = this->_replacingWord->text();
	document.replace("\\bchar\\b", replacingWord);
}