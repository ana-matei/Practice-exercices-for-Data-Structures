//#define _CRT_SECURE_NO_WARNINGS
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//#define HSIZE 30
//#define BUFFERSIZE 255
//
//typedef struct Arrival {
//	unsigned short trainNo;
//	char* destination;
//	char* arrivalTime; //HH:MM
//	unsigned short delay;
//	unsigned short noOfPassengers;
//};
//
//typedef struct Arrival Arrival;
//
//struct SimpleLinkList {
//	Arrival* info;
//	struct SimpleLinkList* next;
//};
//
//typedef struct SimpleLinkList Node;
//
//struct HTable {
//	Node* buckets;
//	int size;
//};
//
//typedef struct HTable HT;
//
//
//Arrival* createArrival(unsigned short, char*, char*, unsigned short, unsigned short);
//Node* createNode(Arrival*);
//Node* addNode(Node**, Arrival*);
//int fHash(const char*, int);
//HT* addHT(HT**, Arrival*);
//void printArrival(Arrival*);
//void printList(Node*);
//void printHT(HT*);
//
//int main() {
//
//
//	FILE* f = fopen("Data.txt", "r");
//	Node* list = NULL;
//	HT* hashTable = NULL;
//
//	if (f) {
//
//		unsigned short trainNo;
//		char destination[BUFFERSIZE];
//		char arrivalTime[6]; //HH:MM
//		unsigned short delay;
//		unsigned short noOfPassengers;
//
//		char* delim = ",\n";
//		char* token = NULL;
//		char buffer[BUFFERSIZE];
//
//		while (fgets(buffer, sizeof(buffer), f)) {
//
//			token = strtok(buffer, delim);
//			trainNo = atoi(token);
//
//			token = strtok(NULL, delim);
//			strcpy(destination, token);
//
//			token = strtok(NULL, delim);
//
//			strcpy(arrivalTime, token);
//
//			token = strtok(NULL, delim);
//			delay = atoi(token);
//
//			token = strtok(NULL, delim);
//			noOfPassengers = atoi(token);
//
//
//			Arrival* arrival = createArrival(trainNo, destination, arrivalTime, delay, noOfPassengers);
//			printArrival(arrival);
//			//list = addNode(&list, arrival);
//			hashTable = addHT(&hashTable, arrival);
//			
//
//		}
//
//		//printHT(hashTable);
//	}
//
//}
//
//
//Arrival* createArrival(unsigned short trainNo, char* destination, char* arrivalTime, unsigned short delay, unsigned short noOfPassengers)
//{
//	Arrival* arrival = (Arrival*)malloc(sizeof(Arrival));
//
//	arrival->trainNo = trainNo;
//	arrival->destination = (char*)malloc(strlen(destination) + 1);
//	strcpy(arrival->destination, destination);
//	arrival->arrivalTime = (char*)malloc(strlen(arrivalTime) + 1);
//	strcpy(arrival->arrivalTime, arrivalTime);
//	arrival->delay = delay;
//	arrival->noOfPassengers = noOfPassengers;
//
//	return arrival;
//}
//
//
//Node* createNode(Arrival* arrival) {
//	Node* node = (Node*)malloc(sizeof(Node));
//	node->info = arrival;
//	node->next = NULL;
//
//	return node;
//}
//
//
//Node* addNode(Node** list, Arrival* arrival) {
//
//	Node* node = createNode(arrival);
//	if (*list == NULL) {
//		*list = node;
//	}
//	else {
//		node->next = *list;
//		*list = node;
//	}
//
//	return *list;
//}
//
//int fHash(const char* destination, int size) {
//	int hash = 0;
//	while (*destination) {
//		hash = hash + (*destination);
//		destination++;
//	}
//
//	return hash % size;
//	
//}
//
//HT* addHT(HT** ht, Arrival* arrival) {
//
//	if ((*ht) == NULL) {
//		*ht = (HT*)malloc(sizeof(HT));
//		(*ht)->size = HSIZE;
//		(*ht)->buckets = (Node**)malloc((*ht)->size * sizeof(Node*));
//		memset((*ht)->buckets, 0, (*ht)->size * sizeof(Node));
//	}
//
//	if (*ht)
//	{
//		int index = fHash(arrival->destination, HSIZE);
//		(*ht)->buckets[index] = addNode(&(*ht)->buckets[index], arrival);
//	}
//	return *ht;
//}
//
//void printArrival(Arrival* arrival) {
//	printf("%d, %s, %s, %d, %d", arrival->trainNo, arrival->destination, arrival->arrivalTime, arrival->delay, arrival->noOfPassengers);
//}
//
//
//void printList(Node* list) {
//	Node* temp = list;
//
//	while (temp) {
//		printArrival(temp->info);
//		temp = temp->next;
//	}
//}
//
//void printHT(HT* ht) {
//	for (int i = 0; i < ht->size; i++) 
//	{
//		printList(&ht->buckets[i]);
//		printf("\n");
//
//	}
//}
//
//
//













#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFERSIZE 255
#define HSIZE 20



struct Arrival {
	unsigned short trainNo;
	char* destination;
	char* arrivalTime; // HH:MM
	unsigned short delay;
	unsigned short noPassengers;
};
typedef struct Arrival Arrival;

struct SimpleLinkList {
	Arrival* info;
	struct SimpleLinkList* next;
};
typedef struct SimpleLinkList Node;

