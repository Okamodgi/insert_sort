#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

long long insertionSort(int* arr, int size, int order) {
    // order - направление сортировки (1 - по возрастанию, 2 - по убыванию)

    long long swapsCount = 0; // Кол-во перестановок

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

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");

    printf("--- Сортировка вставками (Insertion Sort) ---\n\n");

    int size = 20000;
    int* array = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        array[i] = rand() - rand();
    }

    clock_t start = clock();
    long long swaps = insertionSort(array, size, 1);
    clock_t end = clock();
    double timeSpent = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Тест на %d элементах:\n", size);
    printf("Время выполнения сортировки: %.4f сек.\n", timeSpent);
    printf("Количество перестановок (сдвигов): %lld\n\n", swaps);

    free(array);

    return 0;
}