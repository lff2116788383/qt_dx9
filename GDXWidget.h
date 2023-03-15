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

#pragma comment(lib,"winmm.lib")  //调用 timeGetTime()函数所需库文件
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

	//不使用Qt默认的绘制引擎
	virtual QPaintEngine* paintEngine() const { return 0; }

	//初始化Direct3D
	bool InitD3D();

	//创建简单三角形
	bool CreateTriangle();

	void InitScene();   //初始化场景

	bool CreateBox();
	void CreateBox(GeometryGenerator::MeshData& meshData);

	//更新三角形
	void Frame();

public slots:
	//渲染
	void Render();

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void resizeEvent(QResizeEvent* event);

private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;    // 索引缓存对象

	int NumVertices;
	int NumIndices;

	//fps相关的全局变量
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