#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"


//��ȾAPIͷ�ļ�
#include "GDXWidget.h"
#include "d3d11renderwidget.h"
#include "GLWidget.h"

//qt�ؼ�ͷ�ļ�
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
	//virtual bool eventFilter(QObject*, QEvent*);              //��д�¼�������
	void keyPressEvent(QKeyEvent* event);                       //��д���̰����¼�
	void keyReleaseEvent(QKeyEvent* event);                     //��д�����ͷ��¼�

private:
	QComboBox* ComboBox_RendererAPI;

	QButtonGroup* pButtonGroup;
	QCheckBox* pCheckBox[3];

	//��Ⱦ������
	GDXWidget* pDX9Widget;
	D3d11RenderWidget* pDX11Widget;

	GLWidget* pGLWidget;
private:
	Ui::MainWindow ui;
};

