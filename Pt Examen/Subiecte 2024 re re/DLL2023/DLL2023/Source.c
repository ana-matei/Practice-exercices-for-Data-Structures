#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFERSIZE 255


struct MutualFund
{
	char* mutualFundCode;
	char* mutualFundGroup;
	int riskLevel;
	double netAssetvalue;
	float returnOfInvestment;
};

typedef struct MutualFund Fund;

struct DoubleLinkedList
{
	Fund* info;
	struct DoubleLinkedList* next;
	struct DoubleLinkedList* prev;
};

typedef struct DoubleLinkedList Node;



Fund* createFund(char*, char*, int, double, float);
Node* createNode(Fund*);
void printFund(Fund*);
void insertList(Node**, Fund*);
void printList(Node*);
void printGainLoss(Node*);
Node* treshold(Node*, float);




int main()
{

	FILE* f = fopen("Data.txt", "r");
	Node* list = NULL;

	if (f)
	{

		char mutualFundCode[BUFFERSIZE];
		char mutualFundGroup[BUFFERSIZE];
		int riskLevel;
		double netAssetvalue;
		float returnOfInvestment;


		char* token = NULL;
		char* dlm = ",\n";
		char buffer[BUFFERSIZE];

		while (fgets(buffer, sizeof(buffer), f))
		{
			token = strtok(buffer, dlm);
			strcpy(mutualFundCode, token);

			token = strtok(NULL, dlm);
			strcpy(mutualFundGroup, token);

			token = strtok(NULL, dlm);
			riskLevel = atoi(token);

			token = strtok(NULL, dlm);
			netAssetvalue = atoi(token);

			token = strtok(NULL, dlm);
			returnOfInvestment = atof(token);

			Fund* fund = createFund(mutualFundCode, mutualFundGroup, riskLevel, netAssetvalue, returnOfInvestment);
			printFund(fund);

			insertList(&list, fund);

		}

		// ex 2
		printList(list);

		// ex 3
		int treshhold = coountRiskLevel(list, 3);
		printf("treshhold: %d", treshhold);

		// ex 4
		printGainLoss(list);

		// ex 5
		Node* fundTreshold = treshold(list, 1100);
		printFund(fundTreshold->info);
	}

}


Fund* createFund(char* mutualFundCode, char* mutualFundGroup, int riskLevel, double netAssetvalue, float returnOfInvestment)
{
	Fund* fund = (Fund*)malloc(sizeof(Fund));

	fund->mutualFundCode = (char*)malloc(strlen(mutualFundCode) + 1);
	strcpy(fund->mutualFundCode, mutualFundCode);

	fund->mutualFundGroup = (char*)malloc(strlen(mutualFundGroup) + 1);
	strcpy(fund->mutualFundGroup, mutualFundGroup);

	fund->riskLevel = riskLevel;
	fund->netAssetvalue = netAssetvalue;
	fund->returnOfInvestment = returnOfInvestment;

	return fund;
}

Node* createNode(Fund* fund)
{
	Node* node = (Node*)malloc(sizeof(Node));

	node->info = fund;
	node->next = NULL;
	node->prev = NULL;

	return node;
}

void printFund(Fund* fund)
{
	printf("Fund: %s, %s, %d, %5.2f, %5.2f\n", fund->mutualFundCode, fund->mutualFundGroup, fund->riskLevel, fund->netAssetvalue, fund->returnOfInvestment);
}


void insertList(Node** list, Fund* fund)
{
	Node* node = createNode(fund);

	if (*list == NULL)
	{
		*list = node;
	}
	else
	{
		node->next = *list;
		(*list)->prev = node;
		*list = node;
	}
}

void printList(Node* list)
{
	printf("In order: \n");
	while (list->next != NULL)
	{
		printFund(list->info);
		list = list->next;
	}
	printFund(list->info);

	printf("In reverse:\n");
	while (list->prev != NULL)
	{
		printFund(list->info);
		list = list->prev;
	}
	printFund(list->info);

}


int coountRiskLevel(Node* list, int riskLevel)
{

	int count = 0;
	while (list != NULL)
	{
		if (list->info->riskLevel > riskLevel)
		{
			count++;
		}
		list = list->next;
	}

	return count;
}

void printGainLoss(Node* list)
{
	while (list)
	{
		float gainLoss = list->info->returnOfInvestment - list->info->netAssetvalue;
		printf("%f\n", gainLoss);
		list = list->next;
	}
}

Node* treshold(Node* list, float treshold)
{
	while (list)
	{
		if (list->info->netAssetvalue > treshold)
		{
			return list;
		}
		list = list->next;
	}
}