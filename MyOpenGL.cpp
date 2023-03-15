#include "MyOpenGL.h"
//���������������OpenGL32.lib glu32.lib

MyOpenGL::MyOpenGL(QWidget*parent)
    : QGLWidget(parent)
{
   //ui.setupUi(this);

    //���ʹ���û��Զ�����ƣ�����Ҫ����WA_PaintOnScreen
    setAttribute(Qt::WA_PaintOnScreen, true);
    //����ҪĬ�ϵ�Qt����
    setAttribute(Qt::WA_NoSystemBackground, true);
    //�ػ�ʱ��������������
    setAttribute(Qt::WA_OpaquePaintEvent, true);

    fullscreen = false;
    m_FileName = "D:/workspace/Vs+Qt OpenGL/Resource/Textures/darkbrick.bmp";        //Ӧ����ʵ�ʴ��ͼƬ��·�������޸�  ��֧��dds��ʽ

    m_Light = false;
    m_Blend = false;

    m_xRot = 0.0f;
    m_yRot = 0.0f;
    m_xSpeed = 0.0f;
    m_ySpeed = 0.0f;
    m_Deep = -5.0f;

    
    
 
    QTimer* timer = new QTimer(this);                   //����һ����ʱ��
   //����ʱ���ļ�ʱ�ź���updateGL()��
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(16);//Լ60FPS
   
}
void MyOpenGL::initializeGL()
{
    //����widget������ͳߴ�
    //setGeometry(300, 150, 400, 300);


    m_Texture = bindTexture(QPixmap(m_FileName));       //����λͼ��ת��������
    glEnable(GL_TEXTURE_2D);                            //��������ӳ��

    glClearColor(0.0, 0.0, 0.0, 0.0);                   //��ɫ����
    glShadeModel(GL_SMOOTH);                            //������Ӱƽ��

    glClearDepth(1.0);                                  //������Ȼ���
    glEnable(GL_DEPTH_TEST);                            //������Ȳ���
    glDepthFunc(GL_LEQUAL);                             //������Ȳ��Ե�����
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //����ϵͳ��͸�ӽ�������
    
     //�����ǹ�Դ����
    GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };  //���������
    GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //��ɢ�����
    GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f }; //��Դλ��
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);     //���û�����
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);     //���������
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   //���ù�Դλ��
    glEnable(GL_LIGHT1);                                //����һ�Ź�Դ

    //�����ǻ�ϲ���
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);                  //ȫ���ȣ�50%Alpha���
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);                  //����Դ����alpahͨ��ֵ�ð�͸����Ϻ���
   
}

void MyOpenGL::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);               //���õ�ǰ���ӿ�
    glMatrixMode(GL_PROJECTION);                        //ѡ��ͶӰ����
    glLoadIdentity();                                   //����ͶӰ����
    //�����ӿڵĴ�С
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);                         //ѡ��ģ�͹۲����
    glLoadIdentity();
   
   
}


void MyOpenGL::paintGL()                             //�����￪ʼ�������ԵĻ���
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�����Ļ����Ȼ���
    glLoadIdentity();                                   //����ģ�͹۲����
    glTranslatef(0.0f, 0.0f, m_Deep);                   //������Ļ
    glRotatef(m_xRot, 1.0f, 0.0f, 0.0f);                //��x����ת
    glRotatef(m_yRot, 0.0f, 1.0f, 0.0f);                //��y����ת

    glBindTexture(GL_TEXTURE_2D, m_Texture);            //ѡ������
    glBegin(GL_QUADS);                                  //��ʼ����������

    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);                  //����(����)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);                 //����(����)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);                  //����(����)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);                   //����(����)

    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);                  //����(����)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);                 //����(����)
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);                //����(����)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);                 //����(����)

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);                   //����(ǰ��)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);                  //����(ǰ��)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);                 //����(ǰ��)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);                  //����(ǰ��)

    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);                 //����(����)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);                //����(����)
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);                 //����(����)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);                  //����(����)

    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);                  //����(����)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);                 //����(����)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);                //����(����)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);                 //����(����)

    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);                  //����(����)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);                   //����(����)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);                  //����(����)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);                 //����(����)
   
   
    glEnd();                                            //��������ƽ���

    m_xRot += 0.5f;
    m_yRot += 0.5f;

    m_xRot += m_xSpeed;                                 //x����ת
    m_yRot += m_ySpeed;                                 //y����ת
}


void MyOpenGL::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_F1:                                    //F1Ϊȫ������ͨ�����л���
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
    case Qt::Key_Escape:                                //ESCΪ�˳���
        close();
        break;
    case Qt::Key_B:                                     //BΪ��ʼ�رջ�϶����л���
        m_Blend = !m_Blend;
        if (m_Blend)
        {
            glEnable(GL_BLEND);                         //�������
            glDisable(GL_DEPTH_TEST);                   //�ر���Ȳ���
        }
        else
        {
            glDisable(GL_BLEND);                        //�رջ��
            glEnable(GL_DEPTH_TEST);                    //����Ȳ���
        }
        break;
    case Qt::Key_L:                                     //LΪ�����رչ�Դ���л���
        m_Light = !m_Light;
        if (m_Light)
        {
            glEnable(GL_LIGHTING);                      //������Դ
        }
        else
        {
            glDisable(GL_LIGHTING);                     //�رչ�Դ
        }
        break;
    case Qt::Key_PageUp:                                //PageUp����ʹľ��������Ļ�ڲ�
        m_Deep -= 0.1f;
        break;
    case Qt::Key_PageDown:                              //PageDown����ʹľ������۲���
        m_Deep += 0.1f;
        break;
    case Qt::Key_Up:                                    //Up���¼���m_xSpeed
        m_xSpeed -= 0.1f;
        qDebug() << "GLWidget:You press up.";
        break;
    case Qt::Key_Down:                                  //Down��������m_xSpeed
        m_xSpeed += 0.1f;
        qDebug() << "GLWidget:You press down.";
        break;
    case Qt::Key_Right:                                 //Right���¼���m_ySpeed
        m_ySpeed -= 0.1f;
        break;
    case Qt::Key_Left:                                  //Left��������m_ySpeed
        m_ySpeed += 0.1f;
        break;
    }
}

