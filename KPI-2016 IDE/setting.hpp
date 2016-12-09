﻿#pragma once
#include "stdafx.h"

class Setting : public QWidget {
	Q_OBJECT

public:
	Setting(QWidget * parent = Q_NULLPTR);
	~Setting();
	QString _kpiPatch;
	QString _exePatch;
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

	QLabel *_exePatchLabel;
	QLineEdit *_exePathLine;

	QCheckBox *_checkLT;
	QCheckBox *_checkIT;
	QCheckBox *_checkSA;

	QCheckBox *_checkLine;
	QCheckBox *_checkHighLine;

	QSettings *_settings;
	QPushButton *_save;
};
