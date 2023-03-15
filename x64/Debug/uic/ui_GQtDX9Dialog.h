/********************************************************************************
** Form generated from reading UI file 'GQtDX9Dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GQTDX9DIALOG_H
#define UI_GQTDX9DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GQtDX9Dialog
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GQtDX9Dialog)
    {
        if (GQtDX9Dialog->objectName().isEmpty())
            GQtDX9Dialog->setObjectName(QString::fromUtf8("GQtDX9Dialog"));
        GQtDX9Dialog->resize(400, 300);
        menuBar = new QMenuBar(GQtDX9Dialog);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        GQtDX9Dialog->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GQtDX9Dialog);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GQtDX9Dialog->addToolBar(mainToolBar);
        centralWidget = new QWidget(GQtDX9Dialog);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        GQtDX9Dialog->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GQtDX9Dialog);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GQtDX9Dialog->setStatusBar(statusBar);

        retranslateUi(GQtDX9Dialog);

        QMetaObject::connectSlotsByName(GQtDX9Dialog);
    } // setupUi

    void retranslateUi(QMainWindow *GQtDX9Dialog)
    {
        GQtDX9Dialog->setWindowTitle(QCoreApplication::translate("GQtDX9Dialog", "GQtDX9Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GQtDX9Dialog: public Ui_GQtDX9Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GQTDX9DIALOG_H
