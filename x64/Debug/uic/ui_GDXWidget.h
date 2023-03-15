/********************************************************************************
** Form generated from reading UI file 'GDXWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GDXWIDGET_H
#define UI_GDXWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GDXWidgetClass
{
public:

    void setupUi(QWidget *GDXWidgetClass)
    {
        if (GDXWidgetClass->objectName().isEmpty())
            GDXWidgetClass->setObjectName(QString::fromUtf8("GDXWidgetClass"));
        GDXWidgetClass->resize(600, 400);

        retranslateUi(GDXWidgetClass);

        QMetaObject::connectSlotsByName(GDXWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *GDXWidgetClass)
    {
        GDXWidgetClass->setWindowTitle(QCoreApplication::translate("GDXWidgetClass", "GDXWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GDXWidgetClass: public Ui_GDXWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GDXWIDGET_H
