#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>

#include <QOpenGLShaderProgram>

#include <QOpenGLExtraFunctions>
//class GLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core

class GLWidget : public QOpenGLWidget, public QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget* parent = nullptr);
    ~GLWidget();

protected:

    void iniDatas();

    void initializeGL(); //��ʼ����صĲ���ȫ��������������
    void resizeGL(int w, int h);
    void paintGL();
private:
    QOpenGLShaderProgram* m_pShaderProgram = nullptr;

};

#endif // GLWIDGET_H

