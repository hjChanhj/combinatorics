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

typedef struct  List_node
{
	int data;
	struct List_node *next;
}List_node;

typedef struct MyList
{
	List_node *first;
	List_node *last;
	int count;
} MyList;

int find(MyList *list, int index);
void remove(MyList *list, int index);
void myListRemoveDataAtFirst(MyList * const list);
void myListRemoveDataAtLast(MyList* const list);
void freeMyList(MyList * list);

int main2()
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
	List_node *head, *p, *p1;
	head = (struct List_node *)malloc(sizeof(List_node));
	p = head;

	//对于排列result，从第N位开始倒序计算，remain链表存储的是除去已计算的result成员后剩余的result成员，并按从小到大的顺序存储
	MyList *remain = (MyList *)malloc(sizeof(MyList));
	remain->count = 0;
	remain->first = head;
	remain->last = head;
	//remain链表初始化为数据分别是1-N
	for (j = 1; j < N + 1; j++)
	{
		p1 = p;
		p = (struct List_node *)malloc(sizeof(List_node));
		p1->data = j;
		p1->next = p;
		remain->count++;
	}
	p->next = NULL;
	remain->last = p;

	for (j = N; j > 1; j--)
	{
		//排列result的第j个数值等于remain中第(a[j - 1] + 1)个节点的data
		result[j] = find(remain, a[j - 1] + 1);
		//remain中删掉result[j]
		remove(remain, (a[j - 1] + 1));
	}
	//result[1]为remain中最后剩下的数据
	result[1] = remain->first->data;
/***************************  2. 序数->排列 end *******************************/

//输出结果
	cout << "排列：";
	for (int i = N; i>0; i--)
	{
		cout << result[i] << " ";
	}
	cout << endl;	//*/

	freeMyList(remain);

	system("pause");
    return 0;
}

//查找链表第index个节点的数据
int find(MyList *list, int index)
{
	List_node *p2 = list->first;
	for (int i = 1; i < index; i++)
	{
		p2 = p2->next;
	}
	return p2->data;
}

//删除链表第index个节点的数据
void remove(MyList *list, int index)
{
	List_node *p2 = list->first;

	if (index == 1)
		myListRemoveDataAtFirst(list);
	else if (index == list->count)
		myListRemoveDataAtLast(list);
	else
	{
		for (int i = 1; i < index - 1; i++)
		{
			p2 = p2->next;
		}
		List_node *p = p2->next;
		p2->next = p2->next->next;
		free(p);
	}
	(list->count)--;
}

//删除链表的第一个节点
void myListRemoveDataAtFirst(MyList * const list)
{
	List_node *p = list->first;
	list->first = p->next;
	free(p);
	(list->count)--;
	if (list->count == 0)
	{
		list->last = NULL;
	}
}


//删除链表的最后一个节点
void myListRemoveDataAtLast(MyList* const list)
{
	List_node * p = list->first;
	while (p->next != list->last)
	{
		p = p->next;
	}
	free(list->last);
	p->next = NULL;
	list->last = p;
	(list->count)--;
}

//释放链表
void freeMyList(MyList * list)
{
	List_node *p;
	while (list->first)
	{
		p = list->first->next;
		free(list->first);
		list->first = p;
	}
	free(list);
}
