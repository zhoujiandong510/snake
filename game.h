#pragma once

#include "food.h"
#include "snake.h"
#include "conio.h"    //kbhit()判断是否有输入
#include <windows.h> //Sleep函数
//#define VK_ESCAPE 32 //空格键
//#define VK_ESC 27 //退出键
class game
{
public:
	game();
	virtual ~game();
	void run();//游戏运行
	bool checkFailed();//失败检测（检查游戏是否失败）
	bool checkLevel();//等级检测（检查游戏是否过关）
	void drawGameArea();//绘制游戏框图（游戏UI） 
	void drawGameInfo();//绘制游戏信息（信息设置）
	void changeInfo();//更改游戏信息

public:
	static const int KLEFT;//左边距
	static const int KUP;//上下边距
	static const int KWIDTH;//长度
	static const int KHEIGHT;//高度
	static const int KSCORE_OFFSET;//分数显示与最左边的距离
	static const int KLEVEL_OFFSET;//级别显示与最左边的距离

public:
    food *pfood;//食物
	snake *psnake;//蛇
	int iScore;//分数
	int iLevel;//等级
};

