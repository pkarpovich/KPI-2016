#include "ide.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TextEdit textEdit;
	textEdit.show();
	return a.exec();
}
