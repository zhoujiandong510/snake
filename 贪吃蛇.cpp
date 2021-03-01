#include "pch.h"
#include "unit.h"     //单元类
#include "food.h"     //食物类
#include "snake.h"    //蛇类
#include "game.h"     //游戏总控制类
#include <iostream>
#include<windows.h>
using namespace std;
int main()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态*/
	game mygame;
	mygame.run();	
	system("PAUSE");//程序结束后停留一下,显示按任意键继续
	getchar();
	return 0;
}
