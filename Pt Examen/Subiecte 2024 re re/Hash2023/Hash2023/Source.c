#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFERSIZE 255
#define HASHSIZE 10

struct Task
{
	unsigned int id;
	char* date;
	char* owner;
	float completion;
};

typedef struct Task Task;

struct SimpleLinkedList
{
	Task* info;
	struct SimpleLinkedList* next;
};

typedef struct SimpleLinkedList Node;


struct HashTable
{
	Node** buckets;
	int size;
};

typedef struct HashTable Hash;



Task* createTask(unsigned int, char*, char*, float);
void printTask(Task*);
Node* createNode(Task*);
void addNode(Node**, Task*);
int fHash(char*, int);
void addHash(Hash**, Task*);
void printList(Node*);
void printHash(Hash*);
void printNoTasks(Hash*, char*);
void coounForCompletion(Hash*, float);
void changeOwner(Hash**, int, char*);





int main()
{

	FILE* f = fopen("Data.txt", "r");
	Hash* hashTable = NULL;

	if (f)
	{
		unsigned int id;
		char date[BUFFERSIZE];
		char owner[BUFFERSIZE];
		float completion;

		char* token = NULL;;
		char* dlm = ",\n";
		char buffer[BUFFERSIZE];

		while (fgets(buffer, sizeof(buffer), f))
		{
			token = strtok(buffer, dlm);
			id = atoi(token);

			token = strtok(NULL, dlm);
			strcpy(date, token);

			token = strtok(NULL, dlm);
			strcpy(owner, token);

			token = strtok(NULL, dlm);
			completion = atof(token);

			Task* task = createTask(id, date, owner, completion);
			printTask(task);

			// ex 1
			addHash(&hashTable, task);
		}

		// ex 2
		printf("\n");
		printHash(hashTable);

		// ex 3
		
		printNoTasks(hashTable, "Diana");

		// ex 4 
		printf("\n");
		coounForCompletion(hashTable, 60);

		// ex 5
		printf("\n");
		changeOwner(&hashTable, 19, "Isabel");
		printHash(hashTable);
	}


	

}


Task* createTask(unsigned int id, char* date, char* owner, float completion)
{
	Task* task = (Task*)malloc(sizeof(Task));
	task->id = id;

	task->date = (char*)malloc(strlen(date) + 1);
	strcpy(task->date, date);

	task->owner = (char*)malloc(strlen(owner) + 1);
	strcpy(task->owner, owner);

	task->completion = completion;

	return task;

}


void printTask(Task* task)
{
	printf("Task: %d, %s, %s, %5.2f\n", task->id, task->date, task->owner, task->completion);
}



Node* createNode(Task* task)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->info = task;
	node->next = NULL;

	return node;
}

void addNode(Node** list, Task* task)
{
	Node* node = createNode(task);
	if (*list == NULL)
	{
		(*list) = node;
	}
	else
	{
		node->next = *list;
		*list = node;
	}

}

int fHash(char* key, int size)
{
	int sum = 0;
	for (int i = 0; i < strlen(key); i++)
	{
		sum += key[i];
	}

	return sum % size;
}

void addHash(Hash** hashTable, Task* task)
{
	if (*hashTable == NULL)
	{
		*hashTable = (Hash*)malloc(sizeof(Hash));
		(*hashTable)->size = HASHSIZE;
		(*hashTable)->buckets = (Node**)malloc((*hashTable)->size* sizeof(Node*));
		memset((*hashTable)->buckets, 0, (*hashTable)->size * sizeof(Node*));
	}

		int index = fHash(task->owner, (*hashTable)->size);
		addNode(&(*hashTable)->buckets[index], task);
}


void printList(Node* list)
{
	Node* temp = list;

	while (temp != NULL)
	{
		printTask(temp->info);
		temp = temp->next;
	}
}

void printHash(Hash* hashTable)
{
	for (int i = 0; i < hashTable->size; i++)
	{
		printf("Bucket %d:", i);
		printList(hashTable->buckets[i]);
		printf("\n");
	}
}


void printNoTasks(Hash* hashTable, char* key)
{
	
	int count = 0;
	int index = fHash(key, hashTable->size);
	Node* temp = hashTable->buckets[index];
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}

	printf("No of tasks for %s is: %d", key, count);
}

void coounForCompletion(Hash* hashTable, float completion)
{
	int count = 0;
	for (int i = 0; i < hashTable->size; i++)
	{
		Node* temp = hashTable->buckets[i];
		while (temp != NULL)
		{
			if (temp->info->completion > completion)
			{
				count++;
			}
			temp = temp->next;
		}
	}

	printf("No of task above the completion required: % d", count);
}

void changeOwner(Hash** hashTable, int taskId, char* newName)
{
	for (int i = 0; i< (*hashTable)->size; i++)
	{
		Node* temp = (*hashTable)->buckets[i];
		Node* prev = NULL;

		while (temp != NULL)
		{
			if (temp->info->id == taskId)
			{
				if (prev == NULL)
				{
					(*hashTable)->buckets[i] = temp->next;
				}
				else
				{
					prev->next = temp->next;
				}

				free(temp->info->owner);
				temp->info->owner = (char*)malloc(strlen(newName) + 1);
				strcpy(temp->info->owner, newName);

				addHash(&(*hashTable), temp->info);

				free(temp);
				return;
			}

			prev = temp;
			temp = temp->next;
		}
	}
}