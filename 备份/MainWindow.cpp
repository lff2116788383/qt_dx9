#include "MainWindow.h"


#include <QPushButton>
#include <QComboBox>
#include <QListView>
#include <QDebug>
MainWindow::MainWindow(QGLWidget*parent)
	: QGLWidget(parent)
{
	ui.setupUi(this);

	resize(850, 650);
	

	ComboBox_RendererAPI = new QComboBox(this);
	ComboBox_RendererAPI->addItem("Direcx9");
	ComboBox_RendererAPI->addItem("Direcx11");
	ComboBox_RendererAPI->addItem("OpenGL");
	
	ComboBox_RendererAPI->setStyleSheet("QComboBox{border:1px solid gray;}"
		"QComboBox QAbstractItemView::item{height:20px;}" //����ѡ��߶�
		"QComboBox::down-arrow{image:url(:/icon/arrowdown);}" //������ͷ
		"QComboBox::drop-down{border:0px;}"); //������ť
	ComboBox_RendererAPI->setView(new QListView());
	
	ComboBox_RendererAPI->setGeometry(this->width()- ComboBox_RendererAPI->width(),12, ComboBox_RendererAPI->width(), ComboBox_RendererAPI->height());
	connect(ComboBox_RendererAPI, SIGNAL(currentIndexChanged(int)), this, SLOT(boxChange(int)));
	
	pDX9Widget = new GDXWidget(this);
	pDX9Widget->setGeometry(0, 0, 400, 300);
	pDX9Widget->resize(400, 300);
	pDX9Widget->InitD3D();
	pDX9Widget->CreateTriangle();
	//pDX9Widget->move(30, 30);
	pDX9Widget->hide();


	pDX11Widget = new D3d11RenderWidget(this);
	pDX11Widget->setGeometry(0,0,400,300);
	pDX11Widget->resize(400, 300);
	//setCentralWidget(pDX11Widget);
	//pDX11Widget->move(30, 30);
	pDX11Widget->hide();


	pGLWidget =new  MyOpenGL(this);

	pGLWidget->show();

	connect(pDX9Widget, SIGNAL(destroyed()), this, SLOT(CloseRendererWindow()));
	//connect(pDX11Widget, SIGNAL(destroyed()), this, SLOT(CloseRendererWindow()));

	
}

MainWindow::~MainWindow()
{
}

void MainWindow::boxChange(int)
{
	qDebug() << "Renderer API Changed! ";
	if (ComboBox_RendererAPI->currentText()==QString("Direcx9"))
	{
		qDebug() << "Current Renderer API:" << ComboBox_RendererAPI->currentText();
		pDX11Widget->hide();

		pDX9Widget->show();
		
	}
	if (ComboBox_RendererAPI->currentText() == QString("Direcx11"))
	{

		qDebug() << "Current Renderer API:" << ComboBox_RendererAPI->currentText();
		pDX9Widget->hide();

		pDX11Widget->show();
	}

}

void MainWindow::CloseRendererWindow()
{
	qDebug() << "It is Destroyed!";
}