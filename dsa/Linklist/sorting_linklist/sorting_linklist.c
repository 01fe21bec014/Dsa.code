#include <stdio.h>
#include <stdlib.h>

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

// function to perform bubble sort on a linked list of numbers
void bubbleSort(Node* head) {
    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    // check for empty list
    if (head == NULL) {
        return;
    }

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

int main() {
    FILE* fpInput = fopen("linklist_randomnumbers.txt", "r");
    if (fpInput == NULL) {
        printf("Error: input file not found.\n");
        return 1;
    }

    // read the numbers from the input file into a linked list
    Node* head = NULL;
    int num;
    while (fscanf(fpInput, "%d", &num) == 1) {
        append(&head, num);
    }

    fclose(fpInput);

    // perform bubble sort on the linked list
    bubbleSort(head);

    // write the sorted linked list to an output file
    FILE* fpOutput = fopen("output_linklistnumbers.txt", "w");
    Node* current = head;
    while (current != NULL) {
        fprintf(fpOutput, "%d\n", current->data);
        current = current->next;
    }
    fclose(fpOutput);

    // free the memory allocated for the linked list
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    printf(" random numbers are sorted and saved to file 'output_linklistnumbers.txt'\n",num);
    return 0;
}


