#pragma once
#include "unit.h"
#include<vector>

class food :
	public unit
{
public:
	food(int a = 0,int b =0,char pic='@');
	void createPos(vector<unit> vec);//���������ʳ��λ�ã����ܳ����������ϣ�
	virtual ~food();
	
};

