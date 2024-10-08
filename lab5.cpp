#define THIRD

#if defined(FIRST)

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Функция для проверки размера массива
bool checkArraySize(const size_t& n) {
    if (n < 1) {
        cout << "Недопустимое количество элементов массива!" << endl;
        return false;
    }
    return true;
}

// Функция для очистки ввода
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Шаблонная функция для ввода значения с проверкой
template <typename T>
void inputValue(const string& prompt, T& value, bool (*checkFunc)(const T&) = nullptr) {
    while (true) {
        cout << prompt << endl;
        cin >> value;
        if (cin.good())
        {
            if(!checkFunc || checkFunc(value))
            {
                break;
            }
        }
        else {
            cout << "Некорректный ввод! Попробуйте снова!" << endl;
            clearInput();
        }
    }
}

// Функция для ввода элементов массива
void inputMatrixElements(double** matrix, size_t n, size_t m) {
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            string prompt = "Введите (" + to_string(i) + "," + to_string(j) + ")-ый элемент";
            inputValue(prompt, matrix[i][j]);
        }
    }
}

// Функция для выделения памяти под матрицу
void allocateMemory(double**& matrix, size_t n, size_t m) {
    matrix = new double* [n];
    for (size_t i = 0; i < n; ++i) {
        matrix[i] = new double[m];
    }
}

