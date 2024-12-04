#define	_CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define BUFFERSIZE 255


struct File
{
	char* id;
	unsigned int size;
	bool isReadOnly;
	char* date;
	char* owner;
};

typedef struct File File;

struct BinarySearchTree
{
	File* info;
	struct BinarySearchTree* left;
	struct BinarySearchTree* right;
};

typedef struct BinarySearchTree BST;


File* createFile(char*, unsigned int, bool, char*, char*);
void printFile(File*);
BST* insertNode(BST*, File*);
void printBSTinOrder(BST*);
void printPostOrder(BST*);
void printPreOrder(BST*);
void print(BST*, char*);
int countReadOnly(BST*);
void averageParamSize(BST*, int*, int*);
void averageSize(BST*);
//float averageSize(BST*);
void increaseSize(BST*, char*);
void deleteFile(File**);
BST* deleteNodeByKey(BST*, char*);




int main()
{
	FILE* f = fopen("Data.txt", "r");
	BST* bst = NULL;

	if (f)
	{
		char id[BUFFERSIZE];
		unsigned int size;
		bool isReadOnly;
		char date[BUFFERSIZE];
		char owner[BUFFERSIZE];

		char* token = NULL;
		char* dlm = ",\n";
		char buffer[BUFFERSIZE];

		while (fgets(buffer, sizeof(buffer), f))
		{
			token = strtok(buffer, dlm);
			strcpy(id, token);

			token = strtok(NULL, dlm);
			size = atoi(token);

			token = strtok(NULL, dlm);
			if (strcmp(token, "true") == 0)
			{
				isReadOnly = true;
			}
			else if (strcmp(token, "false") == 0)
			{
				isReadOnly = false;
			}

			token = strtok(NULL, dlm);
			strcpy(date, token);

			token = strtok(NULL, dlm);
			strcpy(owner, token);

			File* file = createFile(id, size, isReadOnly, date, owner);
			printFile(file);

			// ex 1
			bst = insertNode(bst, file);
		}

	}

	// ex 2 intermediar
	printf("\n");
	printf("ex 2 \n\n");
	printBSTinOrder(bst);

	printf("\n");
	printPostOrder(bst);

	printf("\n");
	printPreOrder(bst);

	// ex 2
	printf("ex 2\n");
	print(bst, "2022/05/08");

	// ex 3
	int noReadOnly = countReadOnly(bst);
	printf("\n No of read only files: %d", noReadOnly);

	// ex 4
	printf("\n");
	averageSize(bst);
	//float average = averageSize(bst);
	//printf("average %f", average);

	// ex 5
	printf("\n");
	increaseSize(bst, "13");
	printBSTinOrder(bst);

	// deletion of a node by key
	BST* bst2 = deleteNodeByKey(bst, "14");
	printf("\n");
	printBSTinOrder(bst2);
}


File* createFile(char* id, unsigned int size, bool isReadOnly, char* date, char* owner)
{
	File* file = (File*)malloc(sizeof(File));

	file->id = (char*)malloc(strlen(id) + 1);
	strcpy(file->id, id);

	file->size = size;
	file->isReadOnly = isReadOnly;

	file->date = (char*)malloc(strlen(date) + 1);
	strcpy(file->date, date);

	file->owner = (char*)malloc(strlen(owner) + 1);
	strcpy(file->owner, owner);

	return file;

}

void printFile(File* file)
{
	printf("File: %s, %d, %d, %s, %s\n", file->id, file->size, file->isReadOnly, file->date, file->owner);
}


BST* createNode(File* file)
{
	BST* bst = (BST*)malloc(sizeof(BST));
	bst->info = file;
	bst->left = NULL;
	bst->right = NULL;

	return bst;
}

BST* insertNode(BST* bst, File* file)
{
	if (bst == NULL)
	{
		return createNode(file);
	
	}
	else if (strcmp(bst->info->id, file->id) > 0)
	{
		bst->left = insertNode(bst->left, file);
	}
	else if (strcmp(bst->info->id, file->id) < 0)
	{
		bst->right = insertNode(bst->right, file);
	}
	return bst;
}


void printBSTinOrder(BST* bst)
{
	
	if (bst != NULL)
	{
		printBSTinOrder(bst->left);
		printFile(bst->info);
		printBSTinOrder(bst->right);
	}

}

void printPostOrder(BST* bst)
{
	
	if (bst != NULL)
	{	
		printBSTinOrder(bst->left);
		printBSTinOrder(bst->right);
		printFile(bst->info);
	}
}

void printPreOrder(BST* bst)
{
	if (bst != NULL)
	{
		printFile(bst->info);
		printBSTinOrder(bst->left);
		printBSTinOrder(bst->right);
	}
}


void print(BST* root, char* date)
{
	if (root != NULL)
	{
		print(root->left, date);
		if (strcmp(root->info->date, date) > 0)
		{
			printFile(root->info);
			
		}
		print(root->right, date);
	}
}


