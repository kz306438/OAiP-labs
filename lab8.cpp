#define FIRST

#if defined(FIRST)

#include <iostream>
#include <math.h>
#include <climits>
#include <corecrt_math_defines.h>

using namespace std;

// Функция для очистки ввода
void clearInput() 
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Шаблонная функция для ввода значения с проверкой
template <typename T>
void inputValue(const string& prompt, T& value, bool (*checkFunc)(const T&) = nullptr) 
{
    while (true) 
    {
        cout << prompt << '\n';
        cin >> value;
        if (cin.good()) {
            if (!checkFunc || checkFunc(value)) 
            {
                break;
            }
        }
        else {
            cout << "Некорректный ввод! Попробуйте снова!\n";
            clearInput();
        }
    }
}

// Проверка номера функции
bool checkFunctionNumber(const int& value) 
{
    if (value < 1 || value > 3)
    {
        cout << "Такой функции не существует!\n";
        return false;
    }
    return true;
}

// Проверка значения N
bool check_N(const double& value) 
{
    if (value < 1)
    {
        cout << "Число N не может быть меньше единицы!\n";
        return false;
    }
    return true;
}

// Проверка значения h
bool check_H(const double& value) 
{
    if (value == 0) 
    {
        cout << "Число h не может быть равно нулю!\n";
        return false;
    }
    return true;
}

// Проверка корректности введенных данных
bool checkInputData(double a, double b, double h)
{
    if (h > 0) 
    {
        if (b < a) 
        {
            cout << "Число b не может быть меньше числа a, при h > 0!\n";
            return false;
        }
    }
    else
    {
        if (a < b) 
        {
            cout << "Число a не может быть меньше числа b, при h < 0\n!";
            return false;
        }
    }
    return true;
}

// Первая функция для вычислений
double firstFunction(double x, double n) 
{
    double sum = 0.0;
    double p = 1;
    
    for (double k = 1; k <= n; k++)
    {
        p *= x;
        sum += (p / k * cos(k * M_PI / 3.0));
    }

    return sum;
}

// Вторая функция для вычислений
double secondFunction(double x, double n) 
{
    double cos_value = cos(M_PI / 3);
    double expression = 1 - 2 * x * cos_value + x * x;
    return -0.5 * log(expression);
}

// Третья функция для вычислений
double thirdFunction(double x, double n) 
{
    return fabs(firstFunction(x, n) - secondFunction(x, n));
}

// Функция для вывода результатов
void Out_Rez(double (*func)(double, double), double a, double b, double h, double n) 
{
    int i = 1;
    for (double x = a; x <= b; x += h) 
    {
        cout << i << ": \t" << func(x, n) << '\n';
        i++;
    }
    cout << '\n';
}

// Функция для выполнения расчетов
void calculate(int functionNumber, double a, double b, double h, double n) 
{
    switch (functionNumber) 
    {
    case 1:
        cout << "Вызвана функция: S(X) = x^k * cos(k * PI / 3) / k\nЕё результаты:\n\n";
        Out_Rez(firstFunction, a, b, h, n);
        break;
    case 2:
        cout << "Вызвана функция: Y(x) = -0.5 * ln(1 - 2 * x * cos(PI / 3) + x^2)\nЕё результаты:\n\n";
        Out_Rez(secondFunction, a, b, h, n);
        break;
    case 3:
        cout << "Вызвана функция: |S(X) - Y(x)|\nЕё результаты:\n\n";
        Out_Rez(thirdFunction, a, b, h, n);
        break;
    }
}

// Основная функция для запуска программы
void run() 
{
    int functionNumber;
    string prompt = "Доступные функции для расчётов:\n\t1 - S(X) = x^k * cos(k * PI / 3) / k\n\t2 - Y(x) = -0.5 * ln(1 - 2 * x * cos(PI / 3) + x^2)\n\t3 - |S(X) - Y(x)|\nВведите номер функции:";
    inputValue(prompt, functionNumber, checkFunctionNumber);

    double a, b, h, n;
    inputValue("Введите число а:", a);
    inputValue("Введите число b:", b);
    inputValue("Введите число h:", h, check_H);
    inputValue("Введите число n:", n, check_N);

    cout << '\n';

    if (!checkInputData(a, b, h)) return;

    calculate(functionNumber, a, b, h, n);

    cout << '\n';
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

#elif defined(SECOND)

#include <iostream>
#include <cmath>

using namespace std;

// Функция для очистки ввода
void clearInput()
{
    cin.clear(); // Сбрасываем состояние потока
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем оставшиеся символы в потоке
}

// Шаблонная функция для ввода значения с проверкой
template <typename T>
void inputValue(const string& prompt, T& value, bool (*checkFunc)(const T&) = nullptr)
{
    while (true)
    {
        cout << prompt << '\n'; // Выводим приглашение для ввода
        cin >> value; // Считываем значение
        if (cin.good()) { // Проверяем, успешно ли считано значение
            if (!checkFunc || checkFunc(value)) // Если передана функция проверки, вызываем её
            {
                break; // Выходим из цикла, если значение корректно
            }
        }
        else {
            cout << "Некорректный ввод! Попробуйте снова!\n"; // Сообщаем об ошибке ввода
            clearInput(); // Очищаем ввод
        }
    }
}

// Функция для проверки допустимости значения подкорневого выражения
bool checkSqrtDomain(const double& value)
{
    if (value < 0) // Проверяем, что значение не отрицательное
    {
        cout << "Подкорневое выражение не может быть меньше нуля!" << endl; // Сообщаем об ошибке
        return false; // Возвращаем false, если значение некорректно
    }

    return true; // Возвращаем true, если значение корректно
}

// Рекурсивная функция для вычисления квадратного корня
double mySqrtRec(double a, double x_n, double epsilon)
{
    double x_n1 = 0.5 * (x_n + a / x_n); // Вычисляем новое приближение
    if (abs(x_n1 - x_n) < epsilon) // Проверяем условие остановки
    {
        return x_n1; // Возвращаем результат, если достигнута точность
    }
    return mySqrtRec(a, x_n1, epsilon); // Рекурсивно вызываем функцию с новым приближением
}

// Функция для вычисления квадратного корня с заданной точностью
double mySqrt(double a, double epsilon = 1e-7)
{
    return mySqrtRec(a, 0.5 * (1 + a), epsilon); // Вызываем рекурсивную функцию с начальным приближением
}

// Функция для выполнения вычислений
void calculate()
{
    double a;
    inputValue("Введите число a:", a, checkSqrtDomain); // Вводим значение с проверкой

    cout << "Результат рекурсивной реализации функции корня:" << endl;

    if (a)
        cout << mySqrt(a) << endl;
    else
        cout << 0 << endl;

    cout << endl;

    cout << "Результат классической реализации функции корня" << endl;
    cout << sqrt(a) << endl; // Выводим результат стандартной функции sqrt

    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "ru"); // Устанавливаем локаль для корректного отображения русского текста

    while (true)
    {
        calculate(); // Запускаем вычисления в бесконечном цикле
    }

    return 0; // Завершаем программу
}


#else
	#error
#endif