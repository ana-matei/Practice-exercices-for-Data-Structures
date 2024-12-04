#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LINE_SIZE 256

struct MutualFund {
    char* code;
    char* group;
    int riskLevel;
    double netAssetValue;
    float roi;
};

typedef struct MutualFund MutualFund;

struct BSTNode {
    MutualFund* data;
    struct BSTNode* left;
    struct BSTNode* right;
};

typedef struct BSTNode BSTNode;

MutualFund* createFund(char* code, char* group, int riskLevel, double netAssetValue, float roi) {
    MutualFund* fund = (MutualFund*)malloc(sizeof(MutualFund));

    fund->code = (char*)malloc(strlen(code) + 1);
    strcpy(fund->code, code);

    fund->group = (char*)malloc(strlen(group) + 1);
    strcpy(fund->group, group);

    fund->riskLevel = riskLevel;
    fund->netAssetValue = netAssetValue;
    fund->roi = roi;

    return fund;
}

BSTNode* createNode(MutualFund* fund) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->data = fund;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BSTNode* insertNode(BSTNode* root, BSTNode* node) {
    if (root == NULL) {
        return node;
    }

    if (strcmp(node->data->code, root->data->code) < 0) {
        root->left = insertNode(root->left, node);
    }
    else if (strcmp(node->data->code, root->data->code) > 0) {
        root->right = insertNode(root->right, node);
    }
    // If the code is the same, we don't insert duplicates

    return root;
}

void lineBreakPrint() {
    printf("------------------------------------------------------------------------------------\n");
}

void printFund(MutualFund* fund) {
    printf("%s, %s, %d, %f, %.1f%%\n", fund->code, fund->group, fund->riskLevel, fund->netAssetValue, fund->roi);
}

void inOrderTraversal(BSTNode* root) {
    if (root == NULL) {
        return;
    }
    inOrderTraversal(root->left);
    printFund(root->data);
    inOrderTraversal(root->right);
}

void preOrderTraversal(BSTNode* root) {
    if (root == NULL) {
        return;
    }
    printFund(root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void postOrderTraversal(BSTNode* root) {
    if (root == NULL) {
        return;
    }
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printFund(root->data);
}


BSTNode* readFromFile(const char* filename) {
    BSTNode* root = NULL;

    FILE* file = fopen(filename, "r");

    if (file) {
        char* token = NULL;
        char delimiter[] = ",";
        char buffer[LINE_SIZE];

        char code[LINE_SIZE];
        char group[LINE_SIZE];
        int riskLevel;
        double netAssetValue;
        float roi;

        while (fgets(buffer, sizeof(buffer), file)) {
            token = strtok(buffer, delimiter);
            strcpy(code, token);

            token = strtok(NULL, delimiter);
            strcpy(group, token);

            token = strtok(NULL, delimiter);
            riskLevel = atoi(token);

            token = strtok(NULL, delimiter);
            netAssetValue = atof(token);

            token = strtok(NULL, delimiter);
            roi = atof(token);

            MutualFund* fund = createFund(code, group, riskLevel, netAssetValue, roi);
            BSTNode* node = createNode(fund);
            root = insertNode(root, node);
        }
        fclose(file);
    }
    else {
        printf("Failed to open the file.\n");
    }

    return root;
}

BSTNode* searchBST(BSTNode* root, const char* code) {
    if (root == NULL) {
        printf("Mutual Fund with code %s not found.\n", code);
        return NULL;
    }

    if (strcmp(root->data->code, code) == 0) {
        printf("Mutual Fund found:   ");
        printFund(root->data);
        return root;
    }

    if (strcmp(code, root->data->code) < 0) {
        return searchBST(root->left, code);
    }
    else {
        return searchBST(root->right, code);
    }
}


void freeMutualFund(MutualFund* fund) {
    free(fund->code);
    free(fund->group);
    free(fund);
}

void freeBST(BSTNode* root) {
    if (root == NULL) {
        return;
    }
    freeBST(root->left);
    freeBST(root->right);
    freeMutualFund(root->data);
    free(root);
}

BSTNode* deleteNode(BSTNode* root, const char* code) {
    if (root == NULL) {
        printf("Mutual Fund with code %s not found.\n", code);
        return root;
    }

    // Search for the node to delete
    if (strcmp(code, root->data->code) < 0) {
        root->left = deleteNode(root->left, code);
    }
    else if (strcmp(code, root->data->code) > 0) {
        root->right = deleteNode(root->right, code);
    }
    else { // Node found, perform deletion
        if (root->left == NULL) {
            BSTNode* temp = root->right;
            freeMutualFund(root->data);
            free(root);
            printf("Mutual Fund with code %s deleted.\n", code);
            lineBreakPrint();
            return temp;
        }
        else if (root->right == NULL) {
            BSTNode* temp = root->left;
            freeMutualFund(root->data);
            free(root);
            printf("Mutual Fund with code %s deleted.\n\n", code);
            return temp;
        }

        // Node with two children
        BSTNode* successorParent = root;
        BSTNode* successor = root->right;
        while (successor->left != NULL) {
            successorParent = successor;
            successor = successor->left;
        }

        // Copy the data of successor to root
        root->data = successor->data;

        // Delete the successor
        if (successorParent->left == successor) {
            successorParent->left = deleteNode(successorParent->left, successor->data->code);
        }
        else {
            successorParent->right = deleteNode(successorParent->right, successor->data->code);
        }
    }

    return root;
}


int main() {
    BSTNode* root = readFromFile("Data.txt");

    // printing
    printf("In-Order Traversal of BST:\n\n");
    inOrderTraversal(root);
    lineBreakPrint();

    printf("Pre-Order Traversal of BST:\n\n");
    preOrderTraversal(root);
    lineBreakPrint();

    printf("Post-Order Traversal of BST:\n\n");
    postOrderTraversal(root);
    lineBreakPrint();

    // searching
    char code[] = "10C";

    printf("Searching for Mutual Fund with code %s:\n\n", code);
    searchBST(root, code);
    lineBreakPrint();

    // deleting a node
    printf("Deleting Mutual Fund with code %s:\n", code);
    root = deleteNode(root, code);
    inOrderTraversal(root);
    lineBreakPrint();

    // free memory
    freeBST(root);

    return 0;
}
