#include "MyOpenGL.h"
//链接器添加依赖库OpenGL32.lib glu32.lib

MyOpenGL::MyOpenGL(QWidget*parent)
    : QGLWidget(parent)
{
   //ui.setupUi(this);

    //如果使用用户自定义绘制，则需要设置WA_PaintOnScreen
    setAttribute(Qt::WA_PaintOnScreen, true);
    //不需要默认的Qt背景
    setAttribute(Qt::WA_NoSystemBackground, true);
    //重绘时，绘制所有像素
    setAttribute(Qt::WA_OpaquePaintEvent, true);

    fullscreen = false;
    m_FileName = "D:/workspace/Vs+Qt OpenGL/Resource/Textures/darkbrick.bmp";        //应根据实际存放图片的路径进行修改  不支持dds格式

    m_Light = false;
    m_Blend = false;

    m_xRot = 0.0f;
    m_yRot = 0.0f;
    m_xSpeed = 0.0f;
    m_ySpeed = 0.0f;
    m_Deep = -5.0f;

    
    
 
    QTimer* timer = new QTimer(this);                   //创建一个定时器
   //将定时器的计时信号与updateGL()绑定
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(16);//约60FPS
   
}
void MyOpenGL::initializeGL()
{
    //设置widget的坐标和尺寸
    //setGeometry(300, 150, 400, 300);


    m_Texture = bindTexture(QPixmap(m_FileName));       //载入位图并转换成纹理
    glEnable(GL_TEXTURE_2D);                            //启用纹理映射

    glClearColor(0.0, 0.0, 0.0, 0.0);                   //黑色背景
    glShadeModel(GL_SMOOTH);                            //启用阴影平滑

    glClearDepth(1.0);                                  //设置深度缓存
    glEnable(GL_DEPTH_TEST);                            //启用深度测试
    glDepthFunc(GL_LEQUAL);                             //所作深度测试的类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //告诉系统对透视进行修正
    
     //下面是光源部分
    GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };  //环境光参数
    GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //漫散光参数
    GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f }; //光源位置
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);     //设置环境光
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);     //设置漫射光
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   //设置光源位置
    glEnable(GL_LIGHT1);                                //启动一号光源

    //下面是混合部分
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);                  //全亮度，50%Alpha混合
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);                  //基于源像素alpah通道值得半透明混合函数
   
}

void MyOpenGL::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);               //重置当前的视口
    glMatrixMode(GL_PROJECTION);                        //选择投影矩阵
    glLoadIdentity();                                   //重置投影矩阵
    //设置视口的大小
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);                         //选择模型观察矩阵
    glLoadIdentity();
   
   
}


void MyOpenGL::paintGL()                             //从这里开始进行所以的绘制
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕和深度缓存
    glLoadIdentity();                                   //重置模型观察矩阵
    glTranslatef(0.0f, 0.0f, m_Deep);                   //移入屏幕
    glRotatef(m_xRot, 1.0f, 0.0f, 0.0f);                //绕x轴旋转
    glRotatef(m_yRot, 0.0f, 1.0f, 0.0f);                //绕y轴旋转

    glBindTexture(GL_TEXTURE_2D, m_Texture);            //选择纹理
    glBegin(GL_QUADS);                                  //开始绘制立方体

    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(顶面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(顶面)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);                  //左下(顶面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);                   //右下(顶面)

    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);                  //右上(底面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);                 //左上(底面)
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(底面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(底面)

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);                   //右上(前面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);                  //左上(前面)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);                 //左下(前面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);                  //右下(前面)

    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);                 //右上(后面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);                //左上(后面)
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);                 //左下(后面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);                  //右下(后面)

    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);                  //右上(左面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(左面)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(左面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);                 //右下(左面)

    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(右面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);                   //左上(右面)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);                  //左下(右面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(右面)
   
   
    glEnd();                                            //立方体绘制结束

    m_xRot += 0.5f;
    m_yRot += 0.5f;

    m_xRot += m_xSpeed;                                 //x轴旋转
    m_yRot += m_ySpeed;                                 //y轴旋转
}


void MyOpenGL::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_F1:                                    //F1为全屏和普通屏的切换键
        fullscreen = !fullscreen;
        if (fullscreen)
        {
            showFullScreen();
        }
        else
        {
            showNormal();
        }
        break;
    case Qt::Key_Escape:                                //ESC为退出键
        close();
        break;
    case Qt::Key_B:                                     //B为开始关闭混合而对切换键
        m_Blend = !m_Blend;
        if (m_Blend)
        {
            glEnable(GL_BLEND);                         //开启混合
            glDisable(GL_DEPTH_TEST);                   //关闭深度测试
        }
        else
        {
            glDisable(GL_BLEND);                        //关闭混合
            glEnable(GL_DEPTH_TEST);                    //打开深度测试
        }
        break;
    case Qt::Key_L:                                     //L为开启关闭光源的切换键
        m_Light = !m_Light;
        if (m_Light)
        {
            glEnable(GL_LIGHTING);                      //开启光源
        }
        else
        {
            glDisable(GL_LIGHTING);                     //关闭光源
        }
        break;
    case Qt::Key_PageUp:                                //PageUp按下使木箱移向屏幕内部
        m_Deep -= 0.1f;
        break;
    case Qt::Key_PageDown:                              //PageDown按下使木箱移向观察者
        m_Deep += 0.1f;
        break;
    case Qt::Key_Up:                                    //Up按下减少m_xSpeed
        m_xSpeed -= 0.1f;
        qDebug() << "GLWidget:You press up.";
        break;
    case Qt::Key_Down:                                  //Down按下增加m_xSpeed
        m_xSpeed += 0.1f;
        qDebug() << "GLWidget:You press down.";
        break;
    case Qt::Key_Right:                                 //Right按下减少m_ySpeed
        m_ySpeed -= 0.1f;
        break;
    case Qt::Key_Left:                                  //Left按下增加m_ySpeed
        m_ySpeed += 0.1f;
        break;
    }
}

