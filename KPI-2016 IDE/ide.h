#ifndef IDE_H
#define IDE_H
#include "stdafx.h"

class Syntax;
class Setting;

class IDE :public QWidget
{
	Q_OBJECT
public:
	IDE(QWidget *parent = 0);
	private slots:
	void open();
	void save();
	void compil();
	void searchBar();
	void replaceBar();
	void findButton();
	void replaceButton();
private:
	CodeEditor *_textEdit;
	QPushButton *_close;
	QPushButton *_open;
	QPushButton *_save;
	QPushButton *_undo;
	QPushButton *_redo;
	QPushButton *_searchShow;
	QPushButton *_replaceShow;
	QPushButton *_settingShow;
	QLineEdit *_searchInput;
	QPushButton *_searchButton;
	QLineEdit *_replaceWord;
	QLineEdit *_replacingWord;
	QPushButton *_replaceButton;
	QPushButton *_compil;
	QWidget *_searchBar;
	QWidget *_replaceBar;
	bool _isFirstTime;

	Syntax *syntax;
	Setting *setting;
protected:
	virtual void keyPressEvent(QKeyEvent *event);
};

#endif // IDE_H
