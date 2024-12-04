#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX_L 1024


struct MutualFund {
	char* mutualFundCode;
	char* mutualFundGroup;
	int riskLevel;
	double netAssetValue;
	float returnOfInvestment;
};

typedef struct MutualFund MutualFund;

struct DoubleLinkedList {
	struct DoubleLinkedList* next;
	struct DoubleLinkedList* prev;
	MutualFund* info;
};

typedef struct DoubleLinkedList DLL;

MutualFund* createMutualFund(char*, char*, int, double, float);
DLL* createNode(MutualFund*);
DLL* insertNodeHead(DLL*);
DLL* insertNodeTail(DLL**, DLL*);
void printMutualFund(MutualFund*);
void printList(DLL*);
int countRisk(const float, const DLL*);
void displayGainLoss(DLL*);
MutualFund* FirstAboveTreshold(DLL*, double);


int main() {

	FILE* f = fopen("Data.txt", "r");
	DLL* list = NULL;

	if (f) {
		char mutualFundCode[MAX_L];
		char mutualFundGroup[MAX_L];
		int riskLevel;
		double netAssetValue;
		float returnOfInvestment;

		char* token = NULL;
		char* del = ",\n";
		char buffer[MAX_L];

		while (fgets(buffer, sizeof(buffer), f)) {
			token = strtok(buffer, del);
			strcpy(mutualFundCode, token);
			//printf("%s", mutualFundCode);

			token = strtok(NULL, del);
			strcpy(mutualFundGroup, token);
			//printf("%s ", mutualFundGroup);

			token = strtok(NULL, del);
			riskLevel = (int)atoi(token);
			//printf("%d ", riskLevel);

			token = strtok(NULL, del);
			netAssetValue = atof(token);
			//printf("%5.2f ",netAssetValue);

			token = strtok(NULL, del);
			returnOfInvestment = (float)atof(token);
			//printf("%5.2f\n", returnOfInvestment);

			MutualFund* mutualFund = createMutualFund(mutualFundCode, mutualFundGroup, riskLevel, netAssetValue, returnOfInvestment);
			DLL* node = createNode(mutualFund);
			//list = insertNodeHead(&list, node);
			list = insertNodeTail(&list, node);
			
		}

		// ex2
		printList(list);

		//ex3
		int risk = countRisk(5.00f, list);
		printf("risk: %d\n", risk);

		//ex4
		displayGainLoss(list);

		//ex 5
		MutualFund* mutualFundTr =FirstAboveTreshold(list, 1800);
		printMutualFund(mutualFundTr);

	}

	fclose(f);
}


MutualFund* createMutualFund(char* mutualFundCode, char* mutualFundGroup, int riskLevel, double netAssetValue, float returnOfInvestment) {
	MutualFund* mutualFund = (MutualFund*)malloc(sizeof(MutualFund));

	if (mutualFund) {
		mutualFund->mutualFundCode = (char*)malloc(strlen(mutualFundCode)+1);
		strcpy(mutualFund->mutualFundCode,mutualFundCode);

		mutualFund->mutualFundGroup = (char*)malloc(strlen(mutualFundGroup) + 1);
		strcpy(mutualFund->mutualFundGroup, mutualFundGroup);

		mutualFund->riskLevel = riskLevel;
		mutualFund->netAssetValue = netAssetValue;
		mutualFund->returnOfInvestment = returnOfInvestment;


	}

	return mutualFund;
}


DLL* createNode(MutualFund* mutualFund) {
	DLL* node = (DLL*)malloc(sizeof(DLL));

	if (node) {
		node->next = node->prev = NULL;
		node->info = mutualFund;
	}

	return node;
}

DLL* insertNodeHead(DLL** list, DLL* node) {

	if (*list == NULL)
	{
		*list = node;
	}
	else
	{
		node->next = (*list);
		(*list)->prev = node;
		(*list) = node;
	}

	return *list;

}


DLL* insertNodeTail(DLL** list, DLL* node) {
	if (*list == NULL)
	{
		*list = node;
	}
	else
	{
		DLL* temp = (*list);
		while (temp->next != NULL) {
			temp = temp->next;
		}

		temp->next = node;
		node->prev = temp;
	}

	return (*list);

}




void printMutualFund(MutualFund* mutualFund) {

	printf("mutualFundCode: %s  ", mutualFund->mutualFundCode);
	printf(" mutualFundGroup: %s  ", mutualFund->mutualFundGroup);
	printf("riskLevel: %d ", mutualFund->riskLevel);
	printf("netAssetValue: %5.2f ", mutualFund->netAssetValue);
	printf("returnOfInvestment: %5.2f\n", mutualFund->returnOfInvestment);

}

void printList(DLL* list) {
	printf("In order\n");
	while (list->next!=NULL) {
		printMutualFund(list->info);
		list = list->next;
	}
	printMutualFund(list->info);

	printf("In reverse: \n");
	while (list->prev != NULL ) {
		printMutualFund(list->info);
		list = list->prev;
	}
	printMutualFund(list->info);

}


int countRisk(const float risk,const DLL* list) {

	int count = 0;
	while (list) {
		if (list->info->riskLevel > risk)
		{
			count++;
		}
		list = list->next;
	}

	return count;
}


void displayGainLoss(DLL* list) {

	while (list) {
		printf("Mutual Fund code: %s:, gain/loss: %5.2f \n", list->info->mutualFundCode, list->info->netAssetValue * list->info->returnOfInvestment);
		list = list->next;
	}

}

MutualFund* FirstAboveTreshold(DLL* list, double treshold) {
	MutualFund* fund = NULL;
	while (list) {
		if (list->info->netAssetValue > treshold)
		{
			fund = list->info;
			return fund;
		}
		list = list->next;
	}

}