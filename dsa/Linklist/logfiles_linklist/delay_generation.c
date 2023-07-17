#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to calculate the time complexity of linked list operations
double calculateTimeComplexity(struct Node* head) {
    double complexity = 0.0;
    struct Node* current = head;

    while (current != NULL) {
        complexity++;
        current = current->next;
    }

    return complexity;
}

// Function to print the linked list
void printLinkedList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    char filename[100];

    printf("Enter the name of the input file: ");
    scanf("%s", filename);

    // Read the input file and insert its contents into the linked list
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!");
        return 1;
    }

    int data;
    while (fscanf(file, "%d", &data) == 1) {
        insertAtEnd(&head, data);
    }

    fclose(file);

    // Calculate the time complexity of the linked list operations
    double timeComplexity = calculateTimeComplexity(head);

    // Save the time complexity in a log file
    FILE* logFile = fopen("time_complexity.log", "w");
    if (logFile == NULL) {
        printf("Error opening log file!");
        return 1;
    }

    fprintf(logFile, "Time complexity of linked list operations: %.2lf\n", timeComplexity);

    fclose(logFile);

    printf("Linked list created from the input file successfully.\n");

    return 0;
}
