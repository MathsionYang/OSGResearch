/********************************************************************************
** Form generated from reading UI file 'OSGResearch_VS.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OSGRESEARCH_VS_H
#define UI_OSGRESEARCH_VS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OSGResearch_VSClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OSGResearch_VSClass)
    {
        if (OSGResearch_VSClass->objectName().isEmpty())
            OSGResearch_VSClass->setObjectName(QString::fromUtf8("OSGResearch_VSClass"));
        OSGResearch_VSClass->resize(600, 400);
        menuBar = new QMenuBar(OSGResearch_VSClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        OSGResearch_VSClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OSGResearch_VSClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        OSGResearch_VSClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(OSGResearch_VSClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        OSGResearch_VSClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(OSGResearch_VSClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        OSGResearch_VSClass->setStatusBar(statusBar);

        retranslateUi(OSGResearch_VSClass);

        QMetaObject::connectSlotsByName(OSGResearch_VSClass);
    } // setupUi

    void retranslateUi(QMainWindow *OSGResearch_VSClass)
    {
        OSGResearch_VSClass->setWindowTitle(QCoreApplication::translate("OSGResearch_VSClass", "OSGResearch_VS", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OSGResearch_VSClass: public Ui_OSGResearch_VSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSGRESEARCH_VS_H
