/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *test)
    {
        if (test->objectName().isEmpty())
            test->setObjectName(QString::fromUtf8("test"));
        test->resize(400, 300);
        menuBar = new QMenuBar(test);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        test->setMenuBar(menuBar);
        mainToolBar = new QToolBar(test);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        test->addToolBar(mainToolBar);
        centralWidget = new QWidget(test);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        test->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(test);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        test->setStatusBar(statusBar);

        retranslateUi(test);

        QMetaObject::connectSlotsByName(test);
    } // setupUi

    void retranslateUi(QMainWindow *test)
    {
        test->setWindowTitle(QCoreApplication::translate("test", "test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class test: public Ui_test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