// Функция для освобождения памяти массива
void deallocateMemory(double**& matrix, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Функция для нахождения и вывода суммы элементов строк, содержащих отрицательные элементы
void findAndPrintSum(double** matrix, size_t n, size_t m) {
    for (size_t i = 0; i < n; ++i) {
        bool hasNegative = false;
        double rowSum = 0;

        for (size_t j = 0; j < m; ++j) {
            rowSum += matrix[i][j];
            if (matrix[i][j] < 0) {
                hasNegative = true;
            }
        }
        if (hasNegative) {
            cout << "Сумма элементов в строке " << i << ": " << rowSum << endl;
        }
    }
    cout << endl;
}

// Основная функция для выполнения всех операций
void calculate() {
    size_t n, m;

    inputValue("Введите число строк: ", n, checkArraySize);
    inputValue("Введите число столбцов: ", m, checkArraySize);

    double** matrix = nullptr;
    allocateMemory(matrix, n, m);
    inputMatrixElements(matrix, n, m);
    findAndPrintSum(matrix, n, m);
    deallocateMemory(matrix, n);
}

int main() 
{
    setlocale(LC_ALL, "ru");

    while (true) {
        calculate();
    }

    return 0;
}




#elif defined(SECOND)

#include <iostream> // Подключение библиотеки для ввода-вывода
#include <string> // Подключение библиотеки для работы со строками
#include <limits> // Подключение библиотеки для работы с пределами числовых типов
#include <algorithm> // Подключение библиотеки для алгоритмов, таких как сортировка
using namespace std; // Использование пространства имен std

// Функция для проверки размера массива
bool checkArraySize(const size_t& n) {
    if (n < 1) { // Проверка, что размер массива не меньше 1
        cout << "Недопустимое количество элементов массива!" << endl; // Вывод сообщения об ошибке
        return false; // Возврат false, если размер недопустим
    }
    return true; // Возврат true, если размер допустим
}

// Функция для очистки ввода
void clearInput() {
    cin.clear(); // Очистка состояния потока
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование оставшихся символов в потоке
}

// Шаблонная функция для ввода значения с проверкой
template <typename T>
void inputValue(const string& prompt, T& value, bool (*checkFunc)(const T&) = nullptr) {
    while (true) { // Бесконечный цикл для повторного ввода в случае ошибки
        cout << prompt << endl; // Вывод приглашения для ввода
        cin >> value; // Ввод значения
        if (cin.good())
        {
            if (!checkFunc || checkFunc(value))
            {
                break;
            }
        }
        else { // Если ввод некорректен
            cout << "Некорректный ввод! Попробуйте снова!" << endl; // Вывод сообщения об ошибке
            clearInput(); // Очистка ввода
        }
    }
}

// Функция для ввода элементов массива
void inputMatrixElements(double** arr, size_t n, size_t m) {
    for (size_t i = 0; i < n; ++i) { // Цикл по строкам массива
        for (size_t j = 0; j < m; ++j) { // Цикл по столбцам массива
            string prompt = "Введите (" + to_string(i) + "," + to_string(j) + ")-ый элемент"; // Формирование приглашения для ввода
            inputValue(prompt, arr[i][j]); // Ввод элемента массива с проверкой
        }
    }
}

// Функция для выделения памяти под массив
void allocateMemory(double**& matrix, size_t n, size_t m) {
    matrix = new double* [n]; // Выделение памяти под массив указателей на строки
    for (size_t i = 0; i < n; ++i) { // Цикл по строкам массива
        matrix[i] = new double[m]; // Выделение памяти под строку
    }
}

// Функция для освобождения памяти массива
void deallocateMemory(double**& matrix, size_t n) {
    for (size_t i = 0; i < n; ++i) { // Цикл по строкам массива
        delete[] matrix[i]; // Удаление строки
    }
    delete[] matrix; // Удаление массива указателей
}

// Структура для сравнения строк массива
struct CompareRows {
    bool operator()(double* a, double* b) const { // Оператор сравнения
        return a[0] < b[0]; // Сравнение первых элементов строк
    }
};

// Функция для сортировки строк массива по возрастанию первых элементов
void sortRowsInAscendingOrder(double**& matrix, size_t n) {
    std::sort(matrix, matrix + n, CompareRows()); // Сортировка строк массива
}

// Функция для вывода массива на экран
void printMatrix(double**& matrix, size_t n, size_t m) {
    cout << "Матрица, строки которой упорядочены по возрастанию первых их элементов: " << endl; // Вывод заголовка

    for (int i = 0; i < n; i++) { // Цикл по строкам массива
        for (int j = 0; j < m; j++) { // Цикл по столбцам массива
            cout << matrix[i][j] << ' '; // Вывод элемента массива
        }
        cout << endl; // Переход на новую строку после вывода всех элементов строки
    }
    cout << endl; // Пустая строка после вывода всей матрицы
}

// Основная функция для выполнения всех операций
void calculate() {
    size_t n, m; // Объявление переменных для размеров массива

    inputValue("Введите число строк: ", n, checkArraySize); // Ввод числа строк с проверкой
    inputValue("Введите число столбцов: ", m, checkArraySize); // Ввод числа столбцов с проверкой

    double** matrix = nullptr; // Объявление указателя на массив
    allocateMemory(matrix, n, m); // Выделение памяти под массив
    inputMatrixElements(matrix, n, m); // Ввод элементов массива

    sortRowsInAscendingOrder(matrix, n); // Сортировка строк массива
    printMatrix(matrix, n, m); // Вывод массива на экран

    deallocateMemory(matrix, n); // Освобождение памяти массива
}

int main() {
    setlocale(LC_ALL, "ru"); // Установка локали для корректного вывода на русском языке

    while (true) { // Бесконечный цикл для повторного выполнения программы
        calculate(); // Вызов функции для выполнения всех операций
    }

    return 0; // Возврат 0, программа завершена успешно
}


#elif defined(THIRD)

#include <iostream>
#include <string>
#include <limits>

using namespace std;


bool checkMatrixSize(const size_t& n) {
    if (n < 1) { // Проверка, что размер массива не меньше 1
        cout << "Недопустимое количество элементов массива!" << endl; // Вывод сообщения об ошибке
        return false; // Возврат false, если размер недопустим
    }
    return true; // Возврат true, если размер допустим
}

// Функция для очистки ввода
void clearInput() {
    cin.clear(); // Очистка состояния потока
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование оставшихся символов в потоке
}

// Шаблонная функция для ввода значения с проверкой
template <typename T>
void inputValue(const string& prompt, T& value, bool (*checkFunc)(const T&) = nullptr) {
    while (true) { // Бесконечный цикл для повторного ввода в случае ошибки
        cout << prompt << endl; // Вывод приглашения для ввода
        cin >> value; // Ввод значения
        if (cin.good())
        {
            if (!checkFunc || checkFunc(value))
            {
                break;
            }
        }
        else { // Если ввод некорректен
            cout << "Некорректный ввод! Попробуйте снова!" << endl; // Вывод сообщения об ошибке
            clearInput(); // Очистка ввода
        }
    }
}

// Функция для ввода элементов массива
void inputMatrixElements(double** arr, size_t n) {

    cout << "Введите элементы матрицы: " << endl;

    for (size_t i = 0; i < n; ++i) { // Цикл по строкам массива
        for (size_t j = 0; j < n; ++j) { // Цикл по столбцам массива
            string prompt = "Введите (" + to_string(i) + "," + to_string(j) + ")-ый элемент"; // Формирование приглашения для ввода
            inputValue(prompt, arr[i][j]); // Ввод элемента массива с проверкой
        }
    }
}

// Функция для выделения памяти под массив
void allocateMemory(double**& matrix, size_t n) {
    matrix = new double* [n]; // Выделение памяти под массив указателей на строки
    for (size_t i = 0; i < n; ++i) { // Цикл по строкам массива
        matrix[i] = new double[n]; // Выделение памяти под строку
    }
}

// Функция для освобождения памяти массива
void deallocateMemory(double**& matrix, size_t n) {
    for (size_t i = 0; i < n; ++i) { // Цикл по строкам массива
        delete[] matrix[i]; // Удаление строки
    }
    delete[] matrix; // Удаление массива указателей
}

int dotProduct(double* arr1, double*& arr2, size_t n) {
    int product = 0;
    for (size_t i = 0; i < n; ++i) {
        product += arr1[i] * arr2[i];
    }
    return product;
}

// Функция для проверки ортонормированности матрицы
bool isOrthonormal(double**& matrix, size_t n) 
{
    for (size_t i = 0; i < n; ++i) {
        // Проверка скалярного произведения строки на саму себя
        if (dotProduct(matrix[i], matrix[i], n) != 1) {
            return false;
        }
        // Проверка скалярного произведения строки с другими строками
        for (size_t j = i + 1; j < n; ++j) {
            if (dotProduct(matrix[i], matrix[j], n) != 0) {
                return false;
            }
        }
    }
    return true;
}

void run()
{
    size_t n;

    inputValue("Введите размер квадратной матрицы: ", n, checkMatrixSize);

    double** matrix = nullptr;
    allocateMemory(matrix, n); // Выделение памяти
    inputMatrixElements(matrix, n); // ввод элементов матрицы
    
    if (isOrthonormal(matrix, n))  // проверка на ортонормированность
        cout << "Матрица является ортонормированной." << endl;
    else
        cout << "Матрица не является ортонормированной." << endl;

    deallocateMemory(matrix, n); // Освобождение памяти
}

int main()
{
    setlocale(LC_ALL, "ru");

    while (true)
    {
        run();
    }

    return 0;
}

#else
	#error "undefined solution"
#endif