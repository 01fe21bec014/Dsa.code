#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate random numbers in a given range
int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    // Seed the random number generator with current time
    srand(time(0));

    int min, max, num;
    printf("Enter the minimum value: ");
    scanf("%d", &min);
    printf("Enter the maximum value: ");
    scanf("%d", &max);
    printf("Enter the number of random numbers to generate: ");
    scanf("%d", &num);

    // Create a file pointer
    FILE *fp;

    // Open a file in write mode
    fp = fopen("random_numbers.txt", "w");

    if (fp == NULL) {
        printf("Error opening file!");
        return 1;
    }

    // Generate random numbers and write them to the file
    for (int i = 0; i < num; i++) {
        int randomNum = generateRandomNumber(min, max);
        fprintf(fp, "%d\n", randomNum);
    }

    printf("%d random numbers generated and saved to file 'random_numbers.txt'\n", num);

    // Close the file
    fclose(fp);

    return 0;
}
