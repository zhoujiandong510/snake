#pragma once
#include "unit.h"
#include<vector>

class food :
	public unit
{
public:
	food(int a = 0,int b =0,char pic='@');
	void createPos(vector<unit> vec);//随机数生成食物位置（不能出现在蛇身上）
	virtual ~food();
	
};

