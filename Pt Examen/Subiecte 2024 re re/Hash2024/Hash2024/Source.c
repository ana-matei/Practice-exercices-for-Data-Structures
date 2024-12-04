#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define	BUFFERSIZE 255
#define HASHSIZE 10

struct Arrival
{
	unsigned short trainNo;
	char* destination;
	char* arrivalTime;
	unsigned short delay;
	unsigned short passagersNo;
};

typedef struct Arrival Arrival;


struct SimpleLinkedList
{
	Arrival* info;
	struct SimpleLinkedList* next;
};

typedef struct SimpleLinkedList Node;

struct Hash
{
	Node** buckets;
	int size;
};

typedef struct Hash Hash;


Arrival* createArrival(unsigned short, char*, char*, unsigned short, unsigned short);
void printArrival(Arrival*);
Node* createNode(Arrival*);
void addNode(Node**, Arrival*);
int fhash(char*, int);
void addHash(Hash**, Arrival*);
void printList(Node*);
void printHash(Hash*);
Arrival* lastArrival(Hash*, char*);
void changeDestination(Hash**, char*, unsigned short);




int main()
{

	FILE* f = fopen("Data.txt", "r");
	Hash* hash = NULL;

	if (f)
	{
		unsigned short trainNo;
		char destination[BUFFERSIZE];
		char arrivalTime[BUFFERSIZE];
		unsigned short delay;
		unsigned short passagersNo;

		char* token = NULL;
		char* dlm = ",\n";
		char buffer[BUFFERSIZE];


		while (fgets(buffer, sizeof(buffer), f))
		{
			token = strtok(buffer, dlm);
			trainNo = atoi(token);

			token = strtok(NULL, dlm);
			strcpy(destination, token);

			token = strtok(NULL, dlm);
			strcpy(arrivalTime, token);

			token = strtok(NULL, dlm);
			delay = atoi(token);

			token = strtok(NULL, dlm);
			passagersNo = atoi(token);

			Arrival* arrival = createArrival(trainNo, destination, arrivalTime, delay, passagersNo);

			// ex 1
			addHash(&hash, arrival);
		}
	}

	// ex 2
	printHash(hash);


	// ex 3
	printf("\n");
	Arrival* lastArrival1 = lastArrival(hash, "Bucuresti");
	printArrival(lastArrival1);

	// ex 4
	printf("\n");
	int noDelays = countDelays(hash);
	printf("No of delays: %d", noDelays);

	// ex 5
	printf("\n");
	changeDestination(&hash, "Craiova", 3);
	printHash(hash);



}

Arrival* createArrival(unsigned short trainNo, char* destination, char* arrivalTime, unsigned short delay, unsigned short passengersNo)
{
	Arrival* arrival = (Arrival*)malloc(sizeof(Arrival));

	arrival->trainNo = trainNo;

	arrival->destination = (char*)malloc(strlen(destination) + 1);
	strcpy(arrival->destination, destination);

	arrival->arrivalTime = (char*)malloc(strlen(arrivalTime) + 1);
	strcpy(arrival->arrivalTime, arrivalTime);

	arrival->delay = delay;
	arrival->passagersNo = passengersNo;

	return arrival;
}

void printArrival(Arrival* arrival)
{
	printf("%d, %s, %s, %d, %d\n", arrival->trainNo, arrival->destination, arrival->arrivalTime, arrival->delay, arrival->passagersNo);
}

Node* createNode(Arrival* arrival)
{
	Node* node = (Node*)malloc(sizeof(Node));

	node->info = arrival;
	node->next = NULL;

	return node;
}

void addNode(Node** list, Arrival* arrival)
{
	Node* node = createNode(arrival);
	if ((*list) == NULL)
	{
		*list = node;
	}
	else
	{
		node->next = *list;
		*list = node;
	}
}

int fhash(char* key, int size)
{
	int sum = 0;
	for (int i = 0; i < strlen(key); i++)
	{
		sum += key[i];
	}

	return sum % size;
}

void addHash(Hash** hashTable, Arrival* arrival)
{
	if ((*hashTable) == NULL)
	{
		*hashTable = (Hash*)malloc(sizeof(Hash));
		(*hashTable)->size = HASHSIZE;
		(*hashTable)->buckets = (Node**)malloc(sizeof(Node*) * (*hashTable)->size);
		memset((*hashTable)->buckets, 0, sizeof(Node*) * (*hashTable)->size);
	}

		int index = fhash(arrival->destination, (*hashTable)->size);
		addNode(&(*hashTable)->buckets[index], arrival);

}

void printList(Node* list)
{
	Node* temp = list;
	while (temp != NULL)
	{
		printArrival(temp->info);
		temp = temp->next;
	}
}

void printHash(Hash* hash)
{
	for (int i = 0; i < hash->size; i++)
	{
		printf("Bucket %d: ", i);
		printList(hash->buckets[i]);
		printf("\n");
	}
}

Arrival* lastArrival(Hash* hash, char* destination)
{
	int index = fhash(destination, hash->size);
	Node* temp = hash->buckets[index];

	Arrival* max = temp->info;

	while (temp != NULL)
	{
		if (strcmp(max->arrivalTime, temp->info->arrivalTime) < 0)
		{
			max = temp->info;
		}
		temp = temp->next;
	}

	return max;
}


int countDelays(Hash* hash)
{
	int count = 0;
	for (int i = 0; i < hash->size; i++)
	{
		Node* temp = hash->buckets[i];
		while (temp != NULL)
		{
			if (temp->info->delay > 0)
			{
				count++;
			}
			temp = temp->next;
		}
	}

	return count;
}


void changeDestination(Hash** hash, char* newDestination, unsigned short trainNo)
{
	for (int i = 0; i < (*hash)->size; i++)
	{
		Node* temp = (*hash)->buckets[i];
		Node* prev = NULL;

		while (temp != NULL)
		{
			if (temp->info->trainNo == trainNo)
			{
				if (prev == NULL)
				{
					(*hash)->buckets[i] = temp->next;
				}
				else
				{
					prev->next = temp->next;
				}

				free(temp->info->destination);
				temp->info->destination = (char*)malloc(strlen(newDestination) + 1);
				strcpy(temp->info->destination, newDestination);
				addHash(&(*hash), temp->info);

				free(temp);
				return;

			}

			prev = temp;
			temp = temp->next;
		}
	}
}
