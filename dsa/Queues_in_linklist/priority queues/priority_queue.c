#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for a node in the priority queue
typedef struct Node {
    int data;
    int priority;
    struct Node* next;
} Node;

// Structure for the priority queue
typedef struct {
    Node* front;
} PriorityQueue;

// Function to create a new node
Node* createNode(int data, int priority) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

// Function to create an empty priority queue
PriorityQueue* createPriorityQueue() {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->front = NULL;
    return queue;
}

// Function to check if the priority queue is empty
int isEmpty(PriorityQueue* queue) {
    return queue->front == NULL;
}

// Function to enqueue an element in the priority queue based on priority
void enqueue(PriorityQueue* queue, int data, int priority) {
    Node* newNode = createNode(data, priority);
    if (isEmpty(queue) || priority < queue->front->priority) {
        newNode->next = queue->front;
        queue->front = newNode;
    } else {
        Node* current = queue->front;
        while (current->next != NULL && current->next->priority <= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to dequeue the element with the highest priority from the priority queue
int dequeue(PriorityQueue* queue) {
    if (isEmpty(queue)) {
        printf("Priority queue is empty!");
        return -1;
    }
    Node* frontNode = queue->front;
    int data = frontNode->data;
    queue->front = queue->front->next;
    free(frontNode);
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

// Function to read numbers from a file into the priority queue
void readNumbersFromFile(char* filename, PriorityQueue* queue, int numCount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!");
        return;
    }

    int data;
    for (int i = 0; i < numCount; i++) {
        fscanf(file, "%d", &data);
        enqueue(queue, data, data);
    }

    fclose(file);
}

// Function to write numbers from the priority queue to a file
void writeNumbersToFile(char* filename, PriorityQueue* queue, int numCount) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!");
        return;
    }

    for (int i = 0; i < numCount; i++) {
        int data = dequeue(queue);
        fprintf(file, "%d\n", data);
    }

    fclose(file);
}

// Function to perform bubble sort on numbers in the priority queue
void bubbleSort(PriorityQueue* queue, int numCount) {
    for (int i = 0; i < numCount - 1; i++) {
        for (int j = 0; j < numCount - i - 1; j++) {
            int first = dequeue(queue);
            int second = dequeue(queue);
            if (first > second) {
                enqueue(queue, second, second);
                enqueue(queue, first, first);
            } else {
                enqueue(queue, first, first);
                enqueue(queue, second, second);
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

    // Create a priority queue and read numbers from the file into the queue
    PriorityQueue* queue = createPriorityQueue();
    readNumbersFromFile(randomFile, queue, numCount);

    // Sort the numbers in the priority queue
    bubbleSort(queue, numCount);

    // Write the sorted numbers to a file
    writeNumbersToFile(sortedFile, queue, numCount);

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

