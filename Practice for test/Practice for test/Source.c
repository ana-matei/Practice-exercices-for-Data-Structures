#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Datautil.h"
//#include "List.h"
#include "DoubleLinkedList.h"

#define MAX_NO_LINE 256

int main()
{
	////List* list = NULL; // the head pointer I think 
	//DLL* doubleList = NULL;

	//FILE* pfile = fopen("Data.txt", "r");

	//if(pfile)
	//{ 

	//	char buffer[MAX_NO_LINE];
	//	char name[MAX_NO_LINE];
	//	int income;
	//	unsigned short reference;
	//	char* token = NULL;
	//	char* delimiter = "/,";

	//	while (fgets(buffer, sizeof(buffer), pfile)) {

	//		token = strtok(buffer, delimiter);
	//		strcpy(name, token);
	//		//printf("%s\n", name);
	//		token = strtok(NULL, delimiter);
	//		income = atof(token);
	//		//printf("%.1f\n", income);
	//		//printf("%d\n", income);
	//		token = strtok(NULL, delimiter);
	//		reference = atoi(token);
	//		//printf("%d\n", reference);

	//		Student* stud = createStudent(name, income, reference);
	//		//printStudent(stud);
	//		
	//		// List methods
	//		//list = insertNodeatHead(list, stud);
	//		//list = insertNodeatTail(list, stud);
	//		//insertAtHead(&list, stud);
	//		//insertAtTail(&list, stud);
	//		
	//		// Double Link List Method
	//		//doubleList = insertNodeAtHead(doubleList, stud);
	//		doubleList = insertNodeAtTail(doubleList, stud);


	//	}
	//	
	//	// List Methods
	//	//displayLinkedList(list);
	//	//printf("\n");
	//	//list = deleteElement(4, list);
	//	////list = reverseList(list);
	//	//displayLinkedList(list);

	//	// Double Linked List Methods
	//	printDLL(doubleList);
	//	printf("\n");
	//	printDLLreversed(doubleList);
	//}

	//fclose(pfile);




	FILE* f = fopen("Data.txt", "r");
	if (f)
	{

		char name[255];
		int income;
		unsigned short reference;
		char* delimiter = ",";
		char* token = NULL;
		char buffer[255];

		while (fgets(buffer, sizeof(buffer), f))
		{
			token = strtok(buffer, delimiter);
			strcpy(name, token);
			printf("%s", name);

			token = strtok(NULL, delimiter);
			income = atoi(token);

			token = strtok(NULL, delimiter);
			reference = atoi(token);

		}

	}

	fclose(f);




}