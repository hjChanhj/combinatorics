/********************
* ���У�s[n]~s[1]
* ������a[n-1]~a[1]
* ��ţ�result
*********************/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define N 4 //Ԫ�ظ���

int factorial(int n);
int count1(int s[], int n, int obj);
int count2(int s[], int n, int obj);


using namespace std;

int main()
{
	int i, j, x = 0, num = 0;
	int max_left, max_right, max_left_num, max_right_num, max_left_count, max_right_count;
	double result = 0;
	int s[N + 1];
	int a[N] = { 0 };
	int m, n, k;
	clock_t start, end;
	double cost_time;


//��������,�ո�������س�����
/*	for (i = N ; i > 0; i--)
	{
		cin >> s[i];
	}	//*/
//�������Ԫ�ظ���ΪN������
	srand((unsigned int)time(NULL));
	for (i = 0; i < N + 1; i++) 
	{
		s[i] = i;
	}
	for (j = 0; j < N; j++) 
	{
		m = rand() % N + 1;
		n = rand() % N + 1;
		k = s[m];
		s[m] = s[n];
		s[n] = k;
	}	//*/
//��ӡ����
	cout << "���У�";
	for (int i = N; i>0; i--) 
	{
		cout << s[i] << " ";
	}
	cout << endl;	//*/
	
/***************************  1. ����->����  *******************************/
//����s[1] - s[i]�б�s[obj]С�ĸ���
//method 1:
	start = clock();
	for (i = N; i > 0; i--)
	{
		a[i - 1] = count1(s, N, i);
	}
	end = clock();
	cost_time = end - start;
	cout << "method 1 costs time = " << cost_time << "ms" << endl;
	//��ӡ����
	cout << "������";
	for (i = N - 1; i > 0; i--)
	{
		cout << a[i] << " ";
	}
	cout << endl;	//*/

//method 2:
	start = clock();
	for (i = N; i > 0; i--)
	{
		a[i - 1] = count2(s, N, i);
	}
	end = clock();
	cost_time = end - start;
	cout << "method 2 costs time = " << cost_time << "ms" << endl;
	//��ӡ����
	cout << "������";
	for (i = N - 1; i > 0; i--)
	{
		cout << a[i] << " ";
	}
	cout << endl;	//*/

//method 3:
//method 2�Ļ����ϣ����߷ֱ𱣴�һ�����ֵ�����Ӧ�ļ������±�
	start = clock();
	max_right = s[N];
	max_right_num = N;
	max_right_count = 0;
	for (i = N; i > N / 2; i--)
	{
		x = 0;
		if (s[i] > max_right)
		{
			for (j = max_right_num; j > i; j--)
			{
				if (s[j] < s[i])
				{
					x++;
				}
			}
			x += max_right_count;
			//����
			max_right = s[i];
			max_right_num = i;
			max_right_count = x;
		}
		else
		{
			for (j = N; j > i; j--)
			{
				if (s[j] < s[i])
				{
					x++;
				}
			}
		}

		num = s[i] - 1 - x;
		a[i - 1] = num;
	}

	max_left = s[1];
	max_left_num = 1;
	max_left_count = 0;
	for (i = 1; i <= N / 2; i++)
	{
		num = 0;
		if (s[i] > max_left)
		{
			for (j = max_left_num; j < i; j++)
			{
				if (s[j] < s[i])
				{
					num++;
				}
			}
			num += max_left_count;
			//����
			max_left = s[i];
			max_left_num = i;
			max_left_count = num;
		}
		else
		{
			for (j = 1; j < i; j++)
			{
				if (s[j] < s[i])
				{
					num++;
				}
			}
		}
		a[i - 1] = num;
	}
	end = clock();
	cost_time = end - start;
	cout << "method 3 costs time = " << cost_time << "ms" << endl; //*/
	
//��ӡ����
	cout << "������";
	for (i = N - 1; i > 0; i--)
	{
		cout << a[i] << " ";
	}
	cout << endl;	//*/
/***************************  1. ����->���� end *******************************/

/***************************  2. ����->���  **********************************/
	for (i = 1; i < N; i++)
	{
		result += a[i] * factorial(i);
	}
/***************************  2. ����->��� end *******************************/


//������
	cout << "result = " << result << endl;

	system("pause");
    return 0;
}


//��׳��Ӻ���
int factorial(int n)
{
	int i;
	int fact = 1;
	for (i = 1; i <= n; i++)
		fact *= i;

	return fact;
}

//����s[i] < (s[1] ~ s[i-1])�ĸ����ļ��ַ���:
//method 1:
//����s[1] - s[i]�б�s[obj]С�ĸ���
int count1(int s[], int n, int obj)
{
	int i;
	int num = 0;

	for (i = 1; i < obj; i++)
	{
		if (s[i] < s[obj])
		{
			num++;
		}
	}

	return num;
}


//method 2:
//�ֳ�����s[n]-s[n/2 + 1]�Ͷ�s[1]-s[n/2]
int count2(int s[], int n, int obj)
{
	int i, x = 0;
	int num = 0;
	//��s[n]-s[n/2 + 1],����s[obj]-s[n]�б�s[obj]С�ĸ���x��num = s[obj] - 1 - x;
	if (obj > n / 2)
	{
		for (i = n; i > obj; i--)
		{
			if (s[i] < s[obj])
			{
				x++;
			}
		}
		num = s[obj] - 1 - x;
	}
	//��s[1]-s[n/2],����s[1]-s[i]�б�s[obj]С�ĸ���x��num  = x;
	else
	{
		for (i = 1; i < obj; i++)
		{
			if (s[i] < s[obj])
			{
				num++;
			}
		}
	}

	return num;
}
