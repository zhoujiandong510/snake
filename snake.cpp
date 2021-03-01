#include "pch.h"
#include "snake.h"
#include <vector>
#include<windows.h> 
snake::snake(int x , int y , int leng, int speed, Directions direction, int pic )
{
	s_length=leng;//����
	s_headx =x;//��ͷ��x����
	s_heady=y;//��ͷ��y����
	s_speed=speed;//�ߵ��ٶ�
	s_enumCurrentDirection = direction;//ǰ������
	s_pic=pic;//�ߵķ���
	int tempX, tempY;
	for (int i = 0; i < s_length; i++)
	{
		switch (s_enumCurrentDirection)//�ж��н�����
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
void snake::move()//�ߵ��ƶ�
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hout, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//��ɫ����ɫ��ӣ���ɫ
//	while(true)  //һֱ�ƶ�
//	{
		snake::eraseSnake();//��������
		//switch (s_enumCurrentDirection)//�ж��н�����
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
		{//�����һ�������ǰһ���������
			s_vecBody[i + 1].x = s_vecBody[i].x;
			s_vecBody[i + 1].y = s_vecBody[i].y;
		}
		switch (s_enumCurrentDirection)
		{
		case UP:
			s_vecBody[0].y--; //��ͷ�����ƶ�һ��λ��
			s_headx = s_vecBody[0].x;
			s_heady = s_vecBody[0].y;
			break;
		case DOWN:
			s_vecBody[0].y++;//��ͷ�����ƶ�һ��λ��
			s_headx = s_vecBody[0].x;
			s_heady = s_vecBody[0].y;
			break;
		case LEFT:
			s_vecBody[0].x--;//��ͷ�����ƶ�һ��λ��
			s_headx = s_vecBody[0].x;
			s_heady = s_vecBody[0].y;
			break;
		case RIGHT:
			s_vecBody[0].x++;//��ͷ�����ƶ�һ��λ��
			s_headx = s_vecBody[0].x;
			s_heady = s_vecBody[0].y;
			break;
		}
		snake::showSnake();//��ʾ����
		Sleep(SLEEP-s_speed);//ͣ�٣���Ĭ��ֵ-���ٶ���ȷ��ͣ��ʱ�䣬�ٶ�ֵԽ��ͣ��ʱ��ԽС����ǰ��Խ��
//	}
}

bool snake::eatFood(food *pfood)//�߳�ʳ��
{
	//if (s_headx== pfood->x&&s_heady == pfood->y)//��ͷ����ʳ��
	if(s_vecBody[0].x == pfood->x && s_vecBody[0].y == pfood->y)//��ͷ����ʳ��
	{
		pfood->erase();//����ʳ��
		growUp();//�߳Ե�ʳ�ﳤ��
		return 1;//����true����ʾ�Ե�ʳ��
	}
	return 0;
}
void snake::showSnake()//�ߵ���ʾ
{
	for (int i = 0; i < s_length; i++)
	{
		s_vecBody[i].show();
	}
}
void snake::eraseSnake()//�ߵĲ���
{
	for (int i = 0; i < s_length; i++)
	{
		s_vecBody[i].erase();
	}
}

void snake::growUp()//�ߵĳɳ�
{
	//int tempX, tempY;
	//switch (s_enumCurrentDirection)//�ж��н�����
	//{
	//case UP:
	//	tempX = s_vecBody.begin()->x;//�½ڵ��x���������ͷx����
	//	tempY = s_vecBody.begin()->y + s_length;//�½ڵ��y����=��ͷy����+�߳����������һ��λ��)
	//	break;
	//case DOWN:
	//	tempX = s_vecBody.begin()->x;//�½ڵ��x���������ͷx����
	//	tempY = s_vecBody.begin()->y - s_length;//�½ڵ��y����=��ͷy����-�߳����������һ��λ��)
	//	break;
	//case LEFT:
	//	tempX = s_vecBody.begin()->x + s_length;//�½ڵ��x����=��ͷx����+�߳����������һ��λ��)
	//	tempY = s_vecBody.begin()->y;//�½ڵ��y���������ͷy����
	//	break;
	//case RIGHT:
	//	tempX = s_vecBody.begin()->x - s_length;//�½ڵ��x����=��ͷx����-�߳����������һ��λ��)
	//	tempY = s_vecBody.begin()->y;//�½ڵ��y���������ͷy����
	//	break;
	//}
	//unit ut(tempX, tempY, s_pic);
	//s_vecBody.push_back(ut);
	//s_length = s_length + 1;
	unit unit1(0, 0, s_pic);//����һ��������
	s_vecBody.push_back(unit1);//�����ӵ��������һ�����
	s_length++;//������������ԣ�ֻ��Ҫ��������+1�������Զ����������������
}
void snake::changeDirection(int kValue)
{
	switch (kValue)//�ж������ֵ
	{
	case 72://�����ƶ���ǰ�᣺��ǰ״̬�������ϻ�����
		if((s_enumCurrentDirection != UP)&& (s_enumCurrentDirection != DOWN))
		s_enumCurrentDirection = UP;
		break;
	case 80://�����ƶ���ǰ�᣺��ǰ״̬�������ϻ�����
		if((s_enumCurrentDirection != DOWN)&& (s_enumCurrentDirection != UP))
		s_enumCurrentDirection = DOWN;
		break;
	case 75://�����ƶ���ǰ�᣺��ǰ״̬�������һ�����
		if ((s_enumCurrentDirection != LEFT)&& (s_enumCurrentDirection != RIGHT))
		s_enumCurrentDirection = LEFT;
		break;
	case 77://�����ƶ���ǰ�᣺��ǰ״̬�������һ�����
		if ((s_enumCurrentDirection != RIGHT) && (s_enumCurrentDirection != LEFT))
			s_enumCurrentDirection = RIGHT;//s_enumCurrentdirection=RIGHT
		break;
	}
}
snake::~snake()
{
}


