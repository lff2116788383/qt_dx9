/********************************************************************************
** Form generated from reading UI file 'MyOpenGL.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYOPENGL_H
#define UI_MYOPENGL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyOpenGLClass
{
public:

    void setupUi(QWidget *MyOpenGLClass)
    {
        if (MyOpenGLClass->objectName().isEmpty())
            MyOpenGLClass->setObjectName(QString::fromUtf8("MyOpenGLClass"));
        MyOpenGLClass->resize(600, 400);

        retranslateUi(MyOpenGLClass);

        QMetaObject::connectSlotsByName(MyOpenGLClass);
    } // setupUi

    void retranslateUi(QWidget *MyOpenGLClass)
    {
        MyOpenGLClass->setWindowTitle(QCoreApplication::translate("MyOpenGLClass", "MyOpenGL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyOpenGLClass: public Ui_MyOpenGLClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYOPENGL_H
