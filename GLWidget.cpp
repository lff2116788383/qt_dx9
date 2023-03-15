#include "GLWidget.h"
#include <QOpenGLBuffer>

#include <QDebug>

#include <QTimer>
#define BUFFER_OFFSET(offset) ((void*)(offset))


GLuint VAO = -1;
GLWidget::GLWidget(QWidget* parent) :
    QOpenGLWidget(parent)
{


  //  QTimer* timer = new QTimer(this);                   //创建一个定时器
  ////将定时器的计时信号与updateGL()绑定
  //  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  //  timer->start(16);//约60FPS

    QTimer timer;
    timer.setInterval(18);
    connect(&timer, &QTimer::timeout, this, static_cast<void (GLWidget::*)()>(&GLWidget::update));
    timer.start();
}

GLWidget::~GLWidget()
{

}

void GLWidget::iniDatas()
{
    /*static const float triangle[] = {
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.0f,0.5f,0.0f
    };*/

    static const float vertices[] = {
        0.5f,0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        -0.5f,-0.5f,0.0f,
        -0.5f,0.5f,0.0f
    };

    

    unsigned int indices[] = {
        0,1,2,
        2,0,3
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);//解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);//填充图,，默认
    //    glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);//散点图
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框图
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    m_pShaderProgram = new QOpenGLShaderProgram(this);
    m_pShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/GLSL/vertext.vert");
    m_pShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/GLSL/fragment.frag");
    m_pShaderProgram->link();
    m_pShaderProgram->bind();

    iniDatas();
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL()
{
    static const GLfloat color[] = { 0.0f,0.0f,0.0f,1.0f };

    glClearBufferfv(GL_COLOR, 0, color);

    if (VAO == -1) {
        return;
    }

    glUseProgram(m_pShaderProgram->programId());
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    //update();
}
