#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// define a linked list node structure
typedef struct node {
    int data;
    struct node* next;
} Node;

// function to add a new node to the end of the linked list
void append(Node** headRef, int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    Node* current = *headRef;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

int main() {
    int n, min, max;
    printf("Enter the number of random numbers to generate: ");
    scanf("%d", &n);
    printf("Enter the minimum number: ");
    scanf("%d", &min);
    printf("Enter the maximum number: ");
    scanf("%d", &max);

    // seed the random number generator
    srand(time(NULL));

    // create a linked list and generate n random numbers within the specified range
    Node* head = NULL;
    for (int i = 0; i < n; i++) {
        int randomNumber = (rand() % (max - min + 1)) + min;
        append(&head, randomNumber);
    }

    // open a file for writing
    FILE* fp = fopen("linklist_randomnumbers.txt", "w");

    // write the numbers to the file
    Node* current = head;
    while (current != NULL) {
        fprintf(fp, "%d\n", current->data);
        current = current->next;
    }

    // close the file and free the memory allocated for the linked list
    fclose(fp);
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    printf("%d random numbers generated and saved to file 'linklist_randomnumbers.txt'\n",n);
    return 0;
}
