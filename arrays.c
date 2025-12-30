#define _CRT_SECURE_NO_WARNINGS
#include "array.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>

const char* get_design_type_name(DesignType type) {
    switch (type) {
    case DESIGN_2D: return "2D дизайн";
    case DESIGN_3D: return "3D дизайн";
    case DESIGN_UI: return "UI дизайн";
    case DESIGN_UX: return "UX дизайн";
    default: return "Неизвестно";
    }
}

const char* get_format_name(Format format) {
    switch (format) {
    case FORMAT_PNG: return "PNG";
    case FORMAT_JPEG: return "JPEG";
    case FORMAT_SVG: return "SVG";
    case FORMAT_PDF: return "PDF";
    case FORMAT_PSD: return "PSD";
    default: return "Неизвестно";
    }
}

const char* get_requirement_name(Platform req) {
    switch (req) {
    case REQ_WIN10: return "Windows 10";
    case REQ_WIN11: return "Windows 11";
    case REQ_MACOS12: return "macOS 12";
    case REQ_LINUX_UBUNTU20: return "Linux Ubuntu 20";
    default: return "Неизвестно";
    }
}

int output_software(const Software* data, int count) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (count == 0) {
        puts("База пуста!");
        return 0;
    }

    for (int i = 0; i < count; i++) {
        printf("\nЗапись %d:\n", i + 1);
        printf("Название: %s\n", data[i].name);
        printf("Тип дизайна: %s\n", get_design_type_name(data[i].design_type));
        printf("Разработчик: %s\n", data[i].developer);
        printf("Форматы: ");
        for (int j = 0; j < 5; j++) {
            printf("%s", get_format_name(data[i].formats[j]));
            if (j < 4) printf(", ");
        }
        printf("\nЦена: %.2f\n", data[i].price);
        printf("Сайт: %s\n", data[i].website);
        printf("API: %d\n", data[i].api_version);
        printf("Требования: ");
        for (int j = 0; j < 3; j++) {
            printf("%s", get_requirement_name(data[i].requirements[j]));
            if (j < 2) printf(", ");
        }
        printf("\n");
    }
    puts("---------------------------------------------");
    return 1;
}

int input_software(Software* data) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    puts("Введите название ПО:");
    fgets(data->name, sizeof(data->name), stdin);
    data->name[strcspn(data->name, "\n")] = 0;

    puts("Введите тип дизайна (0-2D, 1-3D, 2-UI, 3-UX):");
    int design_type;
    scanf("%d", &design_type);
    data->design_type = (DesignType)design_type;
    getchar();

    puts("Введите разработчика:");
    fgets(data->developer, sizeof(data->developer), stdin);
    data->developer[strcspn(data->developer, "\n")] = 0;

    puts("Введите цену:");
    scanf("%f", &data->price);
    getchar();

    puts("Введите веб-сайт:");
    fgets(data->website, sizeof(data->website), stdin);
    data->website[strcspn(data->website, "\n")] = 0;

    puts("Введите версию API:");
    scanf("%d", &data->api_version);
    getchar();

    puts("Введите форматы (5 чисел 0-4):");
    for (int j = 0; j < 5; j++) {
        int format;
        scanf("%d", &format);
        data->formats[j] = (Format)format;
    }
    getchar();

    puts("Введите требования (3 числа 0-3):");
    for (int j = 0; j < 3; j++) {
        int req;
        scanf("%d", &req);
        data->requirements[j] = (Platform)req;
    }
    getchar();

    puts("-----------------------------------------------------------");
    return 0;
}

void generate_test(Software* data, int size) {
    const char* names[] = { "Photoshop", "GIMP", "Sketch", "Figma", "Canva" };
    const char* devs[] = { "Adobe", "Figma", "Sketch", "GIMP", "Canva" };
    const char* sites[] = { "adobe.com", "figma.com", "sketch.com", "gimp.org", "canva.com" };

    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        strncpy(data[i].name, names[rand() % 5], sizeof(data[i].name) - 1);
        data[i].name[sizeof(data[i].name) - 1] = '\0';

        strncpy(data[i].developer, devs[rand() % 5], sizeof(data[i].developer) - 1);
        data[i].developer[sizeof(data[i].developer) - 1] = '\0';

        strncpy(data[i].website, sites[rand() % 5], sizeof(data[i].website) - 1);
        data[i].website[sizeof(data[i].website) - 1] = '\0';

        data[i].design_type = (DesignType)(rand() % 4);
        data[i].price = 10.0f + rand() % 90;
        data[i].api_version = 1 + rand() % 5;

        for (int j = 0; j < 5; j++) data[i].formats[j] = (Format)(rand() % 5);
        for (int j = 0; j < 3; j++) data[i].requirements[j] = (Platform)(rand() % 4);
    }
}

