#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, int value, int min, int max) {
    if (root == NULL) {
        int randomNum = (rand() % (max - min + 1)) + min;
        root = createNode(randomNum);
    }
    else if (value < root->data) {
        root->left = insertNode(root->left, value, min, max);
    }
    else {
        root->right = insertNode(root->right, value, min, max);
    }
    return root;
}

void generateAndSaveToFile(Node* root, FILE* file, int numNodes, int min, int max) {
    if (numNodes <= 0) {
        return;
    }

    int randomNum = (rand() % (max - min + 1)) + min;
    fprintf(file, "%d ", randomNum);

    root = insertNode(root, randomNum, min, max);
    generateAndSaveToFile(root, file, numNodes - 1, min, max);
}

int main() {
    Node* root = NULL;
    int min, max, numNodes;
    FILE* file;

    printf("Enter the minimum value for random numbers: ");
    scanf("%d", &min);
    printf("Enter the maximum value for random numbers: ");
    scanf("%d", &max);
    printf("Enter the number of nodes in the binary tree: ");
    scanf("%d", &numNodes);

    srand(time(0));

    file = fopen("binary_tree.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    generateAndSaveToFile(root, file, numNodes, min, max);

    fclose(file);
    printf("Binary tree data has been saved to the file.\n");

    return 0;
}
