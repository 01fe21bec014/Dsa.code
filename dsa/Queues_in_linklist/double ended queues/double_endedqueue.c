#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for a node in the double-ended queue
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Structure for the double-ended queue
typedef struct {
    Node* front;
    Node* rear;
} Deque;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to create an empty double-ended queue
Deque* createDeque() {
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    deque->front = NULL;
    deque->rear = NULL;
    return deque;
}

// Function to check if the double-ended queue is empty
int isEmpty(Deque* deque) {
    return deque->front == NULL;
}

// Function to insert an element at the front of the double-ended queue
void insertFront(Deque* deque, int data) {
    Node* newNode = createNode(data);
    if (isEmpty(deque)) {
        deque->front = deque->rear = newNode;
    } else {
        newNode->next = deque->front;
        deque->front->prev = newNode;
        deque->front = newNode;
    }
}

// Function to insert an element at the rear of the double-ended queue
void insertRear(Deque* deque, int data) {
    Node* newNode = createNode(data);
    if (isEmpty(deque)) {
        deque->front = deque->rear = newNode;
    } else {
        newNode->prev = deque->rear;
        deque->rear->next = newNode;
        deque->rear = newNode;
    }
}

// Function to delete an element from the front of the double-ended queue
int deleteFront(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Double-ended queue is empty!");
        return -1;
    }
    Node* frontNode = deque->front;
    int data = frontNode->data;
    deque->front = deque->front->next;
    if (deque->front != NULL) {
        deque->front->prev = NULL;
    } else {
        deque->rear = NULL;
    }
    free(frontNode);
    return data;
}

// Function to delete an element from the rear of the double-ended queue
int deleteRear(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Double-ended queue is empty!");
        return -1;
    }
    Node* rearNode = deque->rear;
    int data = rearNode->data;
    deque->rear = deque->rear->prev;
    if (deque->rear != NULL) {
        deque->rear->next = NULL;
    } else {
        deque->front = NULL;
    }
    free(rearNode);
    return data;
}

// Function to generate random numbers within a given range
void generateRandomNumbers(int min, int max, int numCount, char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!");
        return;
    }

    srand(time(0));
    for (int i = 0; i < numCount; i++) {
        int randomNumber = (rand() % (max - min + 1)) + min;
        fprintf(file, "%d\n", randomNumber);
    }

    fclose(file);
}

// Function to read numbers from a file into the double-ended queue
void readNumbersFromFile(char* filename, Deque* deque, int numCount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!");
        return;
    }

    int data;
    for (int i = 0; i < numCount; i++) {
        fscanf(file, "%d", &data);
        insertRear(deque, data);
    }

    fclose(file);
}

// Function to write numbers from the double-ended queue to a file
void writeNumbersToFile(char* filename, Deque* deque, int numCount) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!");
        return;
    }

    for (int i = 0; i < numCount; i++) {
        int data = deleteFront(deque);
        fprintf(file, "%d\n", data);
    }

    fclose(file);
}

// Function to perform bubble sort on numbers in the double-ended queue
void bubbleSort(Deque* deque, int numCount) {
    for (int i = 0; i < numCount - 1; i++) {
        for (int j = 0; j < numCount - i - 1; j++) {
            int first = deleteFront(deque);
            int second = deleteFront(deque);
            if (first > second) {
                insertRear(deque, second);
                insertRear(deque, first);
            } else {
                insertRear(deque, first);
                insertRear(deque, second);
            }
        }
    }
}

// Function to calculate the time complexity of sorting
double calculateSortTimeComplexity(int numCount) {
    return (double)(numCount * (numCount - 1)) / 2;
}

// Function to calculate the time complexity of random number generation
double calculateRandomNumberTimeComplexity(int numCount) {
    return (double)numCount;
}

int main() {
    int min, max, numCount;
    char randomFile[100] = "random_numbers.txt";
    char sortedFile[100] = "sorted_numbers.txt";
    char logFile[100] = "time_complexity.log";

    printf("Enter the minimum range: ");
    scanf("%d", &min);
    printf("Enter the maximum range: ");
    scanf("%d", &max);
    printf("Enter the number of random numbers to generate: ");
    scanf("%d", &numCount);

    // Generate random numbers and save them to a file
    generateRandomNumbers(min, max, numCount, randomFile);

    // Create a double-ended queue and read numbers from the file into the queue
    Deque* deque = createDeque();
    readNumbersFromFile(randomFile, deque, numCount);

    // Sort the numbers in the double-ended queue
    bubbleSort(deque, numCount);

    // Write the sorted numbers to a file
    writeNumbersToFile(sortedFile, deque, numCount);

    // Calculate the time complexity of sorting and random number generation
    double sortTimeComplexity = calculateSortTimeComplexity(numCount);
    double randomNumberTimeComplexity = calculateRandomNumberTimeComplexity(numCount);

    // Save the time complexities in a log file
    FILE* log = fopen(logFile, "w");
    if (log == NULL) {
        printf("Error opening log file!");
        return 1;
    }

    fprintf(log, "Time complexity of sorting: %.2lf\n", sortTimeComplexity);
    fprintf(log, "Time complexity of random number generation: %.2lf\n", randomNumberTimeComplexity);

    fclose(log);

    printf("Random numbers generated, sorted, and saved successfully.\n");

    return 0;
}

