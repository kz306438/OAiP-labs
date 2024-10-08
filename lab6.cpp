#define THIRD

#if defined(FIRST)

#include <iostream>
#include <cstring>
using namespace std;

// Функция для удаления центрального символа из строки
void removeMiddleChar(char str[], size_t size) {
    size_t middleIndex = size / 2; // Находим индекс центрального символа

    // Сдвигаем все символы после центрального на одну позицию влево
    for (size_t i = middleIndex; i < size - 1; ++i) {
        str[i] = str[i + 1];
    }
    str[size - 1] = '\0'; // Завершаем строку нулевым символом
}

// Функция для проверки, что размер строки не меньше 2
bool checkStrSize(size_t size) {
    return size >= 2;
}

// Функция для ввода строки от пользователя
void getInput(char str[], size_t maxLength) {
    cout << "Введите строку: " << endl;
    cin.getline(str, maxLength); // Читаем строку с клавиатуры
}

// Функция для обработки строки
void processString(char str[], size_t size) {
    if (size % 2) { // Проверяем, является ли размер строки нечётным
        removeMiddleChar(str, size); // Удаляем центральный символ
        cout << "Количество элементов строки нечётное: " << size << " символов" << endl;
        cout << "Из строки был удалён центральный элемент: " << endl << str << endl;
    }
    else {
        cout << "Количество элементов строки чётное: " << size << " символов" << endl;
        cout << "Центральный символ не был удалён!" << endl;
    }
}

// Основная функция для запуска программы
void run() {
    const int MAX_LENGTH = 100; // Максимальная длина строки
    char str[MAX_LENGTH]; // Массив для хранения строки

    getInput(str, MAX_LENGTH); // Ввод строки от пользователя

    size_t size = strlen(str); // Определяем длину строки

    if (!checkStrSize(size)) { // Проверяем, что длина строки достаточна
        cout << "Размер строки слишком мал!" << endl;
        return;
    }

    processString(str, size); // Обрабатываем строку
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "ru"); // Устанавливаем локаль для корректного отображения русских символов

    while (true) { // Бесконечный цикл для многократного запуска программы
        run();
    }

    return 0;
}



#elif defined(SECOND)

#include <iostream> // Подключение библиотеки для ввода-вывода
#include <stdio.h> // Подключение стандартной библиотеки ввода-вывода
#include <string.h> // Подключение библиотеки для работы со строками
#include <ctype.h> // Подключение библиотеки для работы с символами

using namespace std; // Использование пространства имен std

const int MAX_LENGTH = 100; // Определение константы для максимальной длины строки

void getInput(char* input);
void printResult(const char* maxRealSubstring);

// Функция для проверки, является ли строка вещественным числом
bool isFloat(const char* str) {
    bool hasDecimal = false; // Флаг наличия десятичной точки
    bool hasDigits = false; // Флаг наличия цифр
    bool leadingZero = false; // Флаг наличия ведущего нуля

    while (isspace(*str)) str++; // Пропуск пробелов в начале строки

    if (*str == '+' || *str == '-') str++; // Пропуск знака числа

    if (*str == '0') { // Проверка на ведущий ноль
        leadingZero = true;
        str++;
    }

    while (*str) { // Проход по символам строки
        if (isdigit(*str)) { // Проверка, является ли символ цифрой
            if (leadingZero && *str != '0') return false; // Проверка на невалидный формат с ведущим нулем
            hasDigits = true; // Установка флага наличия цифр
        }
        else if (*str == '.' || *str == ',') { // Проверка на десятичную точку или запятую
            if (hasDecimal) return false; // Если десятичная точка уже была, возвращаем false
            hasDecimal = true; // Установка флага наличия десятичной точки
            if (*(str + 1) == '\0') return false; // Проверка, что после точки есть цифры
        }
        else {
            return false; // Если символ не цифра и не точка, возвращаем false
        }
        str++; // Переход к следующему символу
    }

    return hasDigits && !leadingZero; // Возвращаем true, если есть цифры и нет ведущего нуля
}

