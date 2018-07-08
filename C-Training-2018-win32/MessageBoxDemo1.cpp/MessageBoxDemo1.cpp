// MessageBoxDemo1.cpp
#include "windows.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow){
	MessageBox(NULL, TEXT("你好，欢迎来到VC世界"), TEXT("欢迎"), MB_ICONINFORMATION);
	return 0;
}
