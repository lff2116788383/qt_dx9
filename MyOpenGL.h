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
    //��3�����麯�����ض���
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent* event);           //������̰����¼�
private:
    bool fullscreen;                                //�Ƿ�ȫ����ʾ

    QString m_FileName;                             //ͼƬ��·�����ļ���
    GLuint m_Texture;                               //����һ������    

    bool m_Light;                                   //��Դ�Ŀ�/��
    bool m_Blend;                                   //�Ƿ���

    GLfloat m_xRot;                                 //x��ת�Ƕ�
    GLfloat m_yRot;                                 //y��ת�Ƕ�
    GLfloat m_xSpeed;                               //x��ת�ٶ�
    GLfloat m_ySpeed;                               //y��ת�ٶ�
    GLfloat m_Deep;                                 //������Ļ�ľ���
 

private:
    //Ui::MyOpenGLClass ui;

   
  
};
