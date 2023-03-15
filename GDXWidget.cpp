//#include "GDXWidget.h"
//
//GDXWidget::GDXWidget(QWidget *parent)
//    : QWidget(parent)
//{
//    ui.setupUi(this);
//}


#include "GDXWidget.h"
#include "strsafe.h"
#include <QResizeEvent>
#include <QTimer>
#include <QDebug>



GDXWidget::GDXWidget(QWidget* parent, Qt::WindowFlags f) :
	QWidget(parent, f), m_pD3D(0), m_pDevice(0), m_pVB(0),m_pIB(0), NumVertices(0),NumIndices(0)
{
	////如果使用用户自定义绘制，则需要设置WA_PaintOnScreen
	//setAttribute(Qt::WA_PaintOnScreen, true);
	////不需要默认的Qt背景
	//setAttribute(Qt::WA_NoSystemBackground, true);
	////重绘时，绘制所有像素
	//setAttribute(Qt::WA_OpaquePaintEvent, true);

	//设置窗口属性，关键步骤，否则D3D绘制出问题
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);
	

	//QTimer* pTimer = new QTimer(this);
	//connect(pTimer, SIGNAL(timeout()), this, SLOT(update()));
	//pTimer->start(16); //约60FPS

	
}

GDXWidget::~GDXWidget()
{
	if (0 != m_pVB) m_pVB->Release();
	if (0 != m_pIB) m_pIB->Release();
	if (0 != m_pDevice) m_pDevice->Release();
	if (0 != m_pD3D) m_pD3D->Release();
}



//fps相关函数
void GDXWidget::startFPStimer()
{
	LARGE_INTEGER frequencyCount;
	QueryPerformanceFrequency(&frequencyCount);

	countsPerSecond = double(frequencyCount.QuadPart);

	QueryPerformanceCounter(&frequencyCount);
	CounterStart = frequencyCount.QuadPart;
}

double GDXWidget::getTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return double(currentTime.QuadPart - CounterStart) / countsPerSecond;
}

//获取每帧间隔时间
double GDXWidget::getFrameTime()
{
	LARGE_INTEGER currentTime;
	__int64 tickCount;
	QueryPerformanceCounter(&currentTime);

	tickCount = currentTime.QuadPart - frameTimeOld;
	frameTimeOld = currentTime.QuadPart;

	if (tickCount < 0.0f)
		tickCount = 0.0f;

	return float(tickCount) / countsPerSecond;
}

void GDXWidget::paintEvent(QPaintEvent* event)
{
	//计算fps
	frameCount++;
	if (getTime() > 1.0f)
	{
		fps = frameCount;
		frameCount = 0;
		startFPStimer();
		//设置父窗口标题显示fps值
		parentWidget()->setWindowTitle("FPS: " + QString::number(fps));
	}
	frameTime = getFrameTime();

	Frame();//更新场景
	Render();
	update();
}

void GDXWidget::resizeEvent(QResizeEvent* event)
{}

bool GDXWidget::InitD3D()
{
	/*if (0 == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) return false;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, (HWND)winId(),
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pDevice))) return false;

	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);*/


	// 【Direct3D初始化四步曲之一，创接口】：创建Direct3D接口对象, 以便用该Direct3D对象创建Direct3D设备对象
//--------------------------------------------------------------------------------------
	//Direct3D接口对象的创建
	if (0 == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) return false;

	//--------------------------------------------------------------------------------------
	// 【Direct3D初始化四步曲之二,取信息】：获取硬件设备信息
	//--------------------------------------------------------------------------------------
	D3DCAPS9 caps; int vp = 0;
	if (FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		return false;
	}
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;   //支持硬件顶点运算，我们就采用硬件顶点运算，妥妥的
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING; //不支持硬件顶点运算，无奈只好采用软件顶点运算

	//--------------------------------------------------------------------------------------
	// 【Direct3D初始化四步曲之三，填内容】：填充D3DPRESENT_PARAMETERS结构体
	//--------------------------------------------------------------------------------------
	/*D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = this->width();
	d3dpp.BackBufferHeight = this->height();
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = (HWND)winId();
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;*/

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	
	
	//--------------------------------------------------------------------------------------
	// 【Direct3D初始化四步曲之四，创设备】：创建Direct3D设备接口
	//--------------------------------------------------------------------------------------
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		(HWND)winId() , vp, &d3dpp, &m_pDevice)))
		return false;

	//设置渲染状态
	/*m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE); */
	// 设置渲染状态
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);      //关闭光照
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);   //开启背面消隐
	
	return true;
}

