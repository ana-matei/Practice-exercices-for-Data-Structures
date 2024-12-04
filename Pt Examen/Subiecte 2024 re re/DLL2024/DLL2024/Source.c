#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUFFERSIZE 255
#define HASHSIZE 12



struct Request
{
	unsigned int id;
	unsigned int size;
	unsigned short prioriry;
	char* sourceIp;
	char* destinationIp;
};

typedef struct Request Request;

struct DobleLinkedList
{
	Request* info;
	struct DobleLinkedList* next;
	struct DobleLinkedList* prev;

};

typedef struct DobleLinkedList Node;

//struct SimpleLinkedList
//{
//	char* info;
//	struct SimpleLinkedList* next;
//};
//
//typedef struct SimpleLinkedList NodeH;
//
//struct IpHash
//{
//	NodeH** sIP;
//	int size;
//};
//
//typedef struct IpHash IpHash;




Request* createRequest(unsigned int, unsigned int, unsigned short, char*, char*);
void printRequest(Request*);
Node* createNode(Request*);
void insertList(Node**, Request*);
void printList(Node*);
void countRequests(Node*);
//IpHash* createNodeHash(Node*);
//void addNodeH(NodeH**, Node*);
//int fhash(char*, int);
//void addHash(IpHash**, Node*);
//void printHash(IpHash*);
void changePriority(Node**, int, int);
void deleteNode(Node**);
void deleteRequest(Node**, char*);






int main()
{
	FILE* f = fopen("Data.txt", "r");
	Node* list = NULL;
	//IpHash* hash = NULL;

	if (f)
	{
		unsigned int id;
		unsigned int size;
		unsigned short prioriry;
		char sourceIp[BUFFERSIZE];
		char destinationIp[BUFFERSIZE];

		char* token = NULL;
		char* dlm = ",\n";
		char buffer[BUFFERSIZE];


		while (fgets(buffer, sizeof(buffer), f))
		{
			token = strtok(buffer, dlm);
			id = atoi(token);

			token = strtok(NULL, dlm);
			size = atoi(token);

			token = strtok(NULL, dlm);
			prioriry = atoi(token);

			token = strtok(NULL, dlm);
			strcpy(sourceIp, token);

			token = strtok(NULL, dlm);
			strcpy(destinationIp, token);

			Request* request = createRequest(id, size, prioriry, sourceIp, destinationIp);
			printRequest(request);

			//ex 1
			insertList(&list, request);
			//addHash(&hash, list);
		}

		

	}

	// ex2
	printf("\n");
	printList(list);

	// ex 3
	printf("\n");
	countRequests(list);


	//ex 3 dar cu hash
	//printHash(hash);

	// ex 4
	printf("\n");
	changePriority(&list, 33, 2);
	printList(list);

	// ex 5
	printf("\n");
	deleteRequest(&list, "192.25");
	printList(list);



	
}

Request* createRequest(unsigned int id, unsigned int size, unsigned short prioriry, char* sourceIp, char* destinationIp)
{
	Request* request = (Request*)malloc(sizeof(Request));

	request->id = id;
	request->size = size;
	request->prioriry = prioriry;

	request->sourceIp = (char*)malloc(strlen(sourceIp) + 1);
	strcpy(request->sourceIp, sourceIp);
	request->destinationIp = (char*)malloc(strlen(destinationIp)+1);
	strcpy(request->destinationIp, destinationIp);

	return request;
}

void printRequest(Request* request)
{
	printf("Request: %d, %d, %d, %s, %s\n", request->id, request->size, request->prioriry, request->sourceIp, request->destinationIp);
}

Node* createNode(Request* request)
{
	Node* node = (Node*)malloc(sizeof(Node));

	node->info = request;
	node->next = NULL;
	node->prev = NULL;

	return node;
}


void insertList(Node** list, Request* request)
{
	Node* node = createNode(request);
	

	if ((*list) == NULL)
	{
		(*list) = node;
	}
	else if ((*list)->info->size < request->size)
	{
		node->next = (*list);
		(*list)->prev = node;
		(*list) = node;
	}
	else
	{
		Node* temp = *list;
		while (temp->next != NULL && temp->next->info->size > request->size)
		{
			temp = temp->next;
		}

		node->next = temp->next;
		node->prev = temp;

		if (temp->next != NULL)
		{
			temp->next->prev = node;
		}
		temp->next = node;
		
		
	}

}

void printList(Node* list)
{
	while (list != NULL)
	{
		printRequest(list->info);
		list = list->next;
	}
}

// idk prima varianta
//void countRequests(Node* list)
//{
//	int capacity = 10;
//	bool found = 0;
//	Node* temp = list;
//	char** uniqueIp = (char**)malloc(sizeof(char*)*capacity);
//	for (int i = 0; i < capacity; i++)
//	{
//		uniqueIp[i] = (char*)malloc(sizeof(char) * BUFFERSIZE);
//	}
//
//	//int* array = (int*)malloc(sizeof(int)*10);
//	//memset(array, 0, sizeof(array));
//
//	while (temp != NULL)
//	{
//		int i = 0;
//		for (i = 0; i < capacity; i++)
//		{
//			if (strcmp(uniqueIp[i], temp->info->sourceIp) == 0)
//			{
//				//array[i]++;
//				found = 1;
//				break;
//			}	
//		}
//
//		if (found == 0)
//		{
//			if (capacity > (i + 1))
//			{
//				strcpy(uniqueIp[i + 1], temp->info->sourceIp);
//			}
//			else
//			{
//				//int initialSize = sizeof(array);
//				uniqueIp = (char**)realloc(uniqueIp, (capacity * sizeof(char)) + sizeof(uniqueIp));
//				for (int i = 0; i < capacity; i++)
//				{
//					uniqueIp[i] = (char*)malloc(sizeof(char) * BUFFERSIZE);
//				}
//				//array = (int*)realloc(array, (sizeof(int) * 10) + sizeof(array));
//				//memset(array + initialSize, 0, sizeof(array));
//				strcpy(uniqueIp[i + 1], temp->info->sourceIp);
//				//array[i + 1] = 1;
//				capacity += capacity;
//			}
//		}
//
//		temp = temp->next;
//	}
//
//	for (int i = 0; i < sizeof(*uniqueIp); i++)
//	{
//		printf("%s", uniqueIp[i]);
//	}
//	
//	//return array;
//}


