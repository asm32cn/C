
#include <windows.h>
#include <stdio.h>

void PA_DoClick(int x, int y){
	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
	Sleep(50);
}

void main(){
	for(int i = 0; i < 70; i++){
		PA_DoClick(1328, 777);
		printf("%d / %d ", i, 10);
		for(int j = 0; j < 12; j++){
			Sleep(1000);
			printf(".");
		}
		printf("\n");
	}
}
