#pragma once
#include "stdafx.h"

class Setting : public QWidget {
	Q_OBJECT

public:
	Setting(QWidget * parent = Q_NULLPTR);
	~Setting();
	QString _kpiPatch;
	bool isLT; bool isIT; bool isSA;
	bool isLineNumber; bool isHighlightLine;
private slots:
	void setKpiPatch();
	void saveSettings();
	void loadSettings();
private:
	
	
	QLabel *_kpiPatchLabel;
	QPushButton *_kpiPatchButton;
	QLineEdit *_kpiPathLine;
	QSettings *_settings;
	QPushButton *_save;

	QCheckBox *_checkLT;
	QCheckBox *_checkIT;
	QCheckBox *_checkSA;

	QCheckBox *_checkLine;
	QCheckBox *_checkHighLine;
};