bool GDXWidget::CreateTriangle()
{
	SCustomVertex vertices[] = {
		{ -1.0f,-1.0f, 0.0f, 0xffff0000, },
		{  1.0f,-1.0f, 0.0f, 0xff0000ff, },
		{  0.0f, 1.0f, 0.0f, 0xffffffff, },
	};
	if (FAILED(m_pDevice->CreateVertexBuffer(3 * sizeof(SCustomVertex), 0, D3DFVF_SCUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pVB, 0))) return false;

	void* pVertices;
	if (FAILED(m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0))) return false;
	memcpy(pVertices, vertices, sizeof(vertices));
	m_pVB->Unlock();

	return true;
}

void GDXWidget::InitScene()
{
	/*SCustomVertex vertices[] = {
		{ -1.0f,-1.0f, 0.0f, 0xffff0000, },
		{  1.0f,-1.0f, 0.0f, 0xff0000ff, },
		{  0.0f, 1.0f, 0.0f, 0xffffffff, },
	};*/


	SCustomVertex arr[] = {
		{ -1.0f,-1.0f, 0.0f, 0xffff0000, },
		{  1.0f,-1.0f, 0.0f, 0xff0000ff, },
		{  0.0f, 1.0f, 0.0f, 0xffffffff, },
	};
	
	vector<SCustomVertex> vec;
	vec.push_back(arr[0]);
	vec.push_back(arr[1]);
	vec.push_back(arr[2]);



	if (FAILED(m_pDevice->CreateVertexBuffer(3 * sizeof(SCustomVertex), 0, D3DFVF_SCUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pVB, 0))) return;

	SCustomVertex* v;
	m_pVB->Lock(0, 0, (void**)&v, 0);

	/*v[0].x = -1, v[0].y = -1, v[0].z = 0, v[0].color = D3DCOLOR_XRGB(255, 0, 0);
	v[1].x = 0, v[1].y = 1, v[1].z = 0, v[1].color = D3DCOLOR_XRGB(0, 255, 0);
	v[2].x = 1, v[2].y = -1, v[2].z = 0, v[2].color = D3DCOLOR_XRGB(0, 0, 255);*/

	for (size_t i = 0; i < vec.size(); i++)
	{
		v[i] = vec[i];
	}
	m_pVB->Unlock();
}



