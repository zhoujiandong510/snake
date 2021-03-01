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
	int s_length;//����
	int s_headx;//��ͷ��x����
	int s_heady;//��ͷ��y����
	int s_speed;//�ߵ��ٶ�
	int s_pic;//�ߵķ���
	Directions s_enumCurrentDirection;//ǰ������
	vector<unit> s_vecBody;//����
public:
	snake(int x=35,int y=10,int leng=5, int speed=1300, Directions direction=RIGHT, int pic='o');
	void move();
	bool eatFood(food *pfood);//�߳�ʳ��
	void showSnake();//�ߵ���ʾ
	void eraseSnake();//�ߵĲ���
	void growUp();//�ߵĳɳ�
	void changeDirection(int kValue);//�ı䷽��
	virtual ~snake();
};

