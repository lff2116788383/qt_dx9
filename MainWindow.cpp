#include "MainWindow.h"
#include "GeometryGenerator.h"
#include <QListView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	resize(850, 650);
	//setStyleSheet("background-color:white;");

	ComboBox_RendererAPI = new QComboBox(this);
	ComboBox_RendererAPI->addItem("Direcx9");
	ComboBox_RendererAPI->addItem("Direcx11");
	ComboBox_RendererAPI->addItem("OpenGL");

	ComboBox_RendererAPI->setStyleSheet("QComboBox{border:1px solid gray;}"
		"QComboBox QAbstractItemView::item{height:20px;}" //下拉选项高度
		"QComboBox::down-arrow{image:url(:/icon/arrowdown);}" //下拉箭头
		"QComboBox::drop-down{border:0px;}"); //下拉按钮
	ComboBox_RendererAPI->setView(new QListView());

	ComboBox_RendererAPI->setGeometry(this->width() - ComboBox_RendererAPI->width(), 12, ComboBox_RendererAPI->width(), ComboBox_RendererAPI->height());
	connect(ComboBox_RendererAPI, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::boxChange);

	//通过鼠标切换选项会进入该函数
	//通过按钮改变currentIndex不会进入该函数
	//connect(ComboBox_RendererAPI, SIGNAL(activated(int)), this, SLOT(boxChange()));


	//创建物体
	GeometryGenerator::MeshData box;
	GeometryGenerator::CreateBox(1.0f, 1.0f, 1.0f, box);



	pDX9Widget = new GDXWidget(this);
	pDX9Widget->setGeometry(0, 0, 400, 300);
	//pDX9Widget->resize(400, 300);
	pDX9Widget->InitD3D();
	//pDX9Widget->InitScene();
	pDX9Widget->CreateBox(box);
	pDX9Widget->hide();


	pDX11Widget = new D3d11RenderWidget(this);
	pDX11Widget->setGeometry(0, 0, 400, 300);
	pDX11Widget->InitD3D();
	//pDX11Widget->InitScene();
	pDX11Widget->CreateBox(box);
	//pDX11Widget->resize(400, 300);
	//setCentralWidget(pDX11Widget);
	pDX11Widget->hide();


	pGLWidget = new  GLWidget(this);
	pGLWidget->setGeometry(0, 0, 400, 300);
	
	//pGLWidget->resize(400, 300);
	pGLWidget->hide();


	//pDX9Widget->installEventFilter(this);
	//pDX11Widget->installEventFilter(this);
	//pGLWidget->installEventFilter(this);
	//ComboBox_RendererAPI->installEventFilter(this);
	

	connect(pDX9Widget, SIGNAL(destroyed()), this, SLOT(CloseRendererWindow()));
	connect(pDX11Widget, SIGNAL(destroyed()), this, SLOT(CloseRendererWindow()));
	connect(pGLWidget, SIGNAL(destroyed()), this, SLOT(CloseRendererWindow()));

	initCheckBoxGroup();
	connect(pButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(slot_btnGroupClicked(int)));
}

MainWindow::~MainWindow()
{
}
void MainWindow::initCheckBoxGroup()
{
	pButtonGroup = new QButtonGroup(this);
	pButtonGroup->setExclusive(true);               //设置这个按钮组为互斥模式
	for (size_t i = 0; i < 3; i++)
	{
		pCheckBox[i] = new QCheckBox(this);
	}
	pCheckBox[0]->setText("Direcx9");
	pCheckBox[1]->setText("Direcx11");
	pCheckBox[2]->setText("OpenGL");

	int x=750;
	int y=500;
	pCheckBox[0]->setGeometry(x, y, pCheckBox[0]->width(), pCheckBox[0]->height());
	pCheckBox[1]->setGeometry(x, y+30, pCheckBox[1]->width(), pCheckBox[1]->height());
	pCheckBox[2]->setGeometry(x, y+60, pCheckBox[2]->width(), pCheckBox[2]->height());

	

	pButtonGroup->addButton(pCheckBox[0], 0);
	pButtonGroup->addButton(pCheckBox[1], 1);
	pButtonGroup->addButton(pCheckBox[2], 2);

	
	
}

void MainWindow::boxChange(int)
{
	qDebug() << "Renderer API Changed! "<< ComboBox_RendererAPI->currentIndex() ;

	
	if (ComboBox_RendererAPI->currentText() == QString("Direcx9"))
	{
		qDebug() << "Current Renderer API:" << ComboBox_RendererAPI->currentText();
		pDX11Widget->hide();
		pGLWidget->hide();

		pDX9Widget->show();

	}
	if (ComboBox_RendererAPI->currentText() == QString("Direcx11"))
	{

		qDebug() << "Current Renderer API:" << ComboBox_RendererAPI->currentText();
		pDX9Widget->hide();
		pGLWidget->hide();

		pDX11Widget->show();
	}
	if (ComboBox_RendererAPI->currentIndex() == 2)
	{

		qDebug() << "Current Renderer API:" << ComboBox_RendererAPI->currentText();
		pDX9Widget->hide();
		pDX11Widget->hide();

		pGLWidget->show();
	}
}

void MainWindow::CloseRendererWindow()
{
	qDebug() << "It is Destroyed!";
}

void MainWindow::slot_btnGroupClicked(int nId)
{
	//do somethings...
	switch (nId)
	{
	case 0:
		qDebug() << "checkbox[0] is selected";
		pDX11Widget->hide();
		pGLWidget->hide();

		pDX9Widget->show();
		break;
	default:
		break;
	}
}

//
//bool MainWindow::eventFilter(QObject* target, QEvent* event)
//{
//	////返回true为不再转发，false则让其继续被处理
//	//if (event->type() == QEvent::KeyPress)
//	//{
//	//	//将QEvent对象转换为真正的QKeyEvent对象
//	//	QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
//	//	if (keyEvent->key() == Qt::Key_Tab)
//	//	{
//	//		qDebug() << "MainWindow:You press tab.";
//	//		return true;
//	//	}
//	//	else
//	//	{
//	//		return true;
//	//	}
//		//else
//		//{
//		//	return false;//继续传播
//		//}
//
//
//		/*if (target == pGLWidget)
//		{
//			event->accept();
//			return true;
//		}
//
//		if (target == ComboBox_RendererAPI)
//		{
//			event->ignore();
//			return true;
//		}*/
//	//}
//	//return QObject::eventFilter(target, event);
//	return true;
//}


void MainWindow::keyPressEvent(QKeyEvent* event)
{
	
	//if ((event->key() == Qt::Key::Key_F) && !event->isAutoRepeat())
	//{
	//	
	//	qDebug() << "MainWindow:You press F.";
	//	event->accept();
	//}
	//else {
	//	event->ignore();
	//}

	/*switch (event->key())
	{
	case Qt::Key::Key_Up:
		qDebug() << "MainWindow:You press up.";
		ComboBox_RendererAPI->move(ComboBox_RendererAPI->pos().x(), ComboBox_RendererAPI->pos().y()-5);
		break;
	case Qt::Key::Key_Down:
		ComboBox_RendererAPI->move(ComboBox_RendererAPI->pos().x(), ComboBox_RendererAPI->pos().y() + 5);
		qDebug() << "MainWindow:You press down.";
		break;
	default:
		break;
	}*/
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
}
