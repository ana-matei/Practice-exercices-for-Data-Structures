
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUFFERSIZE 255
#define HSIZE 10


struct File
{
	char* name;
	unsigned int size;
	bool isReadOnly;
	char* date;
	char* owner;
};

typedef struct File File;


struct BinarySearchTree
{
	File* info;
	struct BinarySearchTree* right;
	struct BinarySearchTree* left;
};

typedef struct BinarySearchTree BST;


struct SimpleLinkedList
{
	File* info;
	struct SimpleLinkedList* next;
};

typedef struct SimpleLinkedList Node;

struct HashTable
{
	Node** buckets;
	int size;
};

typedef struct HashTable Hash;


File* createFile(char*, unsigned int, bool, char*, char*);
void printFile(File*);
BST* createNode(File*);
BST* insertBST(BST*, File*);
void printBSTinOrder(BST*);
void changeOwner(BST* root, char*, char*);
void deleteFile(File**);
BST* copyFile(BST*, char*);



Node* createNodeSLL(File*);
void insertList(Node**, File*);
int fhash(char*, int);
void insertHash(Hash**, File*);
void convertToHash(BST*, Hash**);
void printList(Node*);
void printHash(Hash*);


int main()
{
	FILE* f = fopen("Data.txt", "r");

	File* file = NULL;
	BST* bst = NULL;
	Hash* hash = NULL;

	if (f)
	{
		char name[BUFFERSIZE];
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
			strcpy(name, token);

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

			file = createFile(name, size, isReadOnly, date, owner);

			// ex 1
			bst = insertBST(bst, file);

			// ex 6
			//insertHash(&hash, file);

		}

	}

	// ex 2
	printBSTinOrder(bst);
	printf("\n");

	// ex 3
	int readOnlyNo = countReadOnly(bst);
	printf("Number of files that have read only access: %d\n", readOnlyNo);
	printf("\n");

	// ex 4
	changeOwner(bst, "FL25", "Marin");
	printBSTinOrder(bst);
	printf("\n");


	// ex 5


	// ex 6
	convertToHash(bst, &hash);
	printHash(hash);

}


File* createFile(char* name, unsigned int size, bool isReadOnly, char* date, char* owner)
{
	File* file = (File*)malloc(sizeof(File));

	file->name = (char*)malloc(strlen(name) + 1);
	strcpy(file->name, name);

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
	printf("File: %s, %d, %d, %s, %s\n", file->name, file->size, file->isReadOnly, file->date, file->owner);
}



BST* createNode(File* file)
{
	BST* node = (BST*)malloc(sizeof(BST));

	node->info = file;
	node->left = NULL;
	node->right = NULL;

	return node;
}


BST* insertBST(BST* root, File* file)
{
	if (root == NULL)
	{
		root = createNode(file);
		return root;
	}
	else if (file->size < root->info->size)
	{
		root->left = insertBST(root->left, file);
	}
	else if (file->size > root->info->size)
	{
		root->right = insertBST(root->right, file);
	}
	return root;
}


void printBSTinOrder(BST* root)
{
	if (root != NULL)
	{
		printBSTinOrder(root->left);
		printFile(root->info);
		printBSTinOrder(root->right);
	}

}


int countReadOnly(BST* root)
{
	int count = 0;
	if (root == NULL)
	{
		return 0;
	}
	else if (root != NULL)
	{
		if (root->info->isReadOnly == true)
		{
			count = 1;
		}
	}

	return count + countReadOnly(root->right) + countReadOnly(root->left);
}

void changeOwner(BST* root, char* name, char* newOwner)
{
	if (root == NULL)
	{
		return;
	}
	else if (root != NULL)
	{
		changeOwner(root->left, name, newOwner);
		if (strcmp(root->info->name, name) == 0)
		{
			free(root->info->owner);
			root->info->owner = (char*)malloc(strlen(newOwner) + 1);
			strcpy(root->info->owner, newOwner);
		}
		changeOwner(root->right, name, newOwner);
	}
}



void deleteFile(File** file)
{
	free((*file)->name);
	free((*file)->date);
	free((*file)->owner);
	free((*file));
}

//// the size is 50% of the original
//BST* copyFile(BST* root, char* name)
//{
//	if (root == NULL)
//	{
//		return root;
//	}
//	else if (root != NULL)
//	{
//		if (strcmp(name, root->info->name) < 0)
//		{
//			root->left = copyFile(root->left, name);
//		}
//		else if (strcmp(name, root->info->name) < 0)
//		{
//			root->right = copyFile(root->right, name);
//		}
//		else if (strcmp(name, root->info->name) == 0)
//		{
//			// one leaf node or none
//
//			if (root->left == NULL)
//			{
//				BST* temp = root;
//				root = root->right;
//				temp->info->size = size / 2;
//				insertBST(temp, temp->info);
//				deleteFile(&(temp)->info);
//				free(temp);
//				return root;
//				
//			}
//			else if (root->right == NULL)
//			{
//				BST* temp = root;
//				root = root->left;
//				temp->info->size = size / 2;
//				insertBST(temp, temp->info);
//				deleteFile(&(temp)->info);
//				free(temp);
//				return root;
//			}
//			else
//			{
//				// two leaf node
//
//				BST* temp = root->right;
//				while (temp != NULL)
//				{
//					temp = temp->left;
//				}
//
//				free(root->info->name);
//				free(root->info->date);
//				free(root->info->owner);
//
//				root->info->name = (char*)malloc(strlen(temp->info->name));
//				root->info->date = (char*)malloc(strlen(temp->info->date));
//				root->info->owner = (char*)malloc(strlen(temp->info->owner));
//				root->info->isReadOnly = temp->info->isReadOnly;
//
//				//unfinished
//
//				
//			}
//		}
//	}
//
//}


Node* createNodeSLL(File* file)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->info = file;
	node->next = NULL;

	return node;
}

void insertList(Node** list, File* file)
{
	Node* node = createNodeSLL(file);
	if (*list == NULL)
	{
		*list = node;
	}
	else if (*list != NULL)
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


void insertHash(Hash** hash, File* file)
{
	if (*hash == NULL)
	{
		*hash = (Hash*)malloc(sizeof(Hash));
		(*hash)->size = HSIZE;
		(*hash)->buckets = (Node**)malloc(sizeof(Node*) * (*hash)->size);
		memset((*hash)->buckets, 0, sizeof(Node*) * (*hash)->size);
	}
	int index = 0;
	index = fhash(file->owner, (*hash)->size);
	insertList(&(*hash)->buckets[index], file);
}

void convertToHash(BST* root, Hash** hash)
{
	if (root != NULL)
	{
		convertToHash(root->left, hash);
		insertHash(hash, root->info);
		convertToHash(root->right, hash);
	}
}


void printList(Node* list)
{
	Node* temp = list;
	while (temp != NULL)
	{
		printFile(temp->info);
		temp = temp->next;
	}
}

void printHash(Hash* hash)
{
	for (int i = 0; i < hash->size; i++)
	{
		printf("Bucket %d\n", i);
		printList(hash->buckets[i]);
		printf("\n");
	}
}