#include "pch.h"
#include "game.h"
#include "unit.h"

const int game::KLEFT = 5;//左边距
const int game::KUP = 2;//上下边距
const int game::KWIDTH = 70;//长度
const int game::KHEIGHT = 20;//高度
const int game::KSCORE_OFFSET = 50;//分数显示与最左边的距离
const int game::KLEVEL_OFFSET = 65;//级别显示与最左边的距离

game::game()
{
	this->pfood = new food();//食物
	this->psnake = new snake();//蛇
	this->iScore = 0; 
	this->iLevel = 1;
	drawGameArea();//绘制游戏UI
	drawGameInfo();//绘制游戏信息
}
game::~game()
{
	delete psnake;
	delete pfood;
	psnake = NULL;
	pfood = NULL;
}
void game::run()//游戏运行
{
	pfood->createPos(psnake->s_vecBody);
	pfood->show();
	psnake->showSnake();
	int key=0;
	while (1)
	{
		if (_kbhit())//判断是否有输入
		{
			key = _getch();//输入键
			//if (key == VK_ESCAPE)
			if (key == 32)//空格键
				break;
			else
			{
				Sleep(1000);//暂停
			}
		}
	}//开始游戏暂停
	while (1) 
	{
		psnake->move();//蛇移动
		if (_kbhit())//判断是否有输入
		{
			key = _getch();//输入键
			//if (key == VK_ESCAPE)
			if (key == 32)//空格键
				while (1)
				{
					Sleep(1000);//暂停
					if (_kbhit())
					{
						key = _getch();
						if (key == 32)//再次输入空格键
							break;
					}
				}
			psnake->changeDirection(key);//改变方向
		}	
		if (psnake->eatFood(pfood))//吃到食物
		{
			iScore = iScore+10;//吃一个食物加10分
			if (checkLevel())//检查是否过关
			{
				//system("cls");//清屏
				//unit::gotoxy(35, 10);//光标定位到屏幕中央
				//cout << "非常棒哦！恭喜通关！！！" << endl;
				//break;
				int flag;
				//将项目属性中字符集的默认“使用Unicode字符集”改为“使用多字节字符集”
				//使MessageBox()函数中参数2和参数3能编译通过
				flag = MessageBox(NULL, "是否再来一次？", "恭喜，你通关了！！！", MB_YESNO);//弹出对话框
				if (flag == 7)//选择否，结束程序
				{
					system("cls");//清屏
					break;//退出程序
				}
				else if (flag == 6)//选择是，重启程序
				{
					system("cls");//清屏
					game mygame;
					mygame.run();
				}
			}
			changeInfo();//修改游戏信息
			pfood->createPos(psnake->s_vecBody);//更改食物位置
			pfood->show();//再次出现食物
		}
		if (checkFailed())//检测是否失败
		{
			//system("cls");//清屏
			//unit::gotoxy(35, 10);//光标定位到屏幕中央
			//cout << "你输了！游戏结束";
			//break;
			int flag;
			flag = MessageBox(NULL, "再来一次？", "你输了！！！", MB_YESNO);//弹出对话框
			if (flag == 7)//选择否，结束程序
			{
				system("cls");//清屏
				break;
			}
			else if (flag == 6)//选择是，重启程序
			{
				system("cls");//清屏
				game mygame;
				mygame.run();
			}
		}
	}
}
bool game::checkFailed()//失败检测
{
	for (int i=1; i < psnake->s_length; i++)
	{
		//蛇头碰到蛇身——自残死
		if ((psnake->s_headx == psnake->s_vecBody[i].x) && (psnake->s_heady == psnake->s_vecBody[i].y))
			return true;
	}
	if ((psnake->s_vecBody[0].x <= game::KLEFT) || (psnake->s_vecBody[0].x >= (game::KLEFT + game::KWIDTH-1)))
	{
		//碰壁死（左右）
		return true;
	}
	if ((psnake->s_heady <= game::KUP +2)|| (psnake->s_heady >= (game::KUP + game::KHEIGHT+1)))
	{
		//碰壁死（上下）
		return true;
	}
	return false;
}
bool game::checkLevel()//等级检测
{
	switch (iLevel)
	{
	case 1:  //1级时，达到30分可升级
		if (iScore % 30 == 0 && iScore != 0)
		{
			iLevel++;//等级加1
			iScore = 0;//分数归0
			psnake->s_speed = psnake->s_speed + 100;//提速
		}
		return false;
	case 2: //2级时，达到50分可升级
		if (iScore % 50 == 0 && iScore != 0)
		{
			iLevel++;//等级加1
			iScore = 0;//分数归0
			psnake->s_speed = psnake->s_speed + 200;//提速
		}
		 return false;
	case 3: //3级时，达到100分可通关
		if (iScore % 100 == 0 && iScore != 0)
		{
			return true;//通关
		}
		return false;
	}
}
void game::drawGameArea()//绘制游戏框图 
{
	unit::gotoxy(KLEFT, KUP);
	for (int j = 0; j < KWIDTH; j++)//绘制上边框
		cout << "-";
	for (int i = 0; i < KHEIGHT; i++)
	{
		unit::gotoxy(KLEFT, KUP + 1 + i);//绘制左边框
		cout << "|";
		unit::gotoxy(KLEFT + KWIDTH - 1, KUP + 1 + i);//绘制右边框
		cout << "|";
	}
	unit::gotoxy(KLEFT, KUP + KHEIGHT + 1);//绘制下边框
	for (int k = 0; k < KWIDTH; k++)
		cout << "-";
	unit::gotoxy(KLEFT + 1, KUP + 2);//绘制标题下边框
	for (int i = 0; i < KWIDTH - 2; i++)
		cout << "-";
}
void game::drawGameInfo()//绘制游戏信息
{
	unit::gotoxy(KLEFT + 1, KUP + 1);
	cout << "游戏名称：贪吃蛇";
	unit::gotoxy(KLEFT + 20, KUP + 1);
	cout << "编写者：zjd";
	unit::gotoxy(KLEFT + 40, KUP + 1);
	cout << "得分";
	unit::gotoxy(KLEFT + KSCORE_OFFSET, KUP + 1);
	cout << iScore;
	unit::gotoxy(KLEFT + 55, KUP + 1);
	cout << "当前关卡";
	unit::gotoxy(KLEFT + KLEVEL_OFFSET, KUP + 1);
	cout << iLevel;
	/*unit::gotoxy(KLEFT, KUP + KHEIGHT + 2);
	cout << "游戏规则： 通过方向键控制贪吃蛇上下左右移动;空格键暂停" << endl;
	unit::gotoxy(KLEFT , KUP + KHEIGHT + 3);
	cout << "共三关：第一关30分通过" << endl;
	unit::gotoxy(KLEFT , KUP + KHEIGHT + 4);
	cout << "        第二关50分通过" << endl;
	unit::gotoxy(KLEFT , KUP + KHEIGHT + 5);
	cout << "        第三关100分通过" << endl;*/

}
void game::changeInfo()//更改游戏信息
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

