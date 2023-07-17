#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

// Structure to represent a circular queue
typedef struct {
    int* arr;
    int front;
    int rear;
    int capacity;
} CircularQueue;

// Function to create a circular queue
CircularQueue* createQueue(int capacity) {
    CircularQueue* queue = (CircularQueue*)malloc(sizeof(CircularQueue));
    queue->arr = (int*)malloc(capacity * sizeof(int));
    queue->front = -1;
    queue->rear = -1;
    queue->capacity = capacity;
    return queue;
}

// Function to check if the circular queue is empty
int isEmpty(CircularQueue* queue) {
    return queue->front == -1;
}

// Function to check if the circular queue is full
int isFull(CircularQueue* queue) {
    return (queue->rear + 1) % queue->capacity == queue->front;
}

// Function to enqueue an element into the circular queue
void enqueue(CircularQueue* queue, int data) {
    if (isFull(queue)) {
        printf("Circular queue is full!\n");
        return;
    }

    if (isEmpty(queue)) {
        queue->front = 0;
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arr[queue->rear] = data;
}

// Function to dequeue an element from the circular queue
int dequeue(CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Circular queue is empty!\n");
        return -1;
    }

    int data = queue->arr[queue->front];

    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->capacity;
    }

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

// Function to read numbers from a file into a circular queue
void readNumbersFromFile(char* filename, CircularQueue* queue, int numCount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!");
        return;
    }

    for (int i = 0; i < numCount; i++) {
        int number;
        fscanf(file, "%d", &number);
        enqueue(queue, number);
    }

    fclose(file);
}

// Function to write numbers from a circular queue to a file
void writeNumbersToFile(char* filename, CircularQueue* queue, int numCount) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!");
        return;
    }

    int count = 0;
    int front = queue->front;
    while (count < numCount) {
        fprintf(file, "%d\n", queue->arr[front]);
        front = (front + 1) % queue->capacity;
        count++;
    }

    fclose(file);
}

// Function to perform bubble sort on an array of numbers
void bubbleSort(int arr[], int numCount) {
    for (int i = 0; i < numCount - 1; i++) {
        for (int j = 0; j < numCount - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to calculate the time complexity of sorting
double calculateSortTimeComplexity(int numCount) {
    return (double)(numCount * numCount);
}

// Function to calculate the time complexity of random number generation
double calculateRandomNumberTimeComplexity(int numCount) {
    return (double)numCount;
}

int main() {
    int min, max, numCount;
    int arr[MAX_SIZE];
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

    // Create a circular queue
    CircularQueue* queue = createQueue(numCount);

    // Read numbers from the file into the circular queue
    readNumbersFromFile(randomFile, queue, numCount);

    // Dequeue the numbers from the circular queue and store them in an array
    for (int i = 0; i < numCount; i++) {
        arr[i] = dequeue(queue);
    }

    // Sort the numbers in the array
    bubbleSort(arr, numCount);

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
