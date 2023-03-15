#pragma once

#include <QMainWindow>
#include <QGLWidget>
#include "ui_MainWindow.h"
//渲染API头文件
#include "GDXWidget.h"
#include "d3d11renderwidget.h"
#include "MyOpenGL.h"

class MainWindow : public QGLWidget
{
	Q_OBJECT

public:
	MainWindow(QGLWidget*parent = Q_NULLPTR);
	~MainWindow();

public slots:
	void boxChange(int);
	void CloseRendererWindow();

private:
	Ui::MainWindow ui;

	QComboBox* ComboBox_RendererAPI;

	//渲染窗口类
	GDXWidget* pDX9Widget;
	D3d11RenderWidget* pDX11Widget;

	MyOpenGL* pGLWidget;
};
