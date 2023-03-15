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
	////���ʹ���û��Զ�����ƣ�����Ҫ����WA_PaintOnScreen
	//setAttribute(Qt::WA_PaintOnScreen, true);
	////����ҪĬ�ϵ�Qt����
	//setAttribute(Qt::WA_NoSystemBackground, true);
	////�ػ�ʱ��������������
	//setAttribute(Qt::WA_OpaquePaintEvent, true);

	//���ô������ԣ��ؼ����裬����D3D���Ƴ�����
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);
	

	//QTimer* pTimer = new QTimer(this);
	//connect(pTimer, SIGNAL(timeout()), this, SLOT(update()));
	//pTimer->start(16); //Լ60FPS

	
}

GDXWidget::~GDXWidget()
{
	if (0 != m_pVB) m_pVB->Release();
	if (0 != m_pIB) m_pIB->Release();
	if (0 != m_pDevice) m_pDevice->Release();
	if (0 != m_pD3D) m_pD3D->Release();
}



//fps��غ���
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

//��ȡÿ֡���ʱ��
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
	//����fps
	frameCount++;
	if (getTime() > 1.0f)
	{
		fps = frameCount;
		frameCount = 0;
		startFPStimer();
		//���ø����ڱ�����ʾfpsֵ
		parentWidget()->setWindowTitle("FPS: " + QString::number(fps));
	}
	frameTime = getFrameTime();

	Frame();//���³���
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


	// ��Direct3D��ʼ���Ĳ���֮һ�����ӿڡ�������Direct3D�ӿڶ���, �Ա��ø�Direct3D���󴴽�Direct3D�豸����
//--------------------------------------------------------------------------------------
	//Direct3D�ӿڶ���Ĵ���
	if (0 == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) return false;

	//--------------------------------------------------------------------------------------
	// ��Direct3D��ʼ���Ĳ���֮��,ȡ��Ϣ������ȡӲ���豸��Ϣ
	//--------------------------------------------------------------------------------------
	D3DCAPS9 caps; int vp = 0;
	if (FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		return false;
	}
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;   //֧��Ӳ���������㣬���ǾͲ���Ӳ���������㣬���׵�
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING; //��֧��Ӳ���������㣬����ֻ�ò��������������

	//--------------------------------------------------------------------------------------
	// ��Direct3D��ʼ���Ĳ���֮���������ݡ������D3DPRESENT_PARAMETERS�ṹ��
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
	// ��Direct3D��ʼ���Ĳ���֮�ģ����豸��������Direct3D�豸�ӿ�
	//--------------------------------------------------------------------------------------
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		(HWND)winId() , vp, &d3dpp, &m_pDevice)))
		return false;

	//������Ⱦ״̬
	/*m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE); */
	// ������Ⱦ״̬
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);      //�رչ���
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);   //������������
	
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
//	srand(timeGetTime());      //��ϵͳʱ���ʼ��������� 
//	//--------------------------------------------------------------------------------------
//// �����㻺�桢���������ͼ�Ĳ���֮�������������㻺�����������
////--------------------------------------------------------------------------------------
////�������㻺��
//	if (FAILED(m_pDevice->CreateVertexBuffer(18 * sizeof(SCustomVertex),
//		0, D3DFVF_SCUSTOMVERTEX,
//		D3DPOOL_DEFAULT, &m_pVB, NULL)))
//	{
//		return E_FAIL;
//	}
//	// ������������
//	if (FAILED(m_pDevice->CreateIndexBuffer(48 * sizeof(WORD), 0,
//		D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL)))
//	{
//		return E_FAIL;
//
//	}
//	//--------------------------------------------------------------------------------------
//	// �����㻺�桢���������ͼ�Ĳ���֮���������ʶ��㻺�����������
//	//--------------------------------------------------------------------------------------
//	//�������ݵ����ã�
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
//	//��䶥�㻺����
//	VOID* pVertices;
//	if (FAILED(m_pVB->Lock(0, sizeof(Vertices), (void**)&pVertices, 0)))
//		return false;
//	memcpy(pVertices, Vertices, sizeof(Vertices));
//	m_pVB->Unlock();
//
//	//�������������
//	WORD Indices[] = { 0,1,2, 0,2,3, 0,3,4, 0,4,5, 0,5,6, 0,6,7, 0,7,8, 0,8,9, 0,9,10, 0,10,11 ,0,11,12, 0,12,13 ,0,13,14 ,0,14,15 ,0,15,16, 0, 16,1 };
//
//	// �����������
//	WORD* pIndices = NULL;
//	m_pIB->Lock(0, 0, (void**)&pIndices, 0);
//	memcpy(pIndices, Indices, sizeof(Indices));
//	m_pIB->Unlock();
	return true;
}

void GDXWidget::CreateBox(GeometryGenerator::MeshData& meshData)
{
	srand(timeGetTime());      //��ϵͳʱ���ʼ��������� 
//--------------------------------------------------------------------------------------
// �����㻺�桢���������ͼ�Ĳ���֮�������������㻺�����������
//--------------------------------------------------------------------------------------
//�������㻺��
	if (FAILED(m_pDevice->CreateVertexBuffer(meshData.Vertices.size() * sizeof(SCustomVertex),
		0, D3DFVF_SCUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pVB, NULL)))
	{
		return ;
	}
	// ������������
	if (FAILED(m_pDevice->CreateIndexBuffer(meshData.Indices.size() * sizeof(WORD), 0,
		D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL)))
	{
		return ;

	}
	
	SCustomVertex* vertices;
	m_pVB->Lock(0, 0, (void**)&vertices, 0);

	//UINT k = 0;	// ÿ�����㶼ƫ��k������Ϊ���ķֱ���Ⱦ��������Ϣ������Ҫƫ��k
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

	// �����������
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

//-----------------------------------��Get_FPS( )������------------------------------------------
//	���������ڼ���ÿ��֡���ʵ�һ������
//--------------------------------------------------------------------------------------------------
float Get_FPS()
{

	//�����ĸ���̬����
	static float  fps = 0; //������Ҫ�����FPSֵ
	static int    frameCount = 0;//֡��
	static float  currentTime = 0.0f;//��ǰʱ��
	static float  lastTime = 0.0f;//����ʱ��

	frameCount++;//ÿ����һ��Get_FPS()������֡������1
	currentTime = timeGetTime() * 0.001f;//��ȡϵͳʱ�䣬����timeGetTime�������ص����Ժ���Ϊ��λ��ϵͳʱ�䣬������Ҫ����0.001���õ���λΪ���ʱ��

	//�����ǰʱ���ȥ����ʱ�������1���ӣ��ͽ���һ��FPS�ļ���ͳ���ʱ��ĸ��£�����֡��ֵ����
	if (currentTime - lastTime > 1.0f) //��ʱ�������1����
	{
		fps = (float)frameCount / (currentTime - lastTime);//������1���ӵ�FPSֵ
		lastTime = currentTime; //����ǰʱ��currentTime��������ʱ��lastTime����Ϊ��һ��Ļ�׼ʱ��
		frameCount = 0;//������֡��frameCountֵ����
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
	//	//m_pDevice->SetIndices(m_pIB);//������������
	//	//m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 17, 0, 16);//��������������϶��㻺�����ͼ��
	//	m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	//	m_pDevice->EndScene();
	//}
	//m_pDevice->Present(0, 0, 0, 0);


	//--------------------------------------------------------------------------------------
	// ��Direct3D��Ⱦ�岽��֮һ������������
	//--------------------------------------------------------------------------------------
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//����һ�����Σ����ڻ�ȡ�����ھ���
	RECT formatRect;
	GetClientRect((HWND)winId(), &formatRect);

	//--------------------------------------------------------------------------------------
	// ��Direct3D��Ⱦ�岽��֮��������ʼ����
	//--------------------------------------------------------------------------------------
	m_pDevice->BeginScene();                     // ��ʼ����
	/*Frame();*/
	//--------------------------------------------------------------------------------------
	// ��Direct3D��Ⱦ�岽��֮��������ʽ����
	//--------------------------------------------------------------------------------------
		// ������Ⱦ״̬
	//m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);//�������ʡ�ԣ���Ϊ�������ɫģʽΪD3DĬ�ϵ���ɫģʽ
	
	//-------------------------------------------------------------------
	// �����㻺�桢���������ͼ�Ĳ���֮�ġ�������ͼ��
	//--------------------------------------------------------------------
	m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(SCustomVertex));//�Ѱ����ļ�������Ϣ�Ķ��㻺�����Ⱦ��ˮ�������
	m_pDevice->SetFVF(D3DFVF_SCUSTOMVERTEX);//ָ������ʹ�õ������ʽ�ĺ�����
	if (NumIndices>0)
	{
		m_pDevice->SetIndices(m_pIB);//������������
		m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVertices, 0, NumIndices);//��������������϶��㻺�����ͼ��
	}
	else
	{
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);//�ӵ�0���㿪ʼ��D3DPT_TRIANGLELIST ģʽ��Ⱦ1��������
	}
	

	//--------------------------------------------------------------------------------------
	// ��Direct3D��Ⱦ�岽��֮�ġ�����������
	//--------------------------------------------------------------------------------------
	m_pDevice->EndScene();                       // ��������
	//--------------------------------------------------------------------------------------
	// ��Direct3D��Ⱦ�岽��֮�塿����ʾ��ת
	//--------------------------------------------------------------------------------------
	m_pDevice->Present(NULL, NULL, NULL, NULL);  // ��ת����ʾ
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
//Ȼ��ͨ��Qt���ʦ����һ�����ڿ�GQtDX9Dialog����GDXWidget��һ��ʵ������ô��ڼ��ɡ