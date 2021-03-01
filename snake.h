#pragma once
#include "unit.h"
#include "food.h"
#include <vector>
#define SLEEP  1500

typedef enum {
	UP,DOWN,LEFT,RIGHT
}Directions;
class snake
{
public:
	int s_length;//长度
	int s_headx;//蛇头的x坐标
	int s_heady;//蛇头的y坐标
	int s_speed;//蛇的速度
	int s_pic;//蛇的符号
	Directions s_enumCurrentDirection;//前进方向
	vector<unit> s_vecBody;//蛇身
public:
	snake(int x=35,int y=10,int leng=5, int speed=1300, Directions direction=RIGHT, int pic='o');
	void move();
	bool eatFood(food *pfood);//蛇吃食物
	void showSnake();//蛇的显示
	void eraseSnake();//蛇的擦除
	void growUp();//蛇的成长
	void changeDirection(int kValue);//改变方向
	virtual ~snake();
};