// Функция для нахождения наибольшей вещественной подстроки
char* getLargestRealSubstring(const char* str) {
    size_t n = strlen(str); // Определение длины строки
    static char maxRealSubstring[MAX_LENGTH]; // Массив для хранения наибольшей вещественной подстроки
    maxRealSubstring[0] = '\0'; // Инициализация пустой строки

    for (int i = 0; i < n; ++i) { // Внешний цикл по начальной позиции подстроки
        for (int j = i; j < n; ++j) { // Внутренний цикл по конечной позиции подстроки
            char tempStr[MAX_LENGTH] = { '\0' }; // Временная строка для текущей подстроки
            int ind = 0; // Индекс для временной строки

            for (int k = i; k <= j; ++k) { // Копирование символов в временную строку
                tempStr[ind] = str[k];
                ind++;
            }
            tempStr[ind] = '\0'; // Завершение временной строки

            if (strlen(tempStr) > strlen(maxRealSubstring)) { // Проверка, длиннее ли текущая подстрока
                if (isFloat(tempStr)) { // Проверка, является ли текущая подстрока вещественным числом
                    std::copy(tempStr, tempStr + strlen(tempStr) + 1, maxRealSubstring); // Копирование текущей подстроки в maxRealSubstring
                }
            }
        }
    }
    return maxRealSubstring; // Возвращение наибольшей вещественной подстроки
}

// Функция для запуска программы
void run() {
    char input[MAX_LENGTH]; // Массив для ввода строки
    getInput(input); // Вызов функции для получения ввода

    if (input[0] == '\0') { // Проверка на пустую строку
        cout << "Вы ввели пустую строку!" << endl; // Вывод сообщения об ошибке
        return; // Завершение функции
    }

    char* maxRealSubstring = getLargestRealSubstring(input); // Нахождение наибольшей вещественной подстроки
    printResult(maxRealSubstring); // Вывод результата
}

// Функция для получения ввода от пользователя
void getInput(char* input) {
    cout << "Введите строку: " << endl; // Вывод приглашения для ввода
    cin.getline(input, MAX_LENGTH); // Чтение строки с клавиатуры
}

// Функция для вывода результата
void printResult(const char* maxRealSubstring) {
    if (maxRealSubstring[0] == '\0') { // Проверка на пустую подстроку
        cout << "Вещественная подстрока не найдена!" << endl; // Вывод сообщения об отсутствии подстроки
    }
    else {
        cout << "Наибольшая вещественная подстрока: " << maxRealSubstring << endl; // Вывод наибольшей вещественной подстроки
    }
}

// Главная функция программы
int main() {
    setlocale(LC_ALL, "ru"); // Установка локали для корректного отображения русского языка
    while (true) { // Бесконечный цикл
        run(); // Вызов функции run
    }
    return 0; // Возвращение 0 для завершения программы
}

#elif defined(THIRD)

#include <iostream> // Подключаем библиотеку для ввода-вывода

using namespace std; // Используем пространство имен std

const int MAX_LENGTH = 100; // Определяем максимальную длину строки

// Функция для вычисления длины строки
size_t myStrlen(const char* str)
{
    size_t length = 0; // Инициализируем переменную длины строки
    while (str[length] != '\0') { // Пока не достигнут конец строки
        ++length; // Увеличиваем длину на 1
    }
    return length; // Возвращаем длину строки
}

// Функция для замены символов в строке
void replaceCharacters(char* str)
{
    size_t n = myStrlen(str); // Вычисляем длину строки

    for (size_t i = 0; i < n; ++i) { // Проходим по каждому символу строки
        if ((i + 1) % 3 == 0 && (i + 1) % 4 == 0) {
            str[i] = '#'; // Заменяем символы, которые кратны и 3, и 4
        }
        else if ((i + 1) % 3 == 0) {
            str[i] = '%'; // Заменяем каждый третий символ
        }
        else if ((i + 1) % 4 == 0) {
            str[i] = '&'; // Заменяем каждый четвертый символ
        }
    }
}

// Функция для ввода строки
void inputString(char* str)
{
    cout << "Введите строку: " << endl; // Просим пользователя ввести строку
    cin.getline(str, MAX_LENGTH); // Считываем строку с клавиатуры
}

// Функция для проверки пустой строки
bool isEmptyString(const char* str)
{
    return str[0] == '\0'; // Проверяем, является ли первый символ строки нулевым
}

// Основная функция для выполнения программы
void run()
{
    char str[MAX_LENGTH]; // Объявляем массив символов для строки

    inputString(str); // Вызываем функцию для ввода строки

    if (isEmptyString(str)) // Проверяем, является ли строка пустой
    {
        cout << "Вы ввели пустую строку!" << endl; // Сообщаем пользователю о пустой строке
        return; // Завершаем выполнение функции
    }

    replaceCharacters(str); // Вызываем функцию для замены символов в строке

    cout << "Изменённая строка: " << str << endl; // Выводим изменённую строку
    cout << endl; // Печатаем пустую строку для разделения вывода
}

int main()
{
    setlocale(LC_ALL, "ru"); // Устанавливаем локаль для корректного отображения русского языка

    while (true) // Бесконечный цикл
    {
        run(); // Вызываем основную функцию
    }

    return 0; // Возвращаем 0, завершая программу
}


#else
	#error "undefined project"
#endif
