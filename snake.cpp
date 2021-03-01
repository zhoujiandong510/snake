#include "pch.h"
#include "snake.h"
#include <vector>
#include<windows.h> 
snake::snake(int x , int y , int leng, int speed, Directions direction, int pic )
{
	s_length=leng;//长度
	s_headx =x;//蛇头的x坐标
	s_heady=y;//蛇头的y坐标
	s_speed=speed;//蛇的速度
	s_enumCurrentDirection = direction;//前进方向
	s_pic=pic;//蛇的符号
	int tempX, tempY;
	for (int i = 0; i < s_length; i++)
	{
		switch (s_enumCurrentDirection)//判断行进方向
		{
		case UP:
			tempX = s_headx;
			tempY = s_heady + i;
			break;
		case DOWN:
			tempX = s_headx;
			tempY = s_heady - i;
			break;
		case LEFT:
			tempX = s_headx + i;
			tempY = s_heady;
			break;
		case RIGHT:
			tempX = s_headx - i;
			tempY = s_heady;
			break;
		}
		unit ut(tempX, tempY, pic);
		s_vecBody.push_back(ut);
	}
}
void snake::move()//蛇的移动
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hout, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//红色和蓝色相加，粉色
//	while(true)  //一直移动
//	{
		snake::eraseSnake();//擦除蛇身
		//switch (s_enumCurrentDirection)//判断行进方向
		//{
		//case UP:
		//	for (int i = 0; i < s_length; i++)
		//	{
		//		s_vecBody[i].y = s_vecBody[i].y - 1;
		//	}
		//	break;
		//case DOWN:
		//	for (int i = 0; i < s_length; i++)
		//	{
		//		s_vecBody[i].y = s_vecBody[i].y + 1;
		//	}
		//	break;
		//case LEFT:
		//	for (int i = 0; i < s_length; i++)
		//	{
		//		s_vecBody[i].x = s_vecBody[i].x - 1;
		//	}
		//	break;
		//case RIGHT:
		//	for (int i = 0; i < s_length; i++)
		//	{
		//		s_vecBody[i].x = s_vecBody[i].x + 1;
		//	}
		//	break;
		//}

		for (int i = s_length - 2; i >= 0; i--) 
		{//蛇身后一个点等于前一个点的坐标
			s_vecBody[i + 1].x = s_vecBody[i].x;
			s_vecBody[i + 1].y = s_vecBody[i].y;
		}
		switch (s_enumCurrentDirection)
		{
		case UP:
			s_vecBody[0].y--; //蛇头向上移动一个位置
			s_headx = s_vecBody[0].x;
			s_heady = s_vecBody[0].y;
			break;
		case DOWN:
			s_vecBody[0].y++;//蛇头向下移动一个位置
			s_headx = s_vecBody[0].x;
			s_heady = s_vecBody[0].y;
			break;
		case LEFT:
			s_vecBody[0].x--;//蛇头向左移动一个位置
			s_headx = s_vecBody[0].x;
			s_heady = s_vecBody[0].y;
			break;
		case RIGHT:
			s_vecBody[0].x++;//蛇头向右移动一个位置
			s_headx = s_vecBody[0].x;
			s_heady = s_vecBody[0].y;
			break;
		}
		snake::showSnake();//显示蛇身
		Sleep(SLEEP-s_speed);//停顿，以默认值-蛇速度来确定停顿时间，速度值越大，停顿时间越小，蛇前进越快
//	}
}

bool snake::eatFood(food *pfood)//蛇吃食物
{
	//if (s_headx== pfood->x&&s_heady == pfood->y)//蛇头碰到食物
	if(s_vecBody[0].x == pfood->x && s_vecBody[0].y == pfood->y)//蛇头碰到食物
	{
		pfood->erase();//擦掉食物
		growUp();//蛇吃到食物长大
		return 1;//返回true，表示吃到食物
	}
	return 0;
}
void snake::showSnake()//蛇的显示
{
	for (int i = 0; i < s_length; i++)
	{
		s_vecBody[i].show();
	}
}
void snake::eraseSnake()//蛇的擦除
{
	for (int i = 0; i < s_length; i++)
	{
		s_vecBody[i].erase();
	}
}

void snake::growUp()//蛇的成长
{
	//int tempX, tempY;
	//switch (s_enumCurrentDirection)//判断行进方向
	//{
	//case UP:
	//	tempX = s_vecBody.begin()->x;//新节点的x坐标等于蛇头x坐标
	//	tempY = s_vecBody.begin()->y + s_length;//新节点的y坐标=蛇头y坐标+蛇长（即蛇身后一个位置)
	//	break;
	//case DOWN:
	//	tempX = s_vecBody.begin()->x;//新节点的x坐标等于蛇头x坐标
	//	tempY = s_vecBody.begin()->y - s_length;//新节点的y坐标=蛇头y坐标-蛇长（即蛇身后一个位置)
	//	break;
	//case LEFT:
	//	tempX = s_vecBody.begin()->x + s_length;//新节点的x坐标=蛇头x坐标+蛇长（即蛇身后一个位置)
	//	tempY = s_vecBody.begin()->y;//新节点的y坐标等于蛇头y坐标
	//	break;
	//case RIGHT:
	//	tempX = s_vecBody.begin()->x - s_length;//新节点的x坐标=蛇头x坐标-蛇长（即蛇身后一个位置)
	//	tempY = s_vecBody.begin()->y;//新节点的y坐标等于蛇头y坐标
	//	break;
	//}
	//unit ut(tempX, tempY, s_pic);
	//s_vecBody.push_back(ut);
	//s_length = s_length + 1;
	unit unit1(0, 0, s_pic);//创建一个蛇身结点
	s_vecBody.push_back(unit1);//将结点加到蛇身最后一个结点
	s_length++;//根据蛇身的特性，只需要将蛇身长度+1，就能自动调整新增结点坐标
}
void snake::changeDirection(int kValue)
{
	switch (kValue)//判断输入键值
	{
	case 72://向上移动，前提：当前状态不是向上或向下
		if((s_enumCurrentDirection != UP)&& (s_enumCurrentDirection != DOWN))
		s_enumCurrentDirection = UP;
		break;
	case 80://向下移动，前提：当前状态不是向上或向下
		if((s_enumCurrentDirection != DOWN)&& (s_enumCurrentDirection != UP))
		s_enumCurrentDirection = DOWN;
		break;
	case 75://向左移动，前提：当前状态不是向右或向左
		if ((s_enumCurrentDirection != LEFT)&& (s_enumCurrentDirection != RIGHT))
		s_enumCurrentDirection = LEFT;
		break;
	case 77://向右移动，前提：当前状态不是向右或向左
		if ((s_enumCurrentDirection != RIGHT) && (s_enumCurrentDirection != LEFT))
			s_enumCurrentDirection = RIGHT;//s_enumCurrentdirection=RIGHT
		break;
	}
}
snake::~snake()
{
}