bool GDXWidget::CreateBox()
{
//	srand(timeGetTime());      //用系统时间初始化随机种子 
//	//--------------------------------------------------------------------------------------
//// 【顶点缓存、索引缓存绘图四步曲之二】：创建顶点缓存和索引缓存
////--------------------------------------------------------------------------------------
////创建顶点缓存
//	if (FAILED(m_pDevice->CreateVertexBuffer(18 * sizeof(SCustomVertex),
//		0, D3DFVF_SCUSTOMVERTEX,
//		D3DPOOL_DEFAULT, &m_pVB, NULL)))
//	{
//		return E_FAIL;
//	}
//	// 创建索引缓存
//	if (FAILED(m_pDevice->CreateIndexBuffer(48 * sizeof(WORD), 0,
//		D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL)))
//	{
//		return E_FAIL;
//
//	}
//	//--------------------------------------------------------------------------------------
//	// 【顶点缓存、索引缓存绘图四步曲之三】：访问顶点缓存和索引缓存
//	//--------------------------------------------------------------------------------------
//	//顶点数据的设置，
//	SCustomVertex Vertices[17];
//	Vertices[0].x = 400;
//	Vertices[0].y = 300;
//	Vertices[0].z = 0.0f;
//	Vertices[0].rhw = 1.0f;
//	Vertices[0].color = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
//	for (int i = 0; i < 16; i++)
//	{
//		Vertices[i + 1].x = (float)(250 * sin(i * 3.14159 / 8.0)) + 400;
//		Vertices[i + 1].y = -(float)(250 * cos(i * 3.14159 / 8.0)) + 300;
//		Vertices[i + 1].z = 0.0f;
//		Vertices[i + 1].rhw = 1.0f;
//		Vertices[i + 1].color = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
//	}
//
//	//填充顶点缓冲区
//	VOID* pVertices;
//	if (FAILED(m_pVB->Lock(0, sizeof(Vertices), (void**)&pVertices, 0)))
//		return false;
//	memcpy(pVertices, Vertices, sizeof(Vertices));
//	m_pVB->Unlock();
//
//	//索引数组的设置
//	WORD Indices[] = { 0,1,2, 0,2,3, 0,3,4, 0,4,5, 0,5,6, 0,6,7, 0,7,8, 0,8,9, 0,9,10, 0,10,11 ,0,11,12, 0,12,13 ,0,13,14 ,0,14,15 ,0,15,16, 0, 16,1 };
//
//	// 填充索引数据
//	WORD* pIndices = NULL;
//	m_pIB->Lock(0, 0, (void**)&pIndices, 0);
//	memcpy(pIndices, Indices, sizeof(Indices));
//	m_pIB->Unlock();
	return true;
}

void GDXWidget::CreateBox(GeometryGenerator::MeshData& meshData)
{
	srand(timeGetTime());      //用系统时间初始化随机种子 
//--------------------------------------------------------------------------------------
// 【顶点缓存、索引缓存绘图四步曲之二】：创建顶点缓存和索引缓存
//--------------------------------------------------------------------------------------
//创建顶点缓存
	if (FAILED(m_pDevice->CreateVertexBuffer(meshData.Vertices.size() * sizeof(SCustomVertex),
		0, D3DFVF_SCUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pVB, NULL)))
	{
		return ;
	}
	// 创建索引缓存
	if (FAILED(m_pDevice->CreateIndexBuffer(meshData.Indices.size() * sizeof(WORD), 0,
		D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL)))
	{
		return ;

	}
	
	SCustomVertex* vertices;
	m_pVB->Lock(0, 0, (void**)&vertices, 0);

	//UINT k = 0;	// 每个顶点都偏移k，但因为做的分别渲染，索引信息并不需要偏移k
	for (size_t i = 0; i < meshData.Vertices.size(); i++)
	{
		vertices[i].x = meshData.Vertices[i].Position.x;
		vertices[i].y = meshData.Vertices[i].Position.y;
		vertices[i].z = meshData.Vertices[i].Position.z;
		vertices[i].color = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	}
	m_pVB->Unlock();
	qDebug() << "meshData Vertex size:" << meshData.Vertices.size();
	for (size_t i = 0; i < meshData.Vertices.size(); i++)
	{
		qDebug() << i<<"Vertex pos:" << meshData.Vertices[i].Position.x << meshData.Vertices[i].Position.x << meshData.Vertices[i].Position.z;
	}

	qDebug() << "meshData Indice size:" << meshData.Indices.size();
	for (size_t i = 0; i < meshData.Indices.size(); i++)
	{
		
		qDebug() << i << "Indice data:" << meshData.Indices[i];
	}

	// 填充索引数据
	WORD* pIndices = NULL;
	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	for (size_t i = 0; i < meshData.Indices.size(); i++)
	{
		pIndices[i] = meshData.Indices[i];
	}
	m_pIB->Unlock();


	NumVertices = meshData.Vertices.size();
	NumIndices = meshData.Indices.size();

	qDebug() << "Vertex size:" << NumVertices;
	qDebug() << "Indice size:" << NumIndices;
}

