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
void food::createPos(vector<unit> vec)//���������ʳ��λ�ã����ܳ����������ϣ�
{
		vector<unit>::iterator i;
		srand(time(0));//ʹÿ�����в������������һ��
		//��֤ʳ��������Ϸ���ڣ����Ҳ����ڿ����ϣ�Ҳ���ܰ��ſ���
		x = rand() % (game::KWIDTH - 2)+ game::KLEFT + 1;//���������x���ֵ����֤game::KLEFT + 1< x < game::KWIDTH - 2��6<x<68
		y = rand() % (game::KHEIGHT - 2) + game::KUP + 3 ;//���������y���ֵ����֤game::KUP + 3 < y < game::KHEIGHT - 2��5<y<18
    	for (i = vec.begin(); i != vec.end(); i++)
		{
			while (x == i->x&&y == i->y)//��֤ʳ�ﲻ����������
			{
				x = game::KLEFT + 1 + rand() % (game::KWIDTH - 2);//�������������x���ֵ����֤x����Ϸ����
				y = game::KUP + 3 + rand() % (game::KHEIGHT - 2);//�������������y���ֵ����֤y����Ϸ����
				//x = rand() % (CWIDTH - 2) + CLEFT + 1;//�������������x���ֵ����֤x����Ϸ����
				//y = rand() % (CHEIGHT - 2) + CUP + 3;//�������������y���ֵ����֤y����Ϸ����
			}
		}
}

food::~food()
{
}
