#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFERSIZE 255

struct Exam
{
	char* examCode;
	unsigned int studentNo;
	char* examDate;
	float finalGrade;
	 
};

typedef struct Exam Exam;


struct SimpleLinkedList
{
	Exam* info;
	struct SimpleLinkedList* next;
};

typedef struct SimpleLinkedList Node;


Exam* createExam(char*, unsigned int, char*, float);
void printExam(Exam*);
Node* createNode(Exam*);
void insertList(Node**, Exam*);
void printList(Node*);
int countTreshold(Node*, const float);
float averageParticipation(Node*, int, int);
void deleteNode(Node**);
void deleteExams(Node**, const char*);





int main()
{

	FILE* f = fopen("Data.txt", "r");

	Node* list = NULL;

	if (f)
	{

		char examCode[BUFFERSIZE];
		unsigned int studentNo;
		char examDate[BUFFERSIZE];
		float finalGrade;


		char* token = NULL;
		char buffer[BUFFERSIZE];
		char* dlm = ",\n";


		while (fgets(buffer, sizeof(buffer), f))
		{
			token = strtok(buffer, dlm);
			strcpy(examCode, token);

			token = strtok(NULL, dlm);
			studentNo = atoi(token);

			token = strtok(NULL, dlm);
			strcpy(examDate, token);

			token = strtok(NULL, dlm);
			finalGrade = atof(token);

			Exam* exam = createExam(examCode, studentNo, examDate, finalGrade);
			//printExam(exam);

			insertList(&list, exam);

		}


		// ex 2
		printList(list);

		// ex 3
		int count = countTreshold(list, 7.9);
		printf("Count %d\n", count);

		// ex 4
		float averageNoStud = averageParticipation(list, 0, 0);
		printf("%5.2f\n",averageNoStud);

		// ex 5 
		deleteExams(&list, "2024-09-06");
		printList(list);

	}

}


Exam* createExam(char* examCode, unsigned int studentNo, char* examDate, float finalGrade)
{
	Exam* exam = (Exam*)malloc(sizeof(Exam));

	exam->examCode = (char*)malloc(strlen(examCode)+1);
	strcpy(exam->examCode, examCode);

	exam->studentNo = studentNo;

	exam->examDate = (char*)malloc(strlen(examDate) + 1);
	strcpy(exam->examDate, examDate);

	exam->finalGrade = finalGrade;
}

void printExam(Exam* exam)
{
	printf("Exam: %s, %d, %s, %5.2f\n", exam->examCode, exam->studentNo, exam->examDate, exam->finalGrade);
}

Node* createNode(Exam* exam)
{
	Node* node = (Node*)malloc(sizeof(Node));

	node->info = exam;
	node->next = NULL;
	return node;
}


// this is the insert for the subject 
void insertList(Node** list, Exam* exam)
{
	Node* node = createNode(exam);
	Node* temp = (*list);
	if ((*list) == NULL)
	{
		(*list) = node;
	}
	else
	{
		if (exam->studentNo <= 100) 
		{
			node->next = (*list);
			(*list) = node;
		}
		else if (exam->studentNo > 100)
		{
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = node;
		}

	}
}


// this is the isnert in case we need a criterion to insert, like to have the final grade in order
//void insertList(Node** list, Exam* exam)
//{
//	Node* node = createNode(exam);
//	Node* temp = *list;
//	if ((*list) == NULL)
//	{
//		(*list) = node;
//	}
//	else
//	{
//		if ((*list)->info->finalGrade > exam->finalGrade)
//		{
//			node->next = *list;
//			*list = node;
//		}
//		else
//		{
//			while (temp->next != NULL && temp->next->info->finalGrade < exam->finalGrade)
//			{
//				temp = temp->next;
//			}
//
//			node->next = temp->next;
//			temp->next = node;
//		}
//
//	}
//}


void printList(Node* list)
{
	printf("Students with the StudentNo <= 100:\n");
	while (list && list->info->studentNo <= 100)
	{
		printExam(list->info);
		list = list->next;
	}

	printf("Students with the StudentNo > 100:\n");
	while (list && list->info->studentNo > 100)
	{
		printExam(list->info);
		list = list->next;
	}

}


int countTreshold(Node* list, const float key)
{
	int count = 0;
	while (list->next != NULL)
	{
		if (list->info->finalGrade > key)
		{
			count++;
		}
		list = list->next;
	}
	return count;
}



float averageParticipation(Node* list, int sum, int count)
{
	if (list == NULL)
	{
		float average;
		average = (float)sum / count;
		return average;
	}
	else
	{ 
		sum += list->info->studentNo;
		count++;
		averageParticipation(list->next, sum, count);
	}
	
}

void deleteNode(Node** node)
{
	free((*node)->info->examCode);
	free((*node)->info->examDate);
	free((*node)->info);
	free(*node);
}

void deleteExams(Node** list, const char* date)
{
	while ((*list)->next != NULL && strcmp((*list)->info->examDate, date) < 0)
	{
		Node* current = *list;
		*list = (*list)->next;
		deleteNode(&current);
	}

	Node* current = *list;
	while (current->next != NULL)
	{
		if (strcmp(current->next->info->examDate, date) < 0)
		{
			Node* temp = current->next;
			current->next = current->next->next;
			deleteNode(&temp);
		}
		else
		{
			current = current->next;
		}
	}
}






