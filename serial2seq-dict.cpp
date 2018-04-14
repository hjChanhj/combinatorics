/********************
* ��ţ�serial
* ������a[n-1]~a[1]
* ���У�result[n]~result[1]
*********************/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define N 4 //Ԫ�ظ���

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


//�������
		cin >> serial;	//*/
		cout << "��� = " << serial << endl;

/***************************  1. ���->����  *******************************/
	int index = 1;
	do {
		a[index] = serial % (index + 1);
		serial = serial / (index + 1);
		index++;
	} while (serial);
//��ӡ����
	cout << "������";
	for (i = N - 1; i > 0; i--)
	{
		cout << a[i] << " ";
	}
	cout << endl;	//*/
/***************************  1. ����->���� end *******************************/

/***************************  2. ����->����  **********************************/
	List_node *head, *p, *p1;
	head = (struct List_node *)malloc(sizeof(List_node));
	p = head;

	//��������result���ӵ�Nλ��ʼ������㣬remain����洢���ǳ�ȥ�Ѽ����result��Ա��ʣ���result��Ա��������С�����˳��洢
	MyList *remain = (MyList *)malloc(sizeof(MyList));
	remain->count = 0;
	remain->first = head;
	remain->last = head;
	//remain�����ʼ��Ϊ���ݷֱ���1-N
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
		//����result�ĵ�j����ֵ����remain�е�(a[j - 1] + 1)���ڵ��data
		result[j] = find(remain, a[j - 1] + 1);
		//remain��ɾ��result[j]
		remove(remain, (a[j - 1] + 1));
	}
	//result[1]Ϊremain�����ʣ�µ�����
	result[1] = remain->first->data;
/***************************  2. ����->���� end *******************************/

//������
	cout << "���У�";
	for (int i = N; i>0; i--)
	{
		cout << result[i] << " ";
	}
	cout << endl;	//*/

	freeMyList(remain);

	system("pause");
    return 0;
}

//���������index���ڵ������
int find(MyList *list, int index)
{
	List_node *p2 = list->first;
	for (int i = 1; i < index; i++)
	{
		p2 = p2->next;
	}
	return p2->data;
}

//ɾ�������index���ڵ������
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

//ɾ������ĵ�һ���ڵ�
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


//ɾ����������һ���ڵ�
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

//�ͷ�����
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
