#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include "array.h"

int main() {
    srand((unsigned)time(NULL));
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Software* data = NULL;
    int count = 0;
    char file_name[64];

    while (1) {
        int operation;
        puts("| ---- Базы данных для графических редакторов ----|");
        puts("|Выполнила: Карнаух Анастасия, БТИИ-251           |");
        puts("|--------------------- Меню: ---------------------|");
        puts("|1. Загрузка данных из файла                      |");
        puts("|2. Просмотр всех записей                         |");
        puts("|3. Поиск по типу дизайна + поддерживаемые форматы|");
        puts("|4. Сортировка данных по цене                     |");
        puts("|5. Добавление новой записи                       |");
        puts("|6. Сохранение данных в файл                      |");
        puts("|7. Генерация тестовых значений                   |");
        puts("|0. Выход                                         |");
        puts("---------------------------------------------------");
        printf("Введите номер операции:");
        scanf("%d", &operation);
        getchar();

        switch (operation) {
        case 1:
            puts("---------------------------------");
            puts("Загрузка данных из файла");
            printf("Введите имя файла: ");
            fgets(file_name, sizeof(file_name), stdin);
            file_name[strcspn(file_name, "\n")] = 0;
            load_from_file(&data, &count, file_name);
            printf("Загружено %d записей\n", count);
            break;
        case 2:
            puts("---------------------------------");
            puts("Просмотр всех записей");
            output_software(data, count);
            break;
        case 3:
            puts("---------------------------------");
            puts("Поиск по типу дизайна + поддерживаемые форматы");
            puts("1 - поиск по типу дизайна");
            puts("2 - комбинированный поиск (цена + формат)");
            int choice;
            scanf("%d", &choice);
            getchar();
            if (choice == 1) {
                search_by_design(data, count);
            }
            else if (choice == 2) {
                search_by_price_and_format(data, count);
            }
            break;
        case 4:
            puts("---------------------------------");
            puts("Сортировка данных по цене");
            if (count == 0) {
                puts("База пуста!");
                break;
            }
            qsort(data, count, sizeof(Software), compare_price);
            output_software(data, count);
            break;
        case 5:
            puts("---------------------------------");
            puts("Добавление новой записи");
            data = add_software(data, &count);
            puts("Запись добавлена!");
            break;
        case 6:
            puts("---------------------------------");
            puts("Сохранение данных в файл");
            printf("Имя файла: ");
            fgets(file_name, sizeof(file_name), stdin);
            file_name[strcspn(file_name, "\n")] = 0;
            save_to_file(data, count, file_name);
            break;
        case 7:
            puts("---------------------------------");
            puts("Генерация тестовых значений");
            printf("Введите количество записей: ");
            scanf("%d", &count);
            getchar();
            data = realloc(data, count * sizeof(Software));
            if (data) generate_test(data, count);
            puts("Нажмите 2 для просмотра");
            break;
        case 0:
            free(data);
            puts("До свидания!");
            return 0;
        }
    }
}