int countReadOnly(BST* root)
{
	int count = 0;
	if (root != NULL)
	{
		if (root->info->isReadOnly == true)
		{
			count = 1;
		}
	}
	else
	{
		return 0;
	}

	return count + countReadOnly(root->left)+ countReadOnly(root->right);
}

void averageParamSize(BST* root, int* sum, int* count)
{

	if (root != NULL)
	{
		(*count)++;
		*sum = *sum + root->info->size;
		averageParamSize(root->left, sum, count);
		averageParamSize(root->right, sum, count);
	}
}


void averageSize(BST* root)
{
	int sum = 0;
	int count = 0;
	averageParamSize(root, &sum, &count);
	if (count == 0)
	{
		printf("No files");
	}
	else
	{
		float average = (float)sum / count;
		printf("%d, %d ", sum, count);
		printf("Average size: %5.2f", average);
	}
}


void increaseSize(BST* root, char* id)
{
	if (root != NULL)
	{
		return;
	}
		
	if (strcmp(root->info->id, id) == 0)
	{
		return;
	}
	root->info->size = root->info->size + root->info->size;
	increaseSize(root->left, id);
	increaseSize(root->right, id);
}


void deleteFile(File** file)
{
	free((*file)->id);
	free((*file)->date);
	free((*file)->owner);
	free(*file);
}

//void deleteNodeByKey(BST** root, char* key)
//{
//	// base case
//	if ((*root) == NULL)
//	{
//		return;
//	}
//
//	//when we need to move down the tree
//	if (strcmp((*root)->info->id, key) < 0)
//	{
//		deleteNodeByKey(&(*root)->left, key);
//	}
//	else if (strcmp((*root)->info->id, key) > 0)
//	{
//		deleteNodeByKey(&(*root)->right, key);
//	}
//	else
//	{
//		//when we find the node and has a leaf or no leaf
//		if ((*root)->left == NULL)
//		{
//			BST* temp = (*root)->right;
//			deleteFile(&(*root)->info);
//			free((*root));
//			*root = temp;
//		}
//		else if ((*root)->right == NULL)
//		{
//			BST* temp = (*root)->left;
//			deleteFile(&(*root)->info);
//			free((*root));
//			*root = temp;
//		}
//		else
//		{
//			// node with 2 leafs
//			BST* current = (*root)->right;
//			while (current->left != NULL)
//			{
//				current = current->left;
//			}
//
//			free((*root)->info->id);
//			free((*root)->info->date);
//			free((*root)->info->owner);
//
//
//			(*root)->info->id = (char*)malloc(strlen(current->info->id) + 1);
//			(*root)->info->date = (char*)malloc(strlen(current->info->date) + 1);
//			(*root)->info->owner = (char*)malloc(strlen(current->info->owner) + 1);
//
//			strcpy((*root)->info->id, current->info->id);
//			strcpy((*root)->info->date, current->info->date);
//			strcpy((*root)->info->owner, current->info->owner);
//			(*root)->info->isReadOnly = current->info->isReadOnly;
//			(*root)->info->size = current->info->size;
//
//			deleteNodeByKey(&(*root)->right, current->info->id);
//
//		}
//	}
//}


BST* deleteNodeByKey(BST* root, char* key)
{
	// base case
	if (root == NULL)
	{
		return root;
	}

	// traverse the bst
	if (strcmp(root->info->id, key) > 0)
	{
		root->left = deleteNodeByKey(root->left, key);
	}
	else if (strcmp(root->info->id, key) < 0)
	{
		root->right = deleteNodeByKey(root->right, key);
	}
	else if (strcmp(root->info->id, key) == 0)
	{
		// we find the node now

		// the node has a leaf or no leaves
		if (root->left == NULL)
		{
			BST* temp = root->right;
			deleteFile(&root->info);
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			BST* temp = root->left;
			deleteFile(&root->info);
			free(root);
			return temp;
		}
		else
		{
			// if the node has 2 leafs
			BST* temp = root->right;
			while (temp->left != NULL)
			{
				temp = temp->left;
			}

			free(root->info->id);
			free(root->info->date);
			free(root->info->owner);

			root->info->id = (char*)malloc(strlen(temp->info->id) + 1);
			root->info->date = (char*)malloc(strlen(temp->info->date) + 1);
			root->info->owner = (char*)malloc(strlen(temp->info->owner) + 1);

			strcpy(root->info->id, temp->info->id);
			strcpy(root->info->date, temp->info->date);
			strcpy(root->info->owner, temp->info->owner);
			root->info->isReadOnly = temp->info->isReadOnly;
			root->info->size = temp->info->size;

			root->right = deleteNodeByKey(root->right, temp->info->id);
		}
	}
	return root;
}









