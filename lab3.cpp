#define FIRST

#if defined(FIRST)

#define PI 3.14159265358980
#include <iostream>
#include <cmath>
#include <limits> // Для использования numeric_limits
using namespace std;

// Функция для ввода числа с проверкой корректности ввода
void inputNumber(const string& prompt, double& value) {
    while (true) {
        cout << prompt << endl;
        cin >> value;
        if (cin.good()) {
            break; // Если ввод корректен, выходим из цикла
        }
        else {
            cout << "Не числовой тип! Попробуйте снова!" << endl;
            cin.clear(); // Очищаем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем некорректный ввод
        }
    }
}

// Функция для проверки допустимости значения под корнем
bool checkDomain(double value) {
    if (value < 0) {
        cout << "Корень не может принимать значения меньше нуля!" << endl;
        return false;
    }
    else {
        return true;
    }
}

// Основная функция для вычислений
void calculate() {
    double a, b, h;

    // Ввод значений a, b и h
    inputNumber("Введите нижний предел промежутка (a): ", a);
    inputNumber("Введите верхний предел промежутка (b): ", b);
    inputNumber("Введите шаг (h): ", h);

    uint32_t indexNumber = 0;

    double minY = numeric_limits<double>::max();
    double maxY = numeric_limits<double>::min();

    // Цикл для вычисления значений функции на заданном промежутке
    for (double i = a; i <= b; i += h) {
        double x = a + indexNumber * h;

        double rootExpr = 15 + 10 * sin(x + PI); // Используем M_PI для значения π

        if (!checkDomain(rootExpr))
            return;

        double y = x * x * sqrt(rootExpr);

        indexNumber++;

        // Вывод результатов
        cout << "Порядковый номер: " << indexNumber << "   "
            << "Значение аргумента x: " << x << "   "
            << "Значение функции y: " << y << endl;

        // Обновление минимального и максимального значений функции
        if (minY > y) minY = y;
        if (maxY < y) maxY = y;
    }

    // Вывод минимального и максимального значений функции
    cout << "Минимальное значение функции: " << minY << endl;
    cout << "Максимальное значение функции: " << maxY << endl;

    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "ru");

    while (true)
    {
        calculate();
    }

    return 0;
}

#elif defined(SECOND)

#define PI 3.14159265358980

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Шаблонная функция для ввода числа с проверкой корректности ввода
template <typename T>
void inputNumber(const string& prompt, T& value) {
    while (true) {
        cout << prompt << endl;
        cin >> value;
        if (cin.good()) {
            break; // Если ввод корректен, выходим из цикла
        }
        else {
            cout << "Не числовой тип! Попробуйте снова!" << endl;
            cin.clear(); // Очищаем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем некорректный ввод
        }
    }
}

// Функция для вычисления суммы ряда
double calculateSum(double x, uint64_t n)
{
    double ans = 0.0;

    for (int k = 1; k <= n; k++)
    {
        ans += (pow(x, k) * cos(k * PI / 3)) / k; // Вычисляем и добавляем очередной член ряда
    }

    return ans;
}

// Функция для проверки области определения логарифма
bool checkDomain(double value)
{
    if (value > 0)
    {
        return true;
    }
    else
    {
        cout << "Логарифм не может принимать значения <= 0" << endl;
        return false;
    }
}

// Основная функция для выполнения расчетов
void calculate()
{
    double a, b, h;
    uint64_t n;

    // Ввод значений a, b, h и n
    inputNumber("Введите число a: ", a);
    inputNumber("Введите число b: ", b);
    inputNumber("Введите число h: ", h);
    inputNumber("Введите число n: ", n);

    double y, s;

    // Цикл для вычисления значений функций на интервале [a, b] с шагом h
    for (double x = a; x <= b; x += h)
    {
        s = calculateSum(x, n); // Вычисляем сумму ряда

        double valueForLog = 1 - 2 * x * cos(PI / 3) + x * x; // Вычисляем значение для логарифма

        if (!checkDomain(valueForLog))
            return; // Если значение для логарифма некорректно, выходим из функции

        y = -0.5 * log(valueForLog); // Вычисляем значение функции Y

        // Выводим результаты
        cout << setw(25) << left << "Значение функции Y: " << setw(10) << left << y
             << setw(25) << left << "Значение функции S: " << setw(10) << left << s
             << setw(35) << left << "Модуль разности значений функций: " << setw(10) << left << abs(y - s) << endl;
    }
    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "ru"); // Устанавливаем локаль для корректного отображения русских символов

    while (true)
    {
        calculate(); // Запускаем вычисления
    }

    return 0;
}

#endif
