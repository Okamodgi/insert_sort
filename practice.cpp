#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void insertionSort(int* arr, int size, int order) {
    // order - направление сортировки (1 - по возрастанию, 2 - по убыванию)
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        if (order == 1) {
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
        }
        else {
            while (j >= 0 && arr[j] < key) {
                arr[j + 1] = arr[j];
                j--;
            }
        }
        arr[j + 1] = key;
    }
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");

    printf("--- Сортировка вставками (Insertion Sort) ---\n\n");

    int size1 = 25;
    int* array1 = (int*)malloc(size1 * sizeof(int));

    printf("Исходный массив (для сортировки по возрастанию):\n");
    for (int i = 0; i < size1; i++) {
        array1[i] = rand() % 100;
        printf("%d ", array1[i]);
    }
    printf("\n");
    insertionSort(array1, size1, 1);
    printf("Отсортированный массив:\n");
    for (int i = 0; i < size1; i++) {
        printf("%d ", array1[i]);
    }
    printf("\n\n");

    free(array1);

    int size2 = 25;
    int* array2 = (int*)malloc(size2 * sizeof(int));

    printf("Исходный массив (для сортировки по убыванию):\n");
    for (int i = 0; i < size2; i++) {
        array2[i] = rand() % 100;
        printf("%d ", array2[i]);
    }
    printf("\n");
    insertionSort(array2, size2, 2);
    printf("Отсортированный массив:\n");
    for (int i = 0; i < size2; i++) {
        printf("%d ", array2[i]);
    }
    printf("\n\n");

    free(array2);

    return 0;
}