#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for stack node
typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

// Function to create a new node
StackNode* createNode(int data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to check if stack is empty
int isEmpty(StackNode* root) {
    return (root == NULL);
}

// Function to push an element onto the stack
void push(StackNode** root, int data) {
    StackNode* newNode = createNode(data);
    newNode->next = *root;
    *root = newNode;
}

// Function to pop an element from the stack
int pop(StackNode** root) {
    if (isEmpty(*root))
        return -1;
    StackNode* temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    free(temp);
    return popped;
}

// Function to sort an array using insertion sort algorithm
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Function to generate random numbers in the given range
void generateRandomNumbers(int min, int max, int count, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    srand(time(0));

    for (int i = 0; i < count; i++) {
        int num = (rand() % (max - min + 1)) + min;
        fprintf(file, "%d\n", num);
    }

    fclose(file);
}

// Function to read numbers from a file and save them in an array
void readNumbersFromFile(const char* filename, int arr[], int size) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file for reading.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        if (fscanf(file, "%d", &arr[i]) != 1) {
            printf("Error reading number from file.\n");
            break;
        }
    }

    fclose(file);
}

// Function to write numbers from an array to a file
void writeNumbersToFile(const char* filename, int arr[], int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", arr[i]);
    }

    fclose(file);
}

int main() {
    const char* inputFilename = "input.txt";
    const char* sortFilename = "sorted.txt";
    const char* updatedFilename = "updated.txt";
    const char* popedFilename = "poped.txt";
    const char* logFilename = "logfile.txt";

    clock_t start, end;
    double cpu_time_used;

    int min, max, count;
    printf("Enter the minimum number: ");
    scanf("%d", &min);
    printf("Enter the maximum number: ");
    scanf("%d", &max);
    printf("Enter the count of random numbers to generate: ");
    scanf("%d", &count);

    start = clock();
    generateRandomNumbers(min, max, count, inputFilename);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Random numbers generated and saved in '%s'. Time taken: %f seconds.\n", inputFilename, cpu_time_used);

    int* numbers = (int*)malloc(count * sizeof(int));

    start = clock();
    readNumbersFromFile(inputFilename, numbers, count);
    insertionSort(numbers, count);
    writeNumbersToFile(sortFilename, numbers, count);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Numbers sorted and saved in '%s'. Time taken: %f seconds.\n", sortFilename, cpu_time_used);

    StackNode* stack = NULL;
    int numToPush;
    printf("Enter the number of elements to push onto the stack: ");
    scanf("%d", &numToPush);

    start = clock();
    for (int i = 0; i < numToPush; i++) {
        push(&stack, numbers[i]);
    }
    writeNumbersToFile(updatedFilename, numbers, numToPush);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Elements pushed onto the stack and saved in '%s'. Time taken: %f seconds.\n", updatedFilename, cpu_time_used);

    int numToPop;
    printf("Enter the number of elements to pop from the stack: ");
    scanf("%d", &numToPop);

    start = clock();
    for (int i = 0; i < numToPop; i++) {
        int popped = pop(&stack);
        if (popped != -1) {
            numbers[i] = popped;
        }
    }
    writeNumbersToFile(popedFilename, numbers, numToPop);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Elements popped from the stack and saved in '%s'. Time taken: %f seconds.\n", popedFilename, cpu_time_used);

    FILE* logFile = fopen(logFilename, "w");
    if (logFile == NULL) {
        printf("Failed to open logfile for writing.\n");
        return 0;
    }

    fprintf(logFile, "Input numbers generated and saved in '%s'. Time taken: %f seconds.\n", inputFilename, ((double)(end - start)) / CLOCKS_PER_SEC);
    fprintf(logFile, "Numbers sorted and saved in '%s'. Time taken: %f seconds.\n", sortFilename, cpu_time_used);
    fprintf(logFile, "Elements pushed onto the stack and saved in '%s'. Time taken: %f seconds.\n", updatedFilename, cpu_time_used);
    fprintf(logFile, "Elements popped from the stack and saved in '%s'. Time taken: %f seconds.\n", popedFilename, cpu_time_used);

    fclose(logFile);
    free(numbers);

    return 0;
}
