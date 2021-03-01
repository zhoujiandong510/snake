#pragma once

#include "food.h"
#include "snake.h"
#include "conio.h"    //kbhit()�ж��Ƿ�������
#include <windows.h> //Sleep����
//#define VK_ESCAPE 32 //�ո��
//#define VK_ESC 27 //�˳���
class game
{
public:
	game();
	virtual ~game();
	void run();//��Ϸ����
	bool checkFailed();//ʧ�ܼ�⣨�����Ϸ�Ƿ�ʧ�ܣ�
	bool checkLevel();//�ȼ���⣨�����Ϸ�Ƿ���أ�
	void drawGameArea();//������Ϸ��ͼ����ϷUI�� 
	void drawGameInfo();//������Ϸ��Ϣ����Ϣ���ã�
	void changeInfo();//������Ϸ��Ϣ

public:
	static const int KLEFT;//��߾�
	static const int KUP;//���±߾�
	static const int KWIDTH;//����
	static const int KHEIGHT;//�߶�
	static const int KSCORE_OFFSET;//������ʾ������ߵľ���
	static const int KLEVEL_OFFSET;//������ʾ������ߵľ���

public:
    food *pfood;//ʳ��
	snake *psnake;//��
	int iScore;//����
	int iLevel;//�ȼ�
};