//-----------------------------------【Get_FPS( )函数】------------------------------------------
//	描述：用于计算每秒帧速率的一个函数
//--------------------------------------------------------------------------------------------------
float Get_FPS()
{

	//定义四个静态变量
	static float  fps = 0; //我们需要计算的FPS值
	static int    frameCount = 0;//帧数
	static float  currentTime = 0.0f;//当前时间
	static float  lastTime = 0.0f;//持续时间

	frameCount++;//每调用一次Get_FPS()函数，帧数自增1
	currentTime = timeGetTime() * 0.001f;//获取系统时间，其中timeGetTime函数返回的是以毫秒为单位的系统时间，所以需要乘以0.001，得到单位为秒的时间

	//如果当前时间减去持续时间大于了1秒钟，就进行一次FPS的计算和持续时间的更新，并将帧数值清零
	if (currentTime - lastTime > 1.0f) //将时间控制在1秒钟
	{
		fps = (float)frameCount / (currentTime - lastTime);//计算这1秒钟的FPS值
		lastTime = currentTime; //将当前时间currentTime赋给持续时间lastTime，作为下一秒的基准时间
		frameCount = 0;//将本次帧数frameCount值清零
	}

	return fps;
}


void GDXWidget::Render()
{
	//m_pDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	//if (SUCCEEDED(m_pDevice->BeginScene())) {
	//	Frame();
	//	m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(SCustomVertex));
	//	m_pDevice->SetFVF(D3DFVF_SCUSTOMVERTEX);
	//	//m_pDevice->SetIndices(m_pIB);//设置索引缓存
	//	//m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 17, 0, 16);//利用索引缓存配合顶点缓存绘制图形
	//	m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	//	m_pDevice->EndScene();
	//}
	//m_pDevice->Present(0, 0, 0, 0);


	//--------------------------------------------------------------------------------------
	// 【Direct3D渲染五步曲之一】：清屏操作
	//--------------------------------------------------------------------------------------
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//定义一个矩形，用于获取主窗口矩形
	RECT formatRect;
	GetClientRect((HWND)winId(), &formatRect);

	//--------------------------------------------------------------------------------------
	// 【Direct3D渲染五步曲之二】：开始绘制
	//--------------------------------------------------------------------------------------
	m_pDevice->BeginScene();                     // 开始绘制
	/*Frame();*/
	//--------------------------------------------------------------------------------------
	// 【Direct3D渲染五步曲之三】：正式绘制
	//--------------------------------------------------------------------------------------
		// 设置渲染状态
	//m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);//这句代码可省略，因为高洛德着色模式为D3D默认的着色模式
	
	//-------------------------------------------------------------------
	// 【顶点缓存、索引缓存绘图四步曲之四】：绘制图形
	//--------------------------------------------------------------------
	m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(SCustomVertex));//把包含的几何体信息的顶点缓存和渲染流水线相关联
	m_pDevice->SetFVF(D3DFVF_SCUSTOMVERTEX);//指定我们使用的灵活顶点格式的宏名称
	if (NumIndices>0)
	{
		m_pDevice->SetIndices(m_pIB);//设置索引缓存
		m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVertices, 0, NumIndices);//利用索引缓存配合顶点缓存绘制图形
	}
	else
	{
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);//从第0个点开始用D3DPT_TRIANGLELIST 模式渲染1个三角形
	}
	

	//--------------------------------------------------------------------------------------
	// 【Direct3D渲染五步曲之四】：结束绘制
	//--------------------------------------------------------------------------------------
	m_pDevice->EndScene();                       // 结束绘制
	//--------------------------------------------------------------------------------------
	// 【Direct3D渲染五步曲之五】：显示翻转
	//--------------------------------------------------------------------------------------
	m_pDevice->Present(NULL, NULL, NULL, NULL);  // 翻转与显示
}

void GDXWidget::Frame()
{
	D3DXMATRIXA16 matWorld;

	UINT iTime = timeGetTime() % 1000;
	FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
	D3DXMatrixRotationY(&matWorld, fAngle);
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}
//然后通过Qt设计师，拉一个窗口框GQtDX9Dialog，将GDXWidget的一个实例放入该窗口即可。