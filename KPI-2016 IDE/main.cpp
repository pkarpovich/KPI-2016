#include "stdafx.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setApplicationName("KPI-2016");
	a.setOrganizationName("TALLER");
	IDE ide;
	ide.show();
	return a.exec();
}
