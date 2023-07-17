


#include <stdio.h>

#define MAX_SIZE 100

int main() {
    FILE *input_file, *output_file;
    int arr[MAX_SIZE];
    int i, j, temp, size;

    // Open input and output files
    input_file = fopen("random_numbers.txt", "r");
    output_file = fopen("output.txt", "w");

    // Read numbers from input file and store them in an array
    i = 0;
    while (fscanf(input_file, "%d", &arr[i]) == 1) {
        i++;
    }
    size = i;

    // Sort the array using bubble sort algorithm
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Write the sorted array to output file
    for (i = 0; i < size; i++) {
        fprintf(output_file, "%d\n", arr[i]);
    }

    // Close input and output files
    fclose(input_file);
    fclose(output_file);

    return 0;
}