int save_to_file(Software* data, int count, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Ошибка файла %s\n", filename);
        return 0;
    }
    fprintf(f, "%d\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s\n%d\n%s\n%.2f\n%s\n%d\n",
            data[i].name, data[i].design_type, data[i].developer,
            data[i].price, data[i].website, data[i].api_version);
        for (int j = 0; j < 5; j++) fprintf(f, "%d ", (int)data[i].formats[j]);
        fprintf(f, "\n");
        for (int j = 0; j < 3; j++) fprintf(f, "%d ", (int)data[i].requirements[j]);
        fprintf(f, "\n");
    }
    fclose(f);
    printf("Сохранено в %s\n", filename);
    return 1;
}

int load_from_file(Software** data, int* count, const char* filename) { // ИЗМЕНИЛА
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Файл %s не найден\n", filename);
        return 0;
    }

    if (fscanf(f, "%d", count) != 1 || *count <= 0) {
        fclose(f);
        return 0;
    }

    *data = realloc(*data, *count * sizeof(Software));
    if (!*data) {
        fclose(f);
        return 0;
    }

    int c;
    char temp[50];
    while ((c = fgetc(f)) != '\n' && c != EOF);

    for (int i = 0; i < *count; i++) {
        fgets((*data)[i].name, 50, f);
        (*data)[i].name[strcspn((*data)[i].name, "\n")] = 0;

        fgets(temp, 20, f); sscanf(temp, "%d", &(*data)[i].design_type);

        fgets((*data)[i].developer, 50, f);
        (*data)[i].developer[strcspn((*data)[i].developer, "\n")] = 0;

        fgets(temp, 20, f); sscanf(temp, "%f", &(*data)[i].price);

        fgets((*data)[i].website, 50, f);
        (*data)[i].website[strcspn((*data)[i].website, "\n")] = 0;

        fgets(temp, 20, f); sscanf(temp, "%d", &(*data)[i].api_version);

        fgets(temp, 50, f);
        sscanf(temp, "%d %d %d %d %d",&(*data)[i].formats[0], &(*data)[i].formats[1], &(*data)[i].formats[2], &(*data)[i].formats[3],&(*data)[i].formats[4]);
            
        fgets(temp, 30, f);
        sscanf(temp, "%d %d %d", &(*data)[i].requirements[0], &(*data)[i].requirements[1],  &(*data)[i].requirements[2]);    
    }
    fclose(f);
    return 1;
}


Software* add_software(Software* data, int* count) {
    (*count)++;
    Software* new_data = realloc(data, *count * sizeof(Software));
    if (!new_data) {
        (*count)--;
        printf("Ошибка realloc!\n");
        return data;
    }
    data = new_data;

    memset(&data[*count - 1], 0, sizeof(Software));
    input_software(&data[*count - 1]);
    return data;
}

int search_by_design(Software* data, int count) {
    int type;
    printf("Тип дизайна (0-3): ");
    scanf("%d", &type);
    getchar();

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (data[i].design_type == (DesignType)type) {
            output_software(&data[i], 1);
            found++;
        }
    }
    printf("Найдено: %d\n", found);
    return found;
}

int search_by_price_and_format(Software* data, int count) {
    float price;
    int fmt;
    printf("Макс цена: ");
    scanf("%f", &price);
    printf("Формат (0-4): ");
    scanf("%d", &fmt);
    getchar();

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (data[i].price <= price) {
            for (int j = 0; j < 5; j++) {
                if (data[i].formats[j] == (Format)fmt) {
                    output_software(&data[i], 1);
                    found++;
                    break;
                }
            }
        }
    }
    printf("Найдено: %d\n", found);
    return found;
}

int compare_price(const void* a, const void* b) {
    float pa = ((Software*)a)->price;
    float pb = ((Software*)b)->price;
    return (pa > pb) - (pa < pb);
}
