#include "pch.h"
#include "game.h"
#include "unit.h"

const int game::KLEFT = 5;//��߾�
const int game::KUP = 2;//���±߾�
const int game::KWIDTH = 70;//����
const int game::KHEIGHT = 20;//�߶�
const int game::KSCORE_OFFSET = 50;//������ʾ������ߵľ���
const int game::KLEVEL_OFFSET = 65;//������ʾ������ߵľ���

game::game()
{
	this->pfood = new food();//ʳ��
	this->psnake = new snake();//��
	this->iScore = 0; 
	this->iLevel = 1;
	drawGameArea();//������ϷUI
	drawGameInfo();//������Ϸ��Ϣ
}
game::~game()
{
	delete psnake;
	delete pfood;
	psnake = NULL;
	pfood = NULL;
}
void game::run()//��Ϸ����
{
	pfood->createPos(psnake->s_vecBody);
	pfood->show();
	psnake->showSnake();
	int key=0;
	while (1)
	{
		if (_kbhit())//�ж��Ƿ�������
		{
			key = _getch();//�����
			//if (key == VK_ESCAPE)
			if (key == 32)//�ո��
				break;
			else
			{
				Sleep(1000);//��ͣ
			}
		}
	}//��ʼ��Ϸ��ͣ
	while (1) 
	{
		psnake->move();//���ƶ�
		if (_kbhit())//�ж��Ƿ�������
		{
			key = _getch();//�����
			//if (key == VK_ESCAPE)
			if (key == 32)//�ո��
				while (1)
				{
					Sleep(1000);//��ͣ
					if (_kbhit())
					{
						key = _getch();
						if (key == 32)//�ٴ�����ո��
							break;
					}
				}
			psnake->changeDirection(key);//�ı䷽��
		}	
		if (psnake->eatFood(pfood))//�Ե�ʳ��
		{
			iScore = iScore+10;//��һ��ʳ���10��
			if (checkLevel())//����Ƿ����
			{
				//system("cls");//����
				//unit::gotoxy(35, 10);//��궨λ����Ļ����
				//cout << "�ǳ���Ŷ����ϲͨ�أ�����" << endl;
				//break;
				int flag;
				//����Ŀ�������ַ�����Ĭ�ϡ�ʹ��Unicode�ַ�������Ϊ��ʹ�ö��ֽ��ַ�����
				//ʹMessageBox()�����в���2�Ͳ���3�ܱ���ͨ��
				flag = MessageBox(NULL, "�Ƿ�����һ�Σ�", "��ϲ����ͨ���ˣ�����", MB_YESNO);//�����Ի���
				if (flag == 7)//ѡ��񣬽�������
				{
					system("cls");//����
					break;//�˳�����
				}
				else if (flag == 6)//ѡ���ǣ���������
				{
					system("cls");//����
					game mygame;
					mygame.run();
				}
			}
			changeInfo();//�޸���Ϸ��Ϣ
			pfood->createPos(psnake->s_vecBody);//����ʳ��λ��
			pfood->show();//�ٴγ���ʳ��
		}
		if (checkFailed())//����Ƿ�ʧ��
		{
			//system("cls");//����
			//unit::gotoxy(35, 10);//��궨λ����Ļ����
			//cout << "�����ˣ���Ϸ����";
			//break;
			int flag;
			flag = MessageBox(NULL, "����һ�Σ�", "�����ˣ�����", MB_YESNO);//�����Ի���
			if (flag == 7)//ѡ��񣬽�������
			{
				system("cls");//����
				break;
			}
			else if (flag == 6)//ѡ���ǣ���������
			{
				system("cls");//����
				game mygame;
				mygame.run();
			}
		}
	}
}
bool game::checkFailed()//ʧ�ܼ��
{
	for (int i=1; i < psnake->s_length; i++)
	{
		//��ͷ�����������Բ���
		if ((psnake->s_headx == psnake->s_vecBody[i].x) && (psnake->s_heady == psnake->s_vecBody[i].y))
			return true;
	}
	if ((psnake->s_vecBody[0].x <= game::KLEFT) || (psnake->s_vecBody[0].x >= (game::KLEFT + game::KWIDTH-1)))
	{
		//�����������ң�
		return true;
	}
	if ((psnake->s_heady <= game::KUP +2)|| (psnake->s_heady >= (game::KUP + game::KHEIGHT+1)))
	{
		//�����������£�
		return true;
	}
	return false;
}
bool game::checkLevel()//�ȼ����
{
	switch (iLevel)
	{
	case 1:  //1��ʱ���ﵽ30�ֿ�����
		if (iScore % 30 == 0 && iScore != 0)
		{
			iLevel++;//�ȼ���1
			iScore = 0;//������0
			psnake->s_speed = psnake->s_speed + 100;//����
		}
		return false;
	case 2: //2��ʱ���ﵽ50�ֿ�����
		if (iScore % 50 == 0 && iScore != 0)
		{
			iLevel++;//�ȼ���1
			iScore = 0;//������0
			psnake->s_speed = psnake->s_speed + 200;//����
		}
		 return false;
	case 3: //3��ʱ���ﵽ100�ֿ�ͨ��
		if (iScore % 100 == 0 && iScore != 0)
		{
			return true;//ͨ��
		}
		return false;
	}
}
void game::drawGameArea()//������Ϸ��ͼ 
{
	unit::gotoxy(KLEFT, KUP);
	for (int j = 0; j < KWIDTH; j++)//�����ϱ߿�
		cout << "-";
	for (int i = 0; i < KHEIGHT; i++)
	{
		unit::gotoxy(KLEFT, KUP + 1 + i);//������߿�
		cout << "|";
		unit::gotoxy(KLEFT + KWIDTH - 1, KUP + 1 + i);//�����ұ߿�
		cout << "|";
	}
	unit::gotoxy(KLEFT, KUP + KHEIGHT + 1);//�����±߿�
	for (int k = 0; k < KWIDTH; k++)
		cout << "-";
	unit::gotoxy(KLEFT + 1, KUP + 2);//���Ʊ����±߿�
	for (int i = 0; i < KWIDTH - 2; i++)
		cout << "-";
}
void game::drawGameInfo()//������Ϸ��Ϣ
{
	unit::gotoxy(KLEFT + 1, KUP + 1);
	cout << "��Ϸ���ƣ�̰����";
	unit::gotoxy(KLEFT + 20, KUP + 1);
	cout << "��д�ߣ�zjd";
	unit::gotoxy(KLEFT + 40, KUP + 1);
	cout << "�÷�";
	unit::gotoxy(KLEFT + KSCORE_OFFSET, KUP + 1);
	cout << iScore;
	unit::gotoxy(KLEFT + 55, KUP + 1);
	cout << "��ǰ�ؿ�";
	unit::gotoxy(KLEFT + KLEVEL_OFFSET, KUP + 1);
	cout << iLevel;
	/*unit::gotoxy(KLEFT, KUP + KHEIGHT + 2);
	cout << "��Ϸ���� ͨ�����������̰�������������ƶ�;�ո����ͣ" << endl;
	unit::gotoxy(KLEFT , KUP + KHEIGHT + 3);
	cout << "�����أ���һ��30��ͨ��" << endl;
	unit::gotoxy(KLEFT , KUP + KHEIGHT + 4);
	cout << "        �ڶ���50��ͨ��" << endl;
	unit::gotoxy(KLEFT , KUP + KHEIGHT + 5);
	cout << "        ������100��ͨ��" << endl;*/

}
void game::changeInfo()//������Ϸ��Ϣ
{
	unit::gotoxy(KLEFT + KSCORE_OFFSET, KUP + 1);
	cout << "  ";
	unit::gotoxy(KLEFT + KSCORE_OFFSET, KUP + 1);
	cout << iScore;
	unit::gotoxy(KLEFT + KLEVEL_OFFSET, KUP + 1);
	cout << "  ";
	unit::gotoxy(KLEFT + KLEVEL_OFFSET, KUP + 1);
	cout << iLevel;
}

