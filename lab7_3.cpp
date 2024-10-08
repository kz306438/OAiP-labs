#include <string>
#include <windows.h>
#include <fstream>
#include <iostream>

using namespace std;

const string PATH_TO_ENCRYPTED_DATA = "encrypted_data.txt";

// Функция для проверки, является ли символ гласной буквой
bool isVowelLetter(char ch) {
    ch = toupper(static_cast<unsigned char>(ch));
    return (ch == 'А' || ch == 'Я' || ch == 'У' || ch == 'Ю' || ch == 'О' ||
        ch == 'Ё' || ch == 'Ы' || ch == 'И' || ch == 'Э' || ch == 'Е' ||
        ch == 'а' || ch == 'я' || ch == 'у' || ch == 'ю' || ch == 'о' ||
        ch == 'ё' || ch == 'ы' || ch == 'и' || ch == 'э' || ch == 'е' ||
        ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' || ch == 'Y');
}

// Функция для шифрования данных
string encode(const string& data) 
{
    string encryptedData;
    encryptedData.reserve(2 * data.size());

    for (char ch : data) {
        encryptedData += ch;
        if (isVowelLetter(ch)) {
            encryptedData += 'с';
        }
    }
    cout << "Строка зашифрована!"    << endl
         << "Зашифрованная строка: " << endl
         << encryptedData << endl    << endl;

    return encryptedData;
}

// Функция для записи данных в файл
void writeDataToFile(const string& data, const string& path) 
{
    ofstream file(path);
    if (file.is_open()) 
    {
        file << data;
        file.close();
    }
    else {
        cout << "Ошибка открытия файла: " << path << endl;
    }
}

// Функция для чтения данных из файла
string readDataFromFile(const string& path) 
{
    ifstream file(path);
    string data;
    if (file.is_open()) {
        file >> data;
        file.close();
    }
    else {
        cout << "Ошибка открытия файла: " << path << endl;
    }
    return data;
}

// Функция для расшифровки данных
string decode(const string& encryptedData)
{
    string decryptedData;
    decryptedData.reserve(encryptedData.size());

    for (size_t i = encryptedData.size() - 1; i > 0; i--) {
        if (encryptedData[i] == 'с' && isVowelLetter(encryptedData[i - 1]))
        {
            continue;
        }
        decryptedData += encryptedData[i];
    }
    decryptedData += encryptedData[0];

    reverse(decryptedData.begin(), decryptedData.end());

    cout << "Строка расшифрована!" << endl;
    return decryptedData;
}

// Функция для ввода данных от пользователя
string input()
{
    string data;
    do {
        cout << "Введите данные, которые необходимо зашифровать:" << endl;
        getline(cin, data);
    } while (data.empty());

    cout << endl;

    return data;
}

// Основная функция для запуска шифрования и расшифровки
void run() 
{
    string inputData = input();
    string encryptedData = encode(inputData);
    writeDataToFile(encryptedData, PATH_TO_ENCRYPTED_DATA);

    string readEncryptedData = readDataFromFile(PATH_TO_ENCRYPTED_DATA);
    string outputData = decode(readEncryptedData);
    cout << "Расшифрованная строка:" << endl;
    cout << outputData << endl << endl;
    writeDataToFile(outputData, "output.txt");
}

int main()
{
    SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
    SetConsoleOutputCP(1251);

    while (true) {
        run();
    }

    return 0;
}
