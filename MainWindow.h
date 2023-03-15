#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"


//渲染API头文件
#include "GDXWidget.h"
#include "d3d11renderwidget.h"
#include "GLWidget.h"

//qt控件头文件
#include <QComboBox>
#include <QButtonGroup>
#include <QCheckBox>
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

	void initCheckBoxGroup();
public slots:
	void boxChange(int);
	void CloseRendererWindow();
	void slot_btnGroupClicked(int);
protected:
	//virtual bool eventFilter(QObject*, QEvent*);              //重写事件过滤器
	void keyPressEvent(QKeyEvent* event);                       //重写键盘按下事件
	void keyReleaseEvent(QKeyEvent* event);                     //重写键盘释放事件

private:
	QComboBox* ComboBox_RendererAPI;

	QButtonGroup* pButtonGroup;
	QCheckBox* pCheckBox[3];

	//渲染窗口类
	GDXWidget* pDX9Widget;
	D3d11RenderWidget* pDX11Widget;

	GLWidget* pGLWidget;
private:
	Ui::MainWindow ui;
};

