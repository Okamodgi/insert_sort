#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

long long insertionSort(int* arr, int size, int order) {
    // order - направление сортировки (1 - по возрастанию, 2 - по убыванию)
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

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");

    printf("--- Сортировка вставками (Insertion Sort) ---\n\n");

    int size = 25; 
    int minVal, maxVal;

    printf("Введите диапазон значений через пробел (минимум и максимум, например: -50 50): ");
    scanf("%d %d", &minVal, &maxVal);

    printf("\n");

    int* arr = (int*)malloc(size * sizeof(int));

    generateRandomArray(arr, size, minVal, maxVal);

    printf("Сгенерированный массив в диапазоне [%d, %d]:\n", minVal, maxVal);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    clock_t start = clock();
    long long swaps = insertionSort(arr, size, 1);
    clock_t end = clock();
    double timeSpent = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("После сортировки по возрастанию:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    printf("Время выполнения: %.4f сек.\n", timeSpent);
    printf("Перестановок: %lld\n", swaps);

    free(arr);
    return 0;
}