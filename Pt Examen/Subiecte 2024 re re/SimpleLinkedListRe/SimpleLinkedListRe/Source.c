#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFERSIZE 255

struct Flight
{
	char* flightCode;
	unsigned int passagersNo;
	char* ETA;
	unsigned int flightTime;
};

typedef struct Flight Flight;

struct SimpleLinkedList
{
	Flight* info;
	struct SimpleLinkedList* next;
};

typedef struct SimpleLinkedList Node;


Flight* createFlight(char*, unsigned int, char*, unsigned int);
void printFligt(Flight*);
Node* createNode(Flight*);
void createList(Node**, Flight*);
void printList(Node*);
int countFlights(Node*, unsigned int);
float averagePassangers(Node*, const char*);
void returnTime(Node*, const char*);




int main()
{
	FILE* f = fopen("Data.txt", "r");
	Node* list = NULL;
	Node* list2 = NULL;

	if (f)
	{
		char flightCode[BUFFERSIZE];
		unsigned int passagersNo;
		char ETA[BUFFERSIZE];
		unsigned int flightTime;

		char buffer[BUFFERSIZE];
		char* token = NULL;
		char* dlm = ",\n";

		while (fgets(buffer, sizeof(buffer), f))
		{
			token = strtok(buffer, dlm);
			strcpy(flightCode, token);

			token = strtok(NULL, dlm);
			passagersNo = atoi(token);

			token = strtok(NULL, dlm);
			strcpy(ETA, token);

			token = strtok(NULL, dlm);
			flightTime = atoi(token);

			Flight* flight = createFlight(flightCode, passagersNo, ETA, flightTime);
			//printFligt(flight);
			createList(&list, flight);
			createList(&list2, flight);
		}

	
		// ex 2
		printList(list);

		// ex 3
		int count = countFlights(list2, 100);
		printf("No of flights with the flight time greater than %d\n", count);

		// ex4 
		float average = averagePassangers(list2, "16:00");
		printf("average %5.2f\n", average);

		//ex 5
		returnTime(list2, "5");
	}


}

Flight* createFlight(char* flightCode, unsigned int passagersNo, char* ETA, unsigned int flightTime)
{
	Flight* flight = (Flight*)malloc(sizeof(Flight));

	flight->flightCode = (char*)malloc(strlen(flightCode) + 1);
	strcpy(flight->flightCode, flightCode);

	flight->passagersNo = passagersNo;

	flight->ETA = (char*)malloc(strlen(ETA) + 1);
	strcpy(flight->ETA, ETA);

	flight->flightTime = flightTime;

	return flight;
}

void printFligt(Flight* flight)
{
	printf("Flight: %s, %d, %s, %d\n", flight->flightCode, flight->passagersNo, flight->ETA, flight->flightTime);
}

Node* createNode(Flight* flight)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->info = flight;
	node->next = NULL;
	return node;
}

void createList(Node** list, Flight* flight)
{
	Node* node = createNode(flight);
	if (*list == NULL)
	{
		*list = node;
	}
	else
	{
		if (strcmp((*list)->info->ETA, flight->ETA) > 0)
		{
			node->next = (*list);
			(*list) = node;
		}
		else {
			Node* temp = *list;
			while (temp->next != NULL && strcmp(temp->next->info->ETA, flight->ETA) < 0)
			{
				temp = temp->next;
			}
			node->next = temp->next;
			temp->next = node;
		}
	}
}


// print list in reverse
void printList(Node* list)
{
	Node* prev = NULL;
	Node* current = list;
	Node* next = NULL;

	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
		
	}

	current = prev;

	while (current)
	{
		printFligt(current->info);
		current = current->next;
	}

	// recursively printing the list, dude that't the best fucking idea
	//	if (list == NULL) {
	//		return;
	//	}

	//	printList(list->next);
	//	printFligt(list->info);
	//}	
}

int countFlights(Node* list, unsigned int flightTime)
{
	int count = 0;

	while (list != NULL)
	{
		if (list->info->flightTime > flightTime)
		{
			count++;
		}
		list = list->next;
	}
	return count;
}


float averagePassangers(Node* list, const char* time)
{
	int sum = 0;
	int count = 0;
	while (list != NULL)
	{
		if (strcmp(list->info->ETA, time) < 0)
		{
			count++;
			sum += list->info->passagersNo;
		}
		list = list->next;
	}

	return (float)sum / count;
}

void returnTime(Node* list, const char* flightCode)
{
	while (list->next != NULL)
	{
		if (strcmp(list->info->flightCode, flightCode) == 0)
		{
			int etaHours, etaMinutes;
			sscanf(list->info->ETA, "%2d:%2d", &etaHours, &etaMinutes);
			int etaTotalMinutes = etaHours * 60 + etaMinutes;
			int departureTotalMinutes = etaTotalMinutes - list->info->flightTime;
			if (departureTotalMinutes < 0) {
				departureTotalMinutes += 24 * 60; // Wrap around if negative
			}
			unsigned int departureHours = departureTotalMinutes / 60;
			unsigned int departureMinutes = departureTotalMinutes % 60;
			printf("Departure time for flight %s: %02u:%02u\n", flightCode, departureHours, departureMinutes);
			return;
		}
		list = list->next;
	}
	printf("Flight with code %s not found.\n", flightCode);
}