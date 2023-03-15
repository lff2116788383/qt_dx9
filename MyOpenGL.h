#pragma once

#include <QtWidgets/QWidget>
//#include "ui_MyOpenGL.h"
#include <QGLWidget>
#include <qgl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QKeyEvent>
#include <QTimer>
#include <QFileDialog>
#include <QImageReader>
#include <QImageWriter>
#include <QFileInfo>


#include <QDebug>

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include "GeometryGenerator.h"



class MyOpenGL : public QGLWidget
{
    Q_OBJECT

public:

    MyOpenGL(QWidget*parent = Q_NULLPTR);

protected:
    //对3个纯虚函数的重定义
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent* event);           //处理键盘按下事件
private:
    bool fullscreen;                                //是否全屏显示

    QString m_FileName;                             //图片的路径及文件名
    GLuint m_Texture;                               //储存一个纹理    

    bool m_Light;                                   //光源的开/关
    bool m_Blend;                                   //是否混合

    GLfloat m_xRot;                                 //x旋转角度
    GLfloat m_yRot;                                 //y旋转角度
    GLfloat m_xSpeed;                               //x旋转速度
    GLfloat m_ySpeed;                               //y旋转速度
    GLfloat m_Deep;                                 //深入屏幕的距离
 

private:
    //Ui::MyOpenGLClass ui;

   
  
};
