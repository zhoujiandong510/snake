#pragma once
#include "pch.h"
#include <iostream>
using namespace std;
class unit
{
public:
	int x;//������
	int y;//������
	char symbol;
public:
	unit(int a=0, int b=0, char s='*');
	void show();
	void erase();
	static void gotoxy(int x, int y);
	~unit();
}; 

