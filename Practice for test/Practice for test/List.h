#pragma 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Datautil.h"

struct Node
{

	Student* data;
	struct Node* next;

};
typedef struct Node List;

List* createNode(Student* stud)
{
	if (stud != NULL)
	{
		List* node = NULL;
	    node = (List*)malloc(sizeof(List));
		node->data = stud;
		node->next = NULL;
		printf("Succesful\n");
		return node;
	}
}

List* insertNodeatHead(List* list, Student* stud) // returning it to a varible, so we return the memory locstion of the node and we modify it in here so is all good
{
	List* node = createNode(stud);
	node->next = list;
	return node;
}

void insertAtHead(List** list, Student* stud) // without returning it to a variable so we need a pointer to pointer so that we can modify the pointer to the lsit so the changes are kept in main
{
	List* node = createNode(stud);
	
		if (*list == NULL)
		{
			*list = node;
		}
	else {
		node->next = *list;
		*list = node;
	}
}  // you need to remeber in the call in main that you need to h=give the address of the list for the void function to work (&)

List* insertNodeatTail(List* list, Student* stud)
{
	if (list == NULL)
	{
		List* node = createNode(stud);
		node->next = NULL;
		return node;
	}
	else {
		List* node = createNode(stud);
		List* temp = list;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = node;
		return list;
	}
}


void insertAtTail(List** list, Student* stud)
{
	List* node = createNode(stud);
	List* temp = *list;
	if (*list==NULL)
	{
		node->next = *list;
		*list = node;
	}
	else {
		while (temp->next!=NULL)
		{
			temp = temp->next;

		}
		temp->next = node;
	}


}

List* deleteElement(int n, List* list)
{
	List* temp = list;
	List* temp1 = list;
	if (n == 1)
	{
		temp = temp->next;
		//free(list->data->name);
		free(list);
		return temp;
		
	}
	else {
		for (int i = 1; i < n-1; i++)
		{
			temp = temp->next;
		}
		temp1 = temp->next;
		temp->next = temp->next->next;
		free(temp1);
		return list;

	}

}


List* reverseList(List* list)
{
	List* current = list;
	List* prev = NULL;
	List* following = list;

	while (following != NULL)
	{

		following = current->next;
		current->next = prev;
		prev = current;
		current = following;
	}
	list = prev;

	return list;



}


void displayLinkedList(List* list)
{
	while (list)
	{
		printStudent(list->data);
		list = list->next;
	}
}