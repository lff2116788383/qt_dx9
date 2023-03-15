

#include "GQtDX9Dialog.h"
#include "GDXWidget.h"
#include "d3d11renderwidget.h"

GQtDX9Dialog::GQtDX9Dialog(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	resize(850, 650);

	//GDXWidget* pDXWidget = new GDXWidget(this);
	//pDXWidget->resize(800, 600);
	//pDXWidget->InitD3D();
	//pDXWidget->CreateTriangle();
	//pDXWidget->move(30, 30);


	//Ìí¼ÓD3D×Ó´°¿Ú
	D3d11RenderWidget* widget = new D3d11RenderWidget(this);
	setCentralWidget(widget);
}

GQtDX9Dialog::~GQtDX9Dialog()
{}