#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "GLWidget.h"
#include "widget.h"
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWindow w; /*dx9 dx11 opengl ��Ⱦ��ת��������*/
	//GLWidget w;/*opengl��Ⱦ������*/
	//Widget w;	/*opengl��Ⱦ������ģ��*/
	w.show();
	return a.exec();
}

/*
1.���Ӱ���Ŀ¼
C:\Users\LewisLiu\source\repos\qt_dx9\SDK\DX9\Include;.\;C:\Users\LewisLiu\source\repos\qt_dx9\Common\Assimp;%(AdditionalIncludeDirectories)
2.���ӿ�Ŀ¼
C:\Users\LewisLiu\source\repos\qt_dx9\SDK\DX9\Lib\x64;%(AdditionalLibraryDirectories)
3.��������
OpenGL32.lib;glu32.lib;Common\Assimp\assimp-vc140-mt.lib;%(AdditionalDependencies)
*/