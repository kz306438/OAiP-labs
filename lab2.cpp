#define SECOND

#ifdef FIRST

#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

// Функция для определения значения x на основе z
double defineX(double z) {
	if (z < 0) {
		cout << "Выполняется условие: z < 0" << endl;
		return z * z - z; // Если z меньше 0, возвращаем z^2 - z
	}
	else {
		cout << "Выполняется условие: z >= 0" << endl;
		return z * z * z; // Если z больше или равно 0, возвращаем z^3
	}
}

bool checkFunctionNumber(const int& value)
{
	if (value < 1 || value > 3)
	{
		cout << "Такой функции не существует! Доступные индентификаторы: 1, 2, 3" << endl;
		return false;
	}
	return true;
}

void clearInput() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

template <typename T>
void inputValue(const string& prompt, T& value, bool (*checkFunc)(const T&) = nullptr) {
	while (true) {
		cout << prompt << endl;
		cin >> value;
		if (cin.good())
		{
			if (!checkFunc || checkFunc(value))
			{
				break;
			}
		}
		else {
			cout << "Не числовой тип! Попробуйте снова!" << endl;
			clearInput();
		}
	}
}

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

// Основная функция для выполнения вычислений
void calculate() {
	double y{}, c{}, d{}, z{};
	int functionNumber; // Вводим номер функции
	inputValue("Введите индентификатор функции:\n1: 2 * x\n2: x * x\n3: x / 3", functionNumber, checkFunctionNumber);

	inputValue("Введите число c: ", c); // Вводим значение c
	inputValue("Введите число d: ", d); // Вводим значение d
	inputValue("Введите число z: ", z); // Вводим значение z

	double x = defineX(z); // Определяем значение x на основе z

	// Выбор функции для вычисления значения y
	switch (functionNumber) {
	case 1:
		cout << "Вычисления производятся в функции с индентификатором 1" << endl;
		y = pow(sin(c * 2 * x + d * d + x * x), 3); //используем функцию 1
		break;
	case 2:
		cout << "Вычисления производятся в функции с индентификатором 2" << endl;
		y = pow(sin(c * x * x + d * d + x * x), 3); //используем функцию 2
		break;
	case 3:
		cout << "Вычисления производятся в функции с индентификатором 3" << endl;
		y = pow(sin(c * x / 3 + d * d + x * x), 3); //используем функцию 3
		break;
	}

	cout << "Значение числа y, которое вычислено с использованием выбранной функции: " << y << endl << endl;
}

int main() {
	setlocale(LC_ALL, "ru"); // Устанавливаем локаль для корректного отображения русских символов

	while (true)
	{
		calculate(); // Вызываем функцию для выполнения вычислений
	}
	return 0;
}


#elif defined(SECOND)

#include <iostream>
#include <limits>

using namespace std;

// Функция для проверки деления на ноль
bool isDivisionByZero(double value) {
	if (value == 0) {
		cout << "Деление на ноль!" << endl;
		return true;
	}
	return false;
}

// Функция для ввода числа с проверкой на корректность и деление на ноль
void inputNumber(const string& prompt, double& value, bool checkForZero) {
	while (true) {
		cout << prompt << endl;
		cin >> value;

		if (cin.good()) { // Проверка, что введено число
			if (!checkForZero || !isDivisionByZero(value)) { // Проверка на деление на ноль, если требуется
				break;
			}
		}
		else {
			cout << "Не числовой тип! Попробуйте снова!" << endl;
			cin.clear(); // Очистка флага ошибки
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование некорректного ввода
		}
	}
}

// Функция для нахождения минимального из двух чисел
inline double myMin(double a, double b) {
	return (a < b) ? a : b;
}

// Функция для нахождения максимального из двух чисел
inline double myMax(double a, double b) {
	return (a > b) ? a : b;
}

// Основная функция для выполнения расчетов
void calculate() {
	double x, y, z;

	// Ввод чисел x, y и z
	inputNumber("Введите число x: ", x, false);
	inputNumber("Введите число y: ", y, false);
	inputNumber("Введите число z: ", z, true);

	// Вычисление числителя и знаменателя
	double numerator = myMin(x + y + z, x * y * z);
	double denominator = myMin(x - y + z, x * y / z);

	// Проверка деления на ноль и вывод результата
	if (!isDivisionByZero(denominator)) {
		cout << "Результат вычислений: " << numerator / denominator << endl << endl;
	}
}

int main() {
	setlocale(LC_ALL, "ru"); // Установка локали для корректного отображения русских символов

	while (true) {
		calculate(); // Запуск расчетов в бесконечном цикле
	}

	return 0;
}


#else
#error "unknown project!"
#endif 



