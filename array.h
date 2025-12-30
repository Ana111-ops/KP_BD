
#define ARRAY_H
#include <stdio.h>

// Типы данных
typedef enum {
    DESIGN_2D, DESIGN_3D, DESIGN_UI, DESIGN_UX
} DesignType;

typedef enum {
    FORMAT_PNG, FORMAT_JPEG, FORMAT_SVG, FORMAT_PDF, FORMAT_PSD
} Format;

typedef enum {
    REQ_WIN10, REQ_WIN11, REQ_MACOS12, REQ_LINUX_UBUNTU20
} Platform;

typedef struct {
    char name[50];
    DesignType design_type;
    char developer[50];
    Format formats[5];
    float price;
    char website[50];
    int api_version;
    Platform requirements[3];
} Software;

/*
 * output_software - выводит count записей из массива data
 * data - указатель на начало массива структур Software
 * count - количество элементов в массиве для вывода
 * Возвращает: int (0 - ошибка вывода, 1 - успешный вывод)
 */
int output_software(Software* data, int count);

/*
 * input_software - вводит данные в структуру Software с клавиатуры
 * data - указатель на структуру Software, куда записываются введенные данные
 * Возвращает: int (0 - успешный ввод)
 */
int input_software(Software* data);

/*
 * generate_test - заполняет массив size случайными тестовыми данными
 * data - указатель на массив структур Software для заполнения
 * count - количество элементов для генерации данных
 * Возвращает: ничего (void)
 */
void generate_test(Software* data, int count);

/*
 * save_to_file - сохраняет count записей в бинарный файл filename
 * data - указатель на массив структур Software с данными
 * count - количество элементов для сохранения
 * filename - указатель на строку с именем файла (C-строка)
 * Возвращает: int (0 - ошибка сохранения, 1 - успешное сохранение)
 */
int save_to_file(Software* data, int count, const char* filename);

/*
 * load_from_file - загружает данные из бинарного файла, динамически выделяет память
 * data - двойной указатель: изменяется на указатель на новый выделенный массив
 * count - указатель на переменную: в неё записывается количество загруженных элементов
 * filename - указатель на строку с именем файла (C-строка)
 * Возвращает: int (0 - ошибка загрузки, 1 - успешная загрузка)
 */
int load_from_file(Software** data, int* count, const char* filename);

/*
 * add_software - добавляет новую запись, перевыделяет память под увеличенный массив
 * data - указатель на текущий массив (может измениться на новый адрес)
 * count - указатель на текущее количество элементов (увеличивается на 1)
 * Возвращает: Software* - новый указатель на увеличенный массив
 */
Software* add_software(Software* data, int* count);

/*
 * search_by_design - ищет программы по типу дизайна, выводит найденные
 * data - указатель на массив структур Software
 * count - общее количество элементов в массиве
 * Возвращает: int (количество найденных совпадений)
 */
int search_by_design(Software* data, int count);

/*
 * search_by_price_and_format - ищет по диапазону цены и поддерживаемому формату
 * data - указатель на массив структур Software
 * count - общее количество элементов в массиве
 * Возвращает: int (количество найденных совпадений)
 */
int search_by_price_and_format(Software* data, int count);

/*
 * compare_price - компаратор для функции qsort() по возрастанию цены
 * a, b - указатели на элементы массива (const void* для совместимости с qsort)
 * Возвращает: int (-1 если a < b, 0 если a == b, 1 если a > b)
 */
int compare_price(const void* a, const void* b);

// Вспомогательные функции для вывода строковых представлений перечислений
const char* get_design_type_name(DesignType type);     // возвращает название типа дизайна
const char* get_format_name(Format format);            // возвращает название формата
const char* get_requirement_name(Platform req);        // возвращает название платформы


