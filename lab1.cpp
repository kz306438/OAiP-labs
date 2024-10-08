#define THIRD

#if defined(FIRST)

#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

// Функция для проверки, является ли число отрицательным
bool checkForNegativeNumber(double value) {
    if (value < 0) {
        cout << "Нельзя взять корень из отрицательного числа! Попробуйте снова!" << endl;
        return true; // Возвращает true, если число отрицательное
    }
    return false; // Возвращает false, если число не отрицательное
}

// Функция для ввода числа с проверкой корректности ввода
void inputNumber(const string& prompt, double& value) {
    bool isCorrect = false;
    while (!isCorrect) {
        cout << prompt << endl;
        cin >> value;
        if (cin.good()) { // Проверка, корректно ли введено число
            if (!checkForNegativeNumber(value))
                isCorrect = true; // Если число корректное и не отрицательное, выход из цикла
        }
        else {
            cout << "Не числовой тип! Попробуйте снова!" << endl;
            cin.clear(); // Очистка состояния потока
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование некорректного ввода
        }
    }
}

// Функция для вычисления значений z1 и z2
void calculate(double& z1, double& z2, double a, double b) {
    // Вычисление числителя и знаменателя для z1
    double numeratorOfZ1 = (a - 1) * sqrt(a) - (b - 1) * sqrt(b);
    double denominatorOfZ1 = sqrt(pow(a, 3) * b) + a * b + a * a - a;

    // Вычисление числителя и знаменателя для z2
    double numeratorOfZ2 = sqrt(a) - sqrt(b);
    double denominatorOfZ2 = a;

    // Проверка на деление на ноль
    if (denominatorOfZ1 == 0 || denominatorOfZ2 == 0) {
        cout << "Деление на 0!" << endl;
        return;
    }

    // Вычисление значений z1 и z2
    z1 = numeratorOfZ1 / denominatorOfZ1;
    z2 = numeratorOfZ2 / denominatorOfZ2;

    // Вывод результатов
    cout << "Результат первого выражения: " << z1 << endl;
    cout << "Результат второго выражения: " << z2 << endl;
}

int main() {
    setlocale(LC_ALL, "ru"); // Установка локали для вывода на русском языке

    double z1, z2, a, b;
    inputNumber("Введите первое число: ", a); // Ввод первого числа
    inputNumber("Введите второе число: ", b); // Ввод второго числа

    calculate(z1, z2, a, b); // Вычисление значений z1 и z2

    return 0; // Завершение программы
}

#elif defined(SECOND)

#include <iostream> // Подключение библиотеки для ввода-вывода
#include <cmath>    // Подключение библиотеки для математических функций

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru"); // Установка локали для корректного отображения русского языка

	double z1, z2, a, b; // Объявление переменных для хранения значений

	cout << "Введите число а: " << endl;
	cin >> a; // Ввод значения для переменной a

	cout << "Введите число b: " << endl;
	cin >> b; // Ввод значения для переменной b

	// Вычисление значения z1 по заданной формуле
	z1 = pow(cos(a), 4) + pow(sin(b), 2) + (pow(sin(2 * a), 2) / 4) - 1;
	// Вычисление значения z2 по заданной формуле
	z2 = sin(b + a) * sin(b - a);

	// Вывод значений z1 и z2 на экран
	cout << "число z1 = " << z1 << endl;
	cout << "число z2 = " << z2 << endl;

	return 0; // Завершение программы
}

#elif defined(THIRD)

#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.1415926 // Определение константы PI

// Функция для очистки ввода
void clearInput() {
    cin.clear();
    cin.ignore(999, '\n');
}

// Функция для проверки значения x
bool checkX(const double& value)
{
    bool isCorrect = true;
    if (value < 0 || value > PI)
    {
        cout << "Число x не соответствует области орпеделения функции arccos!" << endl;
        isCorrect = false;
    }

    if (value <= -1 * PI / 2 || value >= PI / 2)
    {
        cout << "Число x не соответсвует области определения функции arctan!" << endl;
        isCorrect = false;
    }

    return isCorrect;
}

// Шаблонная функция для ввода значения с проверкой
template <typename T>
void inputValue(const string& prompt, T& value, bool (*checkFunc)(const T&) = nullptr) {
    while (true) {
        cout << prompt << endl; // Вывод приглашения для ввода
        cin >> value; // Ввод значения
        if (cin.good())
        {
            if (!checkFunc || checkFunc(value))
            {
                break; // Выход из цикла, если ввод корректен
            }
        }
        else {
            cout << "Некорректный ввод! Попробуйте снова!" << endl;
            clearInput(); // Очистка ввода в случае ошибки
        }
    }
}

// Функция для выполнения расчетов
void calculate()
{
    double x, y, z;

    inputValue("Введите число x:", x, checkX); // Ввод x с проверкой
    inputValue("Введите число y:", y); // Ввод y без проверки
    inputValue("Введите число z:", z); // Ввод z без проверки

    double numerator; // Числитель
    double denominator; // Знаменатель

    numerator = x + (3 * abs(x - y)) + pow(x, 2); // Вычисление числителя
    denominator = abs(x - y) * z + pow(x, 2); // Вычисление знаменателя

    if (denominator == 0)
    {
        cout << "Деление на нуль!" << endl;
        return; // Завершение функции при делении на нуль
    }

    double answer = 5 * atan(x) - (acos(x) / 4) * (numerator / denominator); // Вычисление ответа

    cout << "Решение уравнения: " << answer << endl; // Вывод результата
    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "ru"); // Установка локали для корректного отображения русского языка

    while (true)
    {
        calculate(); // Вызов функции calculate в бесконечном цикле
    }

    return 0;
}


#else
    #error "undefined project"
#endif