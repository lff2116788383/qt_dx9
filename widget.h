#ifndef WIDGET_H
#define WIDGET_H

#include "camera.h"
#include "model.h"

#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWidget>


class Widget : public QOpenGLWidget,public QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w,int h) override;
    virtual bool event(QEvent *e) override;

    void keyPressEvent(QKeyEvent* event);           //处理键盘按下事件

    Model* model;
    Model* plane;
    Camera camera;
    QTimer timer;

private:
    QOpenGLShaderProgram shaderProgram;
};

#endif // WIDGET_H
