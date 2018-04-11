/********************
* 序号：serial
* 序数：a[n-1]~a[1]
* 排列：result[n]~result[1]
*********************/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define N 4 //元素个数

using namespace std;

int main()
{
	int i, j;
	int serial;
	int result[N + 1] = { 0 };
	int a[N] = { 0 };
	clock_t start, end;
	double cost_time;


//输入序号
		cin >> serial;	//*/
		cout << "序号 = " << serial << endl;

/***************************  1. 序号->序数  *******************************/
	int index = 1;
	do {
		a[index] = serial % (index + 1);
		serial = serial / (index + 1);
		index++;
	} while (serial);
//打印序数
	cout << "序数：";
	for (i = N - 1; i > 0; i--)
	{
		cout << a[i] << " ";
	}
	cout << endl;	//*/
/***************************  1. 排列->序数 end *******************************/

/***************************  2. 序数->排列  **********************************/
	for (j = N - 1; j >= 1; j--)
	{
		index = 1;
		int spacecount = 0;
		while (spacecount < a[j] || result[index] != 0)
		{
			if (result[index] == 0)
				spacecount++;
			index++;
		}
		result[index] = j + 1;
	}
	index = N;
	while (result[index] != 0)
		index--;
	result[index] = 1;
/***************************  2. 序数->排列 end *******************************/


//输出结果
	cout << "排列：";
	for (int i = N; i>0; i--)
	{
		cout << result[i] << " ";
	}
	cout << endl;	//*/

	system("pause");
    return 0;
}

