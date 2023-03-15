#pragma once

#include <QGLWidget>
#include <QMainWindow>
#include "ui_test.h"

//��ȾAPIͷ�ļ�
#include "GDXWidget.h"
#include "d3d11renderwidget.h"
#include "MyOpenGL.h"

#include <QComboBox>
class test : public QMainWindow
{
	Q_OBJECT

public:
	test(QWidget *parent = Q_NULLPTR);
	~test();

public slots:
	void boxChange(int);
	void CloseRendererWindow();

private:
	Ui::test ui;


	QComboBox* ComboBox_RendererAPI;

	//��Ⱦ������
	GDXWidget* pDX9Widget;
	D3d11RenderWidget* pDX11Widget;

	MyOpenGL* pGLWidget;
};
