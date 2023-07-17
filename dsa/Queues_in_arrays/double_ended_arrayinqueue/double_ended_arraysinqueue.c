
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

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

// Function to read numbers from a file into an array
void readNumbersFromFile(char* filename, int arr[], int numCount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!");
        return;
    }

    for (int i = 0; i < numCount; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);
}

// Function to write numbers from an array to a file
void writeNumbersToFile(char* filename, int arr[], int numCount) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!");
        return;
    }

    for (int i = 0; i < numCount; i++) {
        fprintf(file, "%d\n", arr[i]);
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
    return (double)(numCount * (numCount - 1)) / 2;
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

    // Read numbers from the file into an array
    readNumbersFromFile(randomFile, arr, numCount);

    // Sort the numbers in the array
    bubbleSort(arr, numCount);

    // Write the sorted numbers to a file
    writeNumbersToFile(sortedFile, arr, numCount);

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
