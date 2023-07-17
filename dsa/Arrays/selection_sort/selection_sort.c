#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void bubbleSort(int arr[], int n) {
  int i, j;
  for (i = 0; i < n-1; i++) {
    for (j = 0; j < n-i-1; j++) {
      if (arr[j] > arr[j+1]) {
        int temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    }
  }
}


void merge(int arr[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  int L[n1], R[n2];

  for (i = 0; i < n1; i++) {
    L[i] = arr[l + i];
  }

  for (j = 0; j < n2; j++) {
    R[j] = arr[m + 1 + j];
  }

  i = 0;
  j = 0;
  k = l;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    }
    else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int l, int r) {
  if (l < r) {
    int m = l+ (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m+1, r);

    merge(arr, l, m, r);
  }
}


void selectionSort(int arr[], int n) {
  int i, j, min_idx;

  for (i = 0; i < n-1; i++) {
    min_idx = i;
    for (j = i+1; j < n; j++) {
      if (arr[j] < arr[min_idx]) {
        min_idx = j;
      }
    }
    int temp = arr[i];
    arr[i] = arr[min_idx];
    arr[min_idx] = temp;
  }
}

int main() {
  FILE *inputFile;
  FILE *logFile;

  char *inputFileName = "input.txt";
  char *logFileName = "logfile.txt";

  int n, i, j;

  clock_t start, end;
  double cpu_time_used;

  logFile = fopen(logFileName, "w");

  for (n = 1000; n <= 10000; n += 1000) {
    int arr[n];


    inputFile = fopen(inputFileName, "r");
    for (i = 0; i < n; i++)
    {
      fscanf(inputFile, "%d", &arr[i]);
    }
    fclose(inputFile);


    start = clock();
    bubbleSort(arr, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(logFile, "Bubble Sort, n = %d, Time taken = %f\n", n, cpu_time_used);


    start = clock();
    mergeSort(arr, 0, n-1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(logFile, "Merge Sort, n = %d, Time taken = %f\n", n, cpu_time_used);


    start = clock();
    selectionSort(arr, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(logFile, "Selection Sort, n = %d, Time taken = %f\n", n, cpu_time_used);
  }

  fclose(logFile);

  return 0;
}
