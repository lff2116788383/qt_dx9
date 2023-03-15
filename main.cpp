#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "GLWidget.h"
#include "widget.h"
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWindow w; /*dx9 dx11 opengl 渲染旋转的立方体*/
	//GLWidget w;/*opengl渲染三角形*/
	//Widget w;	/*opengl渲染立方体模型*/
	w.show();
	return a.exec();
}

/*
1.附加包含目录
C:\Users\LewisLiu\source\repos\qt_dx9\SDK\DX9\Include;.\;C:\Users\LewisLiu\source\repos\qt_dx9\Common\Assimp;%(AdditionalIncludeDirectories)
2.附加库目录
C:\Users\LewisLiu\source\repos\qt_dx9\SDK\DX9\Lib\x64;%(AdditionalLibraryDirectories)
3.库依赖项
OpenGL32.lib;glu32.lib;Common\Assimp\assimp-vc140-mt.lib;%(AdditionalDependencies)
*/