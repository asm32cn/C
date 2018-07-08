// MessageBoxDemo1.cpp
#include <windows.h>     

int APIENTRY WinMain(HINSTANCE hInstance, //当前实例句柄     
		HINSTANCE hPrevInstance,          //前一个实例句柄，Win32下为NULL     
		LPSTR     lpCmdLine,              //命令行参数字符     
		int       nCmdShow)               //窗口的显示方式     
{
    MessageBox(NULL,"欧阳软件学习网欢迎您！","欢迎你",MB_OK | MB_ICONINFORMATION); //通用对话框     
    return 0;  //函数返回值     
}
