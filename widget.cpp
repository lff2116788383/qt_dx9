#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , camera(this)
{
    timer.setInterval(18);
    connect(&timer,&QTimer::timeout,this,static_cast<void (Widget::*)()>(&Widget::update));
    timer.start();

    QSurfaceFormat format;
    format.setSamples(50);
    setFormat(format);
}
Widget::~Widget()
{

}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();

    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);               //ºÚÉ«±³¾°
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/model/model.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/model/model.frag");
    shaderProgram.link();

   

    model=Model::createModel("D:/workspace/GameProject/Models/FBXResource/Monster/Idle/Monster.FBX",context(),&shaderProgram); 

    
    plane = Model::createModel("D:/workspace/GameProject/Models/FBXResource/plane/OceanPlane.FBX", context(), &shaderProgram);

    glEnable(GL_DEPTH_TEST);
    camera.init();
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 projection;
    projection.perspective(45.0f,width()/(float)height(),0.1f,500.0f);
    shaderProgram.setUniformValue("projection",projection);
    shaderProgram.setUniformValue("view",camera.getView());

   
    model->draw();
    plane->draw();
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

bool Widget::event(QEvent*e){
    camera.handle(e);
    return QWidget::event(e);
}

void Widget::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        close();
        break;
    default:
        break;
    }
}