// varianta mea revizuita cu vectori cu frecventa
void countRequests(Node* list)
{
	int capacity = 5;
	Node* temp = list;
	char** uniqueIp = (char**)malloc(sizeof(char*) * capacity);
	int* countIP = (int*)malloc(sizeof(int) * capacity);
	memset(countIP, 0, sizeof(countIP));
	for (int i = 0; i < capacity; i++)
	{
		uniqueIp[i] = (char*)malloc(sizeof(char) * BUFFERSIZE);
		uniqueIp[i][0] = '\0';
	}


	int count = 0;

	while (temp != NULL)
	{
		bool found = false;
		int i = 0;
		for (i = 0; i < count; i++)
		{
			if (strcmp(uniqueIp[i], temp->info->sourceIp) == 0)
			{
				found = true;
				countIP[i]++;
				break;
			}
		}

		if (found == false)
		{
			if (count >= capacity)
			{
				capacity += capacity;
				uniqueIp = (char**)realloc(uniqueIp, sizeof(char*) * capacity);
				for (int i = count; i < capacity; i++)
				{
					uniqueIp[i] = (char*)malloc(sizeof(char) * BUFFERSIZE);
					uniqueIp[i][0] = '\0';
				}
				countIP = (int*)realloc(countIP, sizeof(int) * capacity);
				memset(countIP + count, 0, sizeof(int) * (capacity - count));
				strcpy(uniqueIp[count], temp->info->sourceIp);
				countIP[count] = 1;
				count++;


			}
			else
			{
				strcpy(uniqueIp[count], temp->info->sourceIp);
				countIP[count] = 1;
				count++;
			}
		}
		temp = temp->next;
	}

	for (int i = 0; i < count; i++)
	{
		printf("%s, %d\n", uniqueIp[i], countIP[i]);
	}
}


void changePriority(Node** list, int requestId, int priority)
{
	Node* temp = *list;
	while (temp != NULL)
	{
		if (temp->info->id == requestId)
		{
			temp->info->prioriry = priority;
		}
		temp = temp->next;
	}
}

void deleteNode(Node** node)
{
	free((*node)->info->sourceIp);
	free((*node)->info->destinationIp);
	free((*node)->info);
	free(*node);
}

void deleteRequest(Node** list, char* destinationIp)
{
	Node* temp = *list;
	if (strcmp(temp->info->destinationIp, destinationIp) == 0 && temp->prev == NULL)
	{
		Node* current = temp;
		temp = current->next;
		temp->prev = NULL;
		*list = temp;
		deleteNode(&current);
	}
	else
	{
		while (temp != NULL)
		{
			if (strcmp(temp->info->destinationIp, destinationIp) == 0)
			{
				Node* current = temp;
				temp->prev->next = temp->next;
				temp->next = current->next->next;
				deleteNode(&current);
				temp = temp->next;
			}
			else
			{
				temp = temp->next;
			}
		}
	}	
}

// all the hash functions don't really help, they are kinda fine but not really

//void addHash(IpHash** hash, Node* list)
//{
//	if (*hash == NULL)
//	{
//		*hash = (IpHash*)malloc(sizeof(IpHash));
//		(*hash)->size = HASHSIZE;
//		(*hash)->sIP = (NodeH**)malloc((*hash)->size * sizeof(NodeH*));
//		for (int i = 0; i < HASHSIZE; i++)
//		{
//			(*hash)->sIP[i] = NULL;
//		}
//	}
//	else
//	{
//		int index = fhash(list->info->sourceIp, (*hash)->size);
//		addNodeH(&(*hash)->sIP[index], list);
//	}
//}
//
//int fhash(char* key, int size)
//{
//	unsigned int sum = 0;
//	for (int i = 0; key[i] != '\0'; i++)
//	{
//		sum += key[i];
//	}
//	return sum % size;
//}
//
//void addNodeH(NodeH** listH, Node* list)
//{
//	NodeH* nodeH = createNodeHash(list);
//	if (*listH == NULL)
//	{
//		*listH = nodeH;
//	}
//	else
//	{
//		nodeH->next = *listH;
//		*listH = nodeH;
//	}
//}
//
//IpHash* createNodeHash(Node* list)
//{
//	NodeH* node = (NodeH*)malloc(sizeof(NodeH));
//	node->info = (char*)malloc(strlen(list->info->sourceIp)+1);
//	strcpy(node->info, list->info->sourceIp);
//	node->next = NULL;
//
//	return node;
//	
//}
//
//
//void printHash(IpHash* hashTable)
//{
//	for (int i = 0; i < hashTable->size; i++)
//	{
//		int count = 0;
//		NodeH* node = hashTable->sIP[i];
//		while (node != NULL)
//		{
//			printf("unique ip %s:", hashTable->sIP[i]->info);
//			count++;
//			node = node->next;
//		}
//		printf("Bucket %d: %d unique IPs, ip: %s\n", i, count);
//	}
//}
//
//
