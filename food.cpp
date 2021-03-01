#include "pch.h"
#include "food.h"
#include "game.h"
#include <stdlib.h>
#include <ctime>
food::food(int a , int b , char pic )
{
	x = a;
	y = b;
	symbol = pic;
}
void food::createPos(vector<unit> vec)//随机数生成食物位置（不能出现在蛇身上）
{
		vector<unit>::iterator i;
		srand(time(0));//使每次运行产生的随机数不一样
		//保证食物落在游戏框内，并且不能在框线上，也不能挨着框线
		x = rand() % (game::KWIDTH - 2)+ game::KLEFT + 1;//随机数生成x轴的值，保证game::KLEFT + 1< x < game::KWIDTH - 2即6<x<68
		y = rand() % (game::KHEIGHT - 2) + game::KUP + 3 ;//随机数生成y轴的值，保证game::KUP + 3 < y < game::KHEIGHT - 2即5<y<18
    	for (i = vec.begin(); i != vec.end(); i++)
		{
			while (x == i->x&&y == i->y)//保证食物不落在蛇身上
			{
				x = game::KLEFT + 1 + rand() % (game::KWIDTH - 2);//随机数重新生成x轴的值，保证x在游戏框内
				y = game::KUP + 3 + rand() % (game::KHEIGHT - 2);//随机数重新生成y轴的值，保证y在游戏框内
				//x = rand() % (CWIDTH - 2) + CLEFT + 1;//随机数重新生成x轴的值，保证x在游戏框内
				//y = rand() % (CHEIGHT - 2) + CUP + 3;//随机数重新生成y轴的值，保证y在游戏框内
			}
		}
}

food::~food()
{
}
