#include "pch.h"
#include<windows.h>
#include "unit.h"
#include <iostream>
using namespace std;
unit::unit(int a, int b, char s)
{
	x = a;
	y = b;
	symbol = s;
}

void unit::gotoxy(int x,int y)//���ƹ��λ��
{
	COORD coor;
	coor.X = x;
	coor.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, coor);//���
}
void unit::show()
{
	unit::gotoxy(x, y);
	cout << symbol;
}
void unit::erase()
{
	unit::gotoxy(x, y);
	cout << " ";
}
unit::~unit()
{
}