struct HTable {
	Node** buckets;
	int size;
};

typedef struct HTable HT;


Arrival* createArrival(unsigned short, char*, char*, unsigned short, unsigned short);
Node* createNode(Arrival*);
void addNode(Node**, Arrival*);
int fHash(const char*, int);
void addHT(HT**, Arrival*);
void printArrival(Arrival*);
void printList(Node*);
void printHT(HT*);
Arrival* lastArrival(HT*, const char*);
int countDelays(HT*);
void changeDestination(HT**, int, const char*);



int main()
{

	FILE* f = fopen("Data.txt", "r");

	Node* list = NULL;
	HT* hashTable = NULL;

	if (f) {
		unsigned short trainNo;
		char destination[BUFFERSIZE];
		char arrivalTime[6];
		unsigned short delay;
		unsigned short noPassengers;

		char buffer[BUFFERSIZE];
		char* token = NULL;
		char* dlm = ",\n";


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
			noPassengers = atoi(token);

			Arrival* arrival = createArrival(trainNo, destination, arrivalTime, delay, noPassengers);
			addNode(&list, arrival);
			//printArrival(arrival);
			addHT(&hashTable, arrival);

		}
	}


	// ex 2
	printHT(hashTable);


	// ex 3
	Arrival* ar = lastArrival(hashTable, "Bucuresti");
	printf("Last Arrival");
	printArrival(ar);

	//ex 4 
	int noDelays = countDelays(hashTable);
	printf("No of delays are %d\n", noDelays);
	printf("\n");

	// ex 5
	printHT(hashTable);
	changeDestination(&hashTable, 1, "Brasov");
	printf("\n");
	printHT(hashTable);

	
	fclose(f);


}




Arrival* createArrival(unsigned short trainNo, char* destination, char* arrivalTime, unsigned short delay, unsigned short noPassengers)
{
	Arrival* arrival = (Arrival*)malloc(sizeof(Arrival));

	arrival->trainNo = trainNo;

	arrival->destination = (char*)malloc(strlen(destination) + 1);
	strcpy(arrival->destination, destination);

	arrival->arrivalTime = (char*)malloc(strlen(arrivalTime) + 1);
	strcpy(arrival->arrivalTime,arrivalTime);

	arrival->delay = delay;
	arrival->noPassengers = noPassengers;

	return arrival;
}

Node* createNode(Arrival* arrival) {
	Node* node = (Node*)malloc(sizeof(Node));

	node->info = arrival;
	node->next = NULL;

	return node;
}

void addNode(Node** list, Arrival* arrival)
{
	Node* node = createNode(arrival);

	if (*list == NULL)
	{
		*list = node;
	}
	else
	{
		node->next = *list;
		*list = node;
	}
	
}


int fHash(const char* destination, int size) {
	int hash = 0; 
	while (*destination) {
		hash = hash + (*destination);
		destination++;
	}

	return hash % size;
}

void addHT(HT** hashTable, Arrival* arrival)
{
	if (*hashTable == NULL)
	{
		(*hashTable) = (HT*)malloc(sizeof(HT));
		(*hashTable)->size = HSIZE;
		(*hashTable)->buckets = (Node**)malloc((*hashTable)->size * sizeof(Node*));
		memset((*hashTable)->buckets, 0, (*hashTable)->size * sizeof(Node*));
	}

	if (*hashTable) {
		int index = fHash(arrival->destination, (*hashTable)->size);
		addNode(&(*hashTable)->buckets[index], arrival);
	}

}


void printArrival(Arrival* arrival)
{
	printf("%d, %s, %s, %d, %d\n", arrival->trainNo, arrival->destination, arrival->arrivalTime, arrival->delay, arrival->noPassengers);
}


void printList(Node* list)
{
	Node* temp = list;

	while (temp)
	{
		printArrival(temp->info);
		temp = temp->next;
	}
}

void printHT(HT* hashTable)
{
	for (int i = 0; i < hashTable->size; i++)
	{
		printList(hashTable->buckets[i]);
	}
}


Arrival* lastArrival(HT* hashTable, const char* destination)
{
	//Arrival* finalAr = (Arrival*)malloc(sizeof(Arrival));
	Arrival* max = (Arrival*)malloc(sizeof(Arrival));

	int index = fHash(destination, hashTable->size);

	Node* node = hashTable->buckets[index];
	max = hashTable->buckets[index]->info;

	while (node)
	{
		if (strcmp(max->arrivalTime, node->info->arrivalTime) < 0)
		{
			max = node->info;
		}
		node = node->next;
	}

	return max;	
	
}

int countDelays(HT* hashTable)
{
	int count = 0;
	for (int i=0; i < hashTable->size; i++)
	{
		Node* n = hashTable->buckets[i];
		while (n != NULL)
		{
			if (n->info->delay != 0)
				count++;

			n = n->next;
		}
		
	}

	return count;
}


void changeDestination(HT** hashTable, int trainNo, const char* destination)
{
	//int index = fHash(destination, (*hashTable)->size);

	for (int i = 0; i < (*hashTable)->size; i++)
	{
		Node* n = (*hashTable)->buckets[i];
		while (n)
		{
			if (n->info->trainNo == trainNo)
			{
				strcpy(n->info->destination, destination);
			}
			n = n->next;
		}
	}
}


