#include "stdafx.h"

Setting::Setting(QWidget * parent) : QWidget(parent) {
	
	resize(400, 300);
	setWindowTitle("Settings");
	this->_settings = new QSettings("TALLER", "KPI-2016", this);
	loadSettings();
	this->_kpiPatchLabel = new QLabel("Patch to KPI");
	this->_kpiPatchButton = new QPushButton("Change");
	this->_kpiPathLine = new QLineEdit(this->_kpiPatch);

	this->_exePatchLabel = new QLabel("exe name");
	this->_exePathLine = new QLineEdit(this->_exePatch);

	this->_checkLT = new QCheckBox("Show LT", this); this->_checkLT->setChecked(this->isLT);
	this->_checkIT = new QCheckBox("Show IT", this); this->_checkIT->setChecked(this->isIT);
	this->_checkSA = new QCheckBox("Show SA", this); this->_checkSA->setChecked(this->isSA);
	this->_checkR = new QCheckBox("Show R", this); this->_checkR->setChecked(this->isR);
	this->_checkNT = new QCheckBox("Show NT", this); this->_checkNT->setChecked(this->isNT);

	this->_save = new QPushButton("Save");

	QVBoxLayout *mainLayout = new QVBoxLayout;

	QHBoxLayout *kpiPatchLayout = new QHBoxLayout;
	kpiPatchLayout->addWidget(this->_kpiPatchLabel); 
	kpiPatchLayout->addWidget(this->_kpiPathLine);
	kpiPatchLayout->addWidget(this->_kpiPatchButton);

	QHBoxLayout *exeNameLayout = new QHBoxLayout;
	exeNameLayout->addWidget(this->_exePatchLabel);
	exeNameLayout->addWidget(this->_exePathLine);

	QVBoxLayout *ltLayout = new QVBoxLayout;
	ltLayout->addWidget(this->_checkLT);
	ltLayout->addWidget(this->_checkIT);
	ltLayout->addWidget(this->_checkSA);
	ltLayout->addWidget(this->_checkR);
	ltLayout->addWidget(this->_checkNT);



	mainLayout->addLayout(kpiPatchLayout);
	mainLayout->addLayout(exeNameLayout);
	mainLayout->addLayout(ltLayout);
	mainLayout->addWidget(_save);
	setLayout(mainLayout);
	connect(this->_kpiPatchButton, SIGNAL(clicked()), this, SLOT(setKpiPatch()));
	connect(this->_save, SIGNAL(clicked()), this, SLOT(saveSettings(), close()));
}

Setting::~Setting() {
	saveSettings();
}

void Setting::saveSettings()
{
	this->_settings->setValue("kpiPatch",_kpiPatch);
	this->_settings->setValue("exeName", this->_exePathLine->text());
	this->_settings->setValue("rShow", this->_checkR->isChecked());
	this->_settings->setValue("ntShow", this->_checkNT->isChecked());
	this->_settings->setValue("ltShow", this->_checkLT->isChecked());
	this->_settings->setValue("itShow", this->_checkIT->isChecked());
	this->_settings->setValue("saShow", this->_checkSA->isChecked());
	close();
}

void Setting::loadSettings()
{
	this->_kpiPatch = _settings->value("kpiPatch", "bla").toString();
	this->_exePatch = _settings->value("exeName", "bla").toString();
	this->isLT = _settings->value("ltShow", 0).toBool();
	this->isIT = _settings->value("itShow", 0).toBool();
	this->isSA = _settings->value("saShow", 0).toBool();
	this->isR = _settings->value("rShow", 0).toBool();
	this->isNT = _settings->value("ntShow", 0).toBool();
}

void Setting::setKpiPatch()
{
	_kpiPatch = QFileDialog::getOpenFileName(this, tr("Open KPI compil"), "",
		tr("KPI compil (*.exe)"));
	this->_kpiPathLine->setText(this->_kpiPatch);
	this->_settings->setValue("kpiPatch", _kpiPatch);

}