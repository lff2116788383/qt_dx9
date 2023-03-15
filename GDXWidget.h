//#pragma once
//
//#include <QtWidgets/QWidget>
//#include "ui_GDXWidget.h"
//
//class GDXWidget : public QWidget
//{
//    Q_OBJECT
//
//public:
//    GDXWidget(QWidget *parent = Q_NULLPTR);
//
//private:
//    Ui::GDXWidgetClass ui;
//};


#ifndef _GDXWIDGET_H_
#define _GDXWIDGET_H_

#include <QWidget>
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include "GeometryGenerator.h"
using namespace std;

#pragma comment(lib,"winmm.lib")  //���� timeGetTime()����������ļ�
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

struct SCustomVertex
{
	float x, y, z;
	DWORD color;
};

#define D3DFVF_SCUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

class GDXWidget : public QWidget
{
	Q_OBJECT
public:
	GDXWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
	~GDXWidget();

	//��ʹ��QtĬ�ϵĻ�������
	virtual QPaintEngine* paintEngine() const { return 0; }

	//��ʼ��Direct3D
	bool InitD3D();

	//������������
	bool CreateTriangle();

	void InitScene();   //��ʼ������

	bool CreateBox();
	void CreateBox(GeometryGenerator::MeshData& meshData);

	//����������
	void Frame();

public slots:
	//��Ⱦ
	void Render();

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void resizeEvent(QResizeEvent* event);

private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;    // �����������

	int NumVertices;
	int NumIndices;

	//fps��ص�ȫ�ֱ���
	double countsPerSecond = 0.0;
	__int64 CounterStart = 0;

	int frameCount = 0;
	int fps = 0;

	__int64 frameTimeOld = 0;
	double frameTime;

	void startFPStimer();
	double getTime();
	double getFrameTime();
};

#endif //_GDXWIDGET_H_