#include <iostream>
#include <Windows.h>
#include "BadMouse.h"
const string version = "0.015";
using namespace std;
void e()
{
	bool f = 0;
	SetWinSize(20, 5);
	print("按Scroll Lock开始…", 0, 2);
	while (1)
	{

		if (eventKey(VK_SCROLL))
		{
			f = !f;
			clears();
			//HideCursor();
			if (f) print("状态：■", 5, 2);
			else print("状态：□", 5, 2);
			while (eventKey(VK_SCROLL));
		}
		if (f) Click(LeftClick);
		Sleep(50);
	}
}

int main()
{
	WinExec("Check.exe",SW_SHOW);
	SetWinSize(31, 10);
	SetTitle("Bad Mouse");
	HideCursor();
	print("坏掉的鼠标", YELLOW, 10, 2);
	print(" by 黄靖钊", 21, 9);
	print("v", 25, 8); print(version);
	print("任意键继续……", GREEN, 0, 9);
	{int a = _getch(); }

	SetWinSize(20, 10);

	print("功能列表", 6, 1);

	print("鼠标连点", 5, 5);
	SetColor(0xF * 0x10 + 0);
	SetPos(5, 5);
	sleep_cout("鼠标连点", 10);


	//print("H.帮助与介绍", 0, 9);
	//print("S.设置", 45,9);
	eventLoop({ '1' }, { e });

	while (1) {                      			//循环检测


		if (eventKey(VK_LBUTTON)) {  			//鼠标左键按下
			printf("key down!\n");
			while (eventKey(VK_LBUTTON));
			return 0;
		}
		Sleep(20);                  			//等待20毫秒，减少CPU占用
	}

}
