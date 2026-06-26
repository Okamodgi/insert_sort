#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

long long insertionSort(int* arr, int size, int order) {
    long long swapsCount = 0;
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        if (order == 1) {
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
                swapsCount++;
            }
        }
        else {
            while (j >= 0 && arr[j] < key) {
                arr[j + 1] = arr[j];
                j--;
                swapsCount++;
            }
        }
        arr[j + 1] = key;
    }
    return swapsCount;
}

void generateRandomArray(int* arr, int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (max - min + 1) + min;
    }
}

int writeToFile(const char* fileName, int* arr, int size) {
    FILE* file = fopen(fileName, "w");
    if (file == NULL) return 0;
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
    return 1;
}

int* readFromFile(const char* fileName, int* size) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) return NULL;
    int count = 0, temp;
    while (fscanf(file, "%d", &temp) == 1) {
        count++;
    }
    if (count == 0) {
        fclose(file);
        return NULL;
    }
    *size = count;
    int* arr = (int*)malloc((*size) * sizeof(int));
    if (arr == NULL) {
        fclose(file);
        return NULL;
    }
    rewind(file);
    for (int i = 0; i < *size; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
    return arr;
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");

    int size = 15;
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) return 1;

    generateRandomArray(arr, size, -100, 100);
    writeToFile("input.txt", arr, size);
    free(arr);

    // Проверяем чтение и последующую сортировку
    int newSize;
    int* readArr = readFromFile("input.txt", &newSize);

    if (readArr != NULL) {
        long long swaps = insertionSort(readArr, newSize, 1);
        writeToFile("output.txt", readArr, newSize);
        printf("Файлы успешно созданы и обработаны.\n");
        free(readArr);
    }

    return 0;
}