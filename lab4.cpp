#define FIRST

#if defined(FIRST)

#include <iostream>
#include <limits>

using namespace std;

// Функция для нахождения индекса минимального элемента в массиве
int findIndexOfMinElement(double* arr, size_t n)
{
	double minElement = numeric_limits<double>::max();
	size_t index = -1;

	for (size_t i = 0; i < n; i++)
	{
		if (minElement >= arr[i])
		{
			minElement = arr[i];
			index = i;
		}
	}

	return index;
}

// Функция для ввода размера массива
void inputArraySize(size_t& n)
{
	cout << "Введите размер массива: " << endl;

	bool isCorrect = false;
	while (!isCorrect)
	{
		cin >> n;
		if (n < 1)
		{
			cout << "Недопустимое количество элементов массива!" << endl;
			cout << "Введите размер массива: " << endl;
		}
		else
		{
			isCorrect = true;
		}
	}
}

// Функция для ввода элементов массива
void inputArrayElements(double* arr, size_t n)
{
	cout << "Введите элементы массива: " << endl;

	for (size_t i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
}

// Функция для нахождения суммы элементов массива до минимального элемента
double findSum(double* arr, size_t n)
{
	double sum = 0.0;

	for (size_t i = 0; i < n; i++)
	{
		sum += arr[i];
	}

	return sum;
}

// Основная функция для выполнения расчетов
void calculate()
{
	size_t n;
	inputArraySize(n);

	double* arr = new double[n];
	inputArrayElements(arr, n);

	size_t index = findIndexOfMinElement(arr, n);
	double sumOfElements = findSum(arr, index);

	cout << "Сумма элементов массива, расположенных до минимального элемента: " << sumOfElements << endl << endl;

	delete[] arr; // Освобождение памяти
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

#include <iostream>
#include <limits>
#include <string>
#include <random>
#include <iomanip>

using namespace std;

// Функция для проверки размера массива
bool checkArraySize(const size_t& n)
{
	if (n < 2)
	{
		cout << "Недопустимое количество элементов массива!" << endl;
		return false;
	}
	else
	{
		return true;
	}
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
		if (cin.good()) {
			if (!checkFunc || checkFunc(value))
				break;
		}
		else {
			cout << "Некорректный ввод! Попробуйте снова!" << endl;
			clearInput();
		}
	}
}

// Функция для ввода элементов массива
void inputArrayElements(double* arr, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		string prompt = "Введите " + to_string(i) + "-ый элемент";
		inputValue(prompt, arr[i]);
	}
}

// Функция для поиска первого элемента, удовлетворяющего условию
size_t findFirst(double* arr, size_t n, bool (*condition)(double)) {
	for (size_t i = 0; i < n; i++) {
		if (condition(arr[i])) {
			return i;
		}
	}
	return n; // Возвращаем n, если элемент не найден
}

// Функция для проверки, является ли значение отрицательным
bool isNegative(double value) {
	return value < 0;
}

// Функция для проверки, является ли значение положительным
bool isPositive(double value) {
	return value > 0;
}


// Функция проверяет, есть ли в массиве элемент, удовлетворяющий условию
bool hasElement(double* arr, size_t n, bool (*condition)(double)) {
	for (size_t i = 0; i < n; i++) {
		if (condition(arr[i])) {
			return true; // Возвращает true, если найден элемент, удовлетворяющий условию
		}
	}
	return false; // Возвращает false, если таких элементов нет
}

// Функция вычисляет сумму элементов массива от индекса li до индекса ri включительно
double calculateSum(double* arr, size_t li, size_t ri)
{
	double sum = 0.0;

	for (size_t i = li; i <= ri; i++)
	{
		sum += arr[i]; // Добавляет значение текущего элемента к сумме
	}

	return sum; // Возвращает вычисленную сумму
}

void inputCommand(string& comand)
{
	// Выводим запрос на использование автоматического заполнения массива случайными числами
	cout << "Использовать автоматическое заполнение массива случайными числами?" << endl;
	cout << "[Y/n]" << endl;

	bool isCorrect = false;

	// Пока команда не будет корректной
	while (!isCorrect)
	{
		// Считываем команду пользователя
		cin >> comand;

		// Проверяем, является ли команда корректной
		if (comand == "Y" || comand == "n")
			isCorrect = true;
		else
			// Если команда некорректна, выводим сообщение об ошибке
			cout << "Команда не распознана!" << endl;
	}
}

void fillArrayRandomNum(double* arr, size_t n) {
	// Создаем генератор случайных чисел
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(-100.0, 100.0); // для равномерного распределения чисел

	// Заполняем массив случайными числами в диапазоне от -100.0 до 100.0
	for (size_t i = 0; i < n; ++i) {
		arr[i] = dis(gen);
	}
}

void printArray(const double* arr, size_t n) {
	// Выводим элементы массива
	cout << "Элементы массива: " << endl;
	for (size_t i = 0; i < n; ++i) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}

void handleArrayInput(double* arr, size_t n, const std::string& command) {
	// Если команда "Y", заполняем массив случайными числами и выводим его
	if (command == "Y") {
		fillArrayRandomNum(arr, n);
		printArray(arr, n);
	}
	// Если команда "n", запрашиваем ввод элементов массива у пользователя
	else if (command == "n") {
		inputArrayElements(arr, n);
	}
}

bool checkArrayElements(double* arr, size_t n) {
	// Проверяем, содержит ли массив отрицательные элементы
	bool hasNegative = hasElement(arr, n, isNegative);
	// Проверяем, содержит ли массив положительные элементы
	bool hasPositive = hasElement(arr, n, isPositive);

	// Если массив не содержит отрицательных элементов, выводим сообщение и возвращаем false
	if (!hasNegative) {
		cout << "Массив не содержит отрицательных элементов!" << endl;
		return false;
	}

	// Если массив не содержит положительных элементов, выводим сообщение и возвращаем false
	if (!hasPositive) {
		cout << "Массив не содержит положительных элементов!" << endl;
		return false;
	}

	// Если массив содержит и отрицательные, и положительные элементы, возвращаем true
	return true;
}

double calculateSumBetweenElements(double* arr, size_t n) {
	// Находим индекс первого отрицательного элемента
	size_t leftIndex = findFirst(arr, n, isNegative);
	// Находим индекс первого положительного элемента
	size_t rightIndex = findFirst(arr, n, isPositive);

	// Если индекс отрицательного элемента больше индекса положительного, меняем их местами
	if (leftIndex > rightIndex) {
		swap(leftIndex, rightIndex);
	}

	// Вычисляем сумму элементов между найденными индексами
	return calculateSum(arr, leftIndex, rightIndex);
}


void calculate() {
	string command;
	inputCommand(command); // Ввод команды

	size_t n;
	inputValue("Введите количество элементов массива:", n, checkArraySize); // Ввод количества элементов массива с проверкой размера

	double* arr = new double[n];
	handleArrayInput(arr, n, command); // Ввод элементов массива в зависимости от команды

	if (!checkArrayElements(arr, n)) { // Проверка элементов массива
		delete[] arr; // Освобождение памяти, если проверка не пройдена
		return;
	}

	double sum = calculateSumBetweenElements(arr, n); // Вычисление суммы элементов между первым положительным и первым отрицательным элементами
	cout << "Сумма элементов, расположенных между первым положительным и первым отрицательным элементами: " << sum << endl << endl;

	delete[] arr; // Освобождение памяти
}

int main() {
	setlocale(LC_ALL, "ru"); // Установка локали для корректного отображения русских символов

	while (true) {
		calculate(); // Вызов функции calculate в бесконечном цикле
	}

	return 0;
}


#elif defined(THIRD)

#include <iostream> // Подключение библиотеки для работы с вводом-выводом
#include <string> // Подключение библиотеки для работы со строками
#include <algorithm> // Подключение библиотеки для работы с алгоритмами (например, сортировка)
#include <limits> // Подключение библиотеки для работы с числовыми пределами

using namespace std; // Использование пространства имен std для упрощения записи

