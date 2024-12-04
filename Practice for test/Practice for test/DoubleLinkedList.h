#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Datautil.h"

struct DoubleLinkedList
{
	struct DoubleLinkedList* prev;
	Student* data;
	struct DoubleLinkedList* next;
};

typedef struct DoubleLinkedList DLL;

DLL* createNode(Student* stud)
{
	DLL* node = NULL;
	node = (DLL*)malloc(sizeof(DLL));
	node->data = stud;
	node->prev = NULL;
	node->next = NULL;
	printf("Succes\n");
	return node;
}

DLL* insertNodeAtHead(DLL* doubleList, Student* stud)
{
	if (doubleList == NULL)
	{
		DLL* node = createNode(stud);
		node->next = doubleList;
		return node;
	}
	else
	{
		DLL* temp = createNode(stud);
		temp->next = doubleList;
		doubleList->prev = temp;
		return temp;

	}
}


DLL* insertNodeAtTail(DLL* doubleList, Student* stud)
{
	if (doubleList == NULL)
	{
		DLL* temp = createNode(stud);
		doubleList = temp;
		return doubleList;
	}
	else {
		DLL* temp = createNode(stud);
		DLL* temp1 = doubleList;
		while (doubleList->next!=NULL)
		{
			doubleList = doubleList->next;
		}
		doubleList->next = temp;
		temp->prev = doubleList;
		return temp1;
	}
}



DLL* deleteByKey(DLL* doubleList)
{

}


void printDLL(DLL* doubleList)
{
	while (doubleList!=NULL)
	{
		printStudent(doubleList->data);
		doubleList = doubleList->next;
	}
}

void printDLLreversed(DLL* doubleList)
{
	while (doubleList->next != NULL)
	{
		doubleList = doubleList->next;
	}

	while (doubleList != NULL)
	{
		printStudent(doubleList->data);
		doubleList = doubleList->prev;
	}

}
