#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
void readNumbersFromFile(char* filename, int* numbers, int numCount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!");
        return;
    }

    for (int i = 0; i < numCount; i++) {
        fscanf(file, "%d", &numbers[i]);
    }

    fclose(file);
}

// Function to write numbers from an array to a file
void writeNumbersToFile(char* filename, int* numbers, int numCount) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!");
        return;
    }

    for (int i = 0; i < numCount; i++) {
        fprintf(file, "%d\n", numbers[i]);
    }

    fclose(file);
}

// Function to perform bubble sort
void bubbleSort(int* numbers, int numCount) {
    for (int i = 0; i < numCount - 1; i++) {
        for (int j = 0; j < numCount - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
}

// Function to calculate the time complexity of sorting
double calculateSortTimeComplexity(int numCount) {
    // Time complexity of bubble sort is O(n^2)
    return numCount * numCount;
}

// Function to calculate the time complexity of random number generation
double calculateRandomNumberTimeComplexity(int numCount) {
    // Time complexity of generating a random number is O(1)
    return numCount;
}

int main() {
    int minRange, maxRange, numCount;
    char randomFile[50] = "random_numbers.txt";
    char sortedFile[50] = "sorted_numbers.txt";
    char logFile[50] = "time_complexity.log";

    printf("Enter the minimum range: ");
    scanf("%d", &minRange);

    printf("Enter the maximum range: ");
    scanf("%d", &maxRange);

    printf("Enter the number of random numbers to generate: ");
    scanf("%d", &numCount);

    // Generate random numbers and save them to a file
    generateRandomNumbers(minRange, maxRange, numCount, randomFile);

    // Read the random numbers from the file
    int* numbers = (int*)malloc(numCount * sizeof(int));
    readNumbersFromFile(randomFile, numbers, numCount);

    // Sort the numbers
    bubbleSort(numbers, numCount);

    // Write the sorted numbers to a file
    writeNumbersToFile(sortedFile, numbers, numCount);

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
    free(numbers);

    printf("Random numbers generated, sorted, and saved successfully.\n");

    return 0;
}