// Функция для проверки размера массива
bool checkArraySize(const size_t& n) {
	if (n < 1) { // Проверка, что размер массива больше 0
		cout << "Недопустимое количество элементов массива!" << endl; // Вывод сообщения об ошибке
		return false; // Возврат false, если размер массива недопустим
	}
	return true; // Возврат true, если размер массива допустим
}

// Функция для очистки ввода
void clearInput() {
	cin.clear(); // Очистка флага ошибки ввода
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование оставшихся символов в буфере ввода
}

// Шаблонная функция для ввода значения с проверкой
template <typename T>
void inputValue(const string& prompt, T& value, bool (*checkFunc)(const T&) = nullptr) {
	while (true) { // Бесконечный цикл для повторного ввода в случае ошибки
		cout << prompt << endl; // Вывод приглашения для ввода
		cin >> value; // Ввод значения
		if (cin.good()) { // Проверка, что ввод успешен
			if (!checkFunc || checkFunc(value)) // Проверка значения с помощью функции, если она задана
				break; // Выход из цикла, если ввод корректен
		}
		else {
			cout << "Некорректный ввод! Попробуйте снова!" << endl; // Вывод сообщения об ошибке
			clearInput(); // Очистка ввода
		}
	}
}

// Функция для ввода элементов массива
void inputArrayElements(double* arr, size_t n) {
	for (size_t i = 0; i < n; i++) { // Цикл по всем элементам массива
		string prompt = "Введите " + to_string(i) + "-ый элемент"; // Формирование строки приглашения для ввода
		inputValue(prompt, arr[i]); // Ввод значения элемента массива
	}
}

// Функция для сортировки двух массивов
void sortArrays(double* arr1, double* arr2, size_t n) {
	sort(arr1, arr1 + n); // Сортировка первого массива
	sort(arr2, arr2 + n); // Сортировка второго массива
}

// Функция для нахождения и вывода первого уникального элемента
void findAndPrintFirstUniqueElement(double* arr1, double* arr2, size_t n) {
	size_t i = 0, j = 0; // Инициализация индексов для обоих массивов
	while (i < n && j < n) { // Цикл до конца одного из массивов
		if (arr1[i] < arr2[j]) { // Если элемент первого массива меньше элемента второго
			cout << "Наименьший элемент в первом массиве, который не входит во второй: " << arr1[i] << endl; // Вывод уникального элемента
			return; // Завершение функции
		}
		else if (arr1[i] == arr2[j]) { // Если элементы равны
			i++; // Переход к следующему элементу первого массива
			j++; // Переход к следующему элементу второго массива
		}
		else { // Если элемент первого массива больше элемента второго
			j++; // Переход к следующему элементу второго массива
		}
	}

	if (i < n) // Если остались элементы в первом массиве
		cout << "Наименьший элемент в первом массиве, который не входит во второй: " << arr1[i] << endl; // Вывод уникального элемента
	else
		cout << "Все элементы первого массива присутствуют во втором массиве." << endl; // Сообщение, что все элементы первого массива присутствуют во втором
}

// Основная функция для нахождения первого уникального элемента
void findFirstUniqueElement() {
	size_t n; // Переменная для хранения размера массива
	inputValue("Введите количество элементов массива:", n, checkArraySize); // Ввод размера массива с проверкой

	double* arr1 = new double[n]; // Выделение памяти для первого массива
	cout << "Введите элементы первого массива: " << endl; // Сообщение для пользователя
	inputArrayElements(arr1, n); // Ввод элементов первого массива

	double* arr2 = new double[n]; // Выделение памяти для второго массива
	cout << "Введите элементы второго массива: " << endl; // Сообщение для пользователя
	inputArrayElements(arr2, n); // Ввод элементов второго массива

	sortArrays(arr1, arr2, n); // Сортировка обоих массивов
	findAndPrintFirstUniqueElement(arr1, arr2, n); // Нахождение и вывод первого уникального элемента

	delete[] arr1; // Освобождение памяти первого массива
	delete[] arr2; // Освобождение памяти второго массива
}


int main() {
	setlocale(LC_ALL, "ru");

	while (true) {
		findFirstUniqueElement();
	}

	return 0;
}


#else
	#error "project is undefined!"
#endif