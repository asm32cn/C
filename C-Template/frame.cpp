#include <windows.h>

LRESULT CALLBACK WindowFunc(HWND,UINT,WPARAM,LPARAM);

char szWinName[]="MyWin";

int WINAPI WinMain(HINSTANCE hThisInst,HINSTANCE hPrevInst,
				   LPSTR lpszArgs,int nWinMode){
	HWND hwnd;
	MSG msg;
	WNDCLASS wc1;

	//定义一个窗口类
	wc1.hInstance=hThisInst;        //改实例的句柄
	wc1.lpszClassName=szWinName;    //窗口类的名称
	wc1.lpfnWndProc=WindowFunc;     //窗口名称
	wc1.style=0;                    //默认模式

	wc1.hIcon=LoadIcon(NULL,IDI_APPLICATION);   //图标模式
	wc1.hCursor=LoadCursor(NULL,IDC_ARROW);     //光标模式
	wc1.lpszMenuName=NULL;                      //没有菜单

	wc1.cbClsExtra=0;
	wc1.cbWndExtra=0;

	//设置窗口背景为白色
	wc1.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);

	//登记窗口类
	if(!RegisterClass(&wc1)) return 0;

	//创建一个窗口
	hwnd=CreateWindow(
		szWinName,              //窗口类名
		"Windows 98 Framework", //标题
		WS_OVERLAPPEDWINDOW,    //窗口模式
		CW_USEDEFAULT,          // X 坐标
		CW_USEDEFAULT,          // Y 坐标
		CW_USEDEFAULT,          //宽度
		CW_USEDEFAULT,          //高度
		HWND_DESKTOP,           //没有父窗口
		NULL,                   //没有菜单
		hThisInst,              //该程序实例的句柄
		NULL
		);

	//显示窗口
	ShowWindow(hwnd,nWinMode);
	UpdateWindow(hwnd);

	//创建消息循环
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg); //允许使用键盘
		DispatchMessage(&msg);  //返回窗口控制
	}
	return msg.wParam;
}

//该函数被 Windows 98 调用，可以从消息队列中传递消息
LRESULT CALLBACK WindowFunc(HWND hwnd,UINT message,
							WPARAM wParam,LPARAM lParam){
	switch(message){
	case WM_DESTROY: //终止进程
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd,
			message,wParam,lParam);
	}
	return 0;
}