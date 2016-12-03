/********************************************************************************
** Form generated from reading UI file 'ide.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IDE_H
#define UI_IDE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ideClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ideClass)
    {
        if (ideClass->objectName().isEmpty())
            ideClass->setObjectName(QStringLiteral("ideClass"));
        ideClass->resize(600, 400);
        menuBar = new QMenuBar(ideClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ideClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ideClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ideClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ideClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ideClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ideClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ideClass->setStatusBar(statusBar);

        retranslateUi(ideClass);

        QMetaObject::connectSlotsByName(ideClass);
    } // setupUi

    void retranslateUi(QMainWindow *ideClass)
    {
        ideClass->setWindowTitle(QApplication::translate("ideClass", "ide", 0));
    } // retranslateUi

};

namespace Ui {
    class ideClass: public Ui_ideClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IDE_H
