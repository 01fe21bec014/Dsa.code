#include <stdio.h>
#include <stdlib.h>

// Node structure for the doubly linked list
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to create a 4x4 matrix using a doubly linked list
Node* createMatrix() {
    int row, col, data;
    Node* head = NULL;
    Node* currentRow = NULL;
    Node* currentCol = NULL;

    // Create the matrix
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            printf("Enter element at row %d, column %d: ", row, col);
            scanf("%d", &data);

            Node* newNode = createNode(data);

            if (head == NULL) {
                // First element of the matrix
                head = newNode;
                currentRow = head;
                currentCol = head;
            } else {
                // Connect the nodes horizontally
                currentCol->next = newNode;
                newNode->prev = currentCol;
                currentCol = newNode;

                // Connect the nodes vertically
                Node* prevRowNode = currentRow;
                Node* prevColNode = newNode->prev;
                while (prevRowNode != NULL && prevColNode != NULL) {
                    prevRowNode->next = newNode;
                    newNode->prev = prevRowNode;
                    prevRowNode = prevRowNode->prev;
                    prevColNode = prevColNode->prev;
                }
                currentRow = currentRow->next;
            }
        }
    }

    return head;
}

// Function to display the matrix
void displayMatrix(Node* head) {
    printf("Matrix:\n");
    Node* rowNode = head;
    while (rowNode != NULL) {
        Node* colNode = rowNode;
        while (colNode != NULL) {
            printf("%d\t", colNode->data);
            colNode = colNode->next;
        }
        printf("\n");
        rowNode = rowNode->next;
    }
}

// Main function
int main() {
    Node* head = createMatrix();
    displayMatrix(head);

    return 0;
}


