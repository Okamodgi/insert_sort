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

int writeToFile(const char* fileName, int* arr, int size) {
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        return 0;
    }
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
    return 1;
}

int* readFromFile(const char* fileName, int* size) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        return NULL;
    }

    int count = 0;
    int temp;
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

void generateRandomArray(int* arr, int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (max - min + 1) + min;
    }
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");

    int size, order, dataSource;
    int* arr;
    char inFileName[256], outFileName[256];

    printf("==================================================\n");
    printf("       СОРТИРОВКА ВСТАВКАМИ (INSERTION SORT)      \n");
    printf("==================================================\n\n");

    printf("[1] Настройка источника данных\n");
    printf("--------------------------------------------------\n");
    while (1) {
        printf("Выберите источник (1 - Файл, 2 - Генерация случайными числами): ");
        if (scanf("%d", &dataSource) == 1 && (dataSource == 1 || dataSource == 2)) {
            break;
        }
        printf(">> Ошибка: введите число 1 или 2!\n");
    }

    if (dataSource == 1) {
        while (1) {
            printf("Имя входного файла (input.txt): ");
            scanf("%255s", inFileName);

            arr = readFromFile(inFileName, &size);
            if (arr != NULL) {
                printf(">> Успешно. Обнаружено элементов: %d\n", size);
                break;
            }
            printf(">> Ошибка чтения файла %s. Попробуйте снова.\n", inFileName);
        }
    }
    else {
        while (1) {
            printf("Длина массива (число > 0): ");
            if (scanf("%d", &size) == 1 && size > 0) {
                break;
            }
            printf(">> Ошибка: длина должна быть целым положительным числом!\n");
        }

        int minVal, maxVal;
        while (1) {
            printf("Диапазон значений [min max]: ");
            if (scanf("%d %d", &minVal, &maxVal) == 2 && minVal <= maxVal) {
                break;
            }
            printf(">> Ошибка: введите два числа (min <= max)!\n");
        }

        arr = (int*)malloc(size * sizeof(int));
        if (arr == NULL) {
            printf("\n>> Критическая ошибка: не удалось выделить память.\n");
            return 1;
        }

        generateRandomArray(arr, size, minVal, maxVal);

        while (1) {
            printf("Имя файла для исходного массива: ");
            scanf("%255s", inFileName);

            if (writeToFile(inFileName, arr, size)) {
                printf(">> Массив успешно сгенерирован и сохранен.\n");
                break;
            }
            printf(">> Ошибка записи файла. Проверьте имя.\n");
        }
    }

    printf("\n[2] Настройка экспорта и параметров\n");
    printf("--------------------------------------------------\n");
    while (1) {
        printf("Имя файла для результата: ");
        scanf("%255s", outFileName);

        FILE* testFile = fopen(outFileName, "w");
        if (testFile != NULL) {
            fclose(testFile);
            break;
        }
        printf(">> Ошибка: некорректное имя или нет прав.\n");
    }

    while (1) {
        printf("Порядок (1 - Возрастание, 2 - Убывание): ");
        if (scanf("%d", &order) == 1 && (order == 1 || order == 2)) {
            break;
        }
        printf(">> Ошибка: введите 1 или 2!\n");
    }

    clock_t start = clock();
    long long swaps = insertionSort(arr, size, order);
    clock_t end = clock();
    double timeSpent = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\n==================================================\n");
    printf("                РЕЗУЛЬТАТЫ СОРТИРОВКИ             \n");
    printf("==================================================\n");
    printf("%-30s : %d\n", "Обработано элементов", size);
    printf("%-30s : %s\n", "Направление сортировки", (order == 1) ? "По возрастанию" : "По убыванию");
    printf("%-30s : %.4f сек.\n", "Время выполнения", timeSpent);
    printf("%-30s : %lld\n", "Количество перестановок", swaps);
    printf("--------------------------------------------------\n");

    if (writeToFile(outFileName, arr, size)) {
        printf(">> Результат сохранен в файл: %s\n", outFileName);
    }
    else {
        printf(">> Ошибка при финальной записи в файл %s.\n", outFileName);
    }
    printf("==================================================\n");

    free(arr);
    return 0;
}