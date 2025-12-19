#include <iostream>
#include <locale>
#include <string>
#include "module.h"

/**
 * @file main.cpp (RouteCipher)
 * @brief Главный модуль программы для шифрования методом маршрутной перестановки
 * @author Пресняков Александр
 * @version 1.0
 * @date 2025
 * @details Программа предоставляет интерактивный интерфейс для шифрования и дешифрования текста
 * методом табличной маршрутной перестановки.
 */

/**
 * @brief Проверка корректности ключа
 * @param s - строка с ключом
 * @return true если ключ валиден, false в противном случае
 * @details Ключ должен быть положительным целым числом, состоящим только из цифр
 */
bool isValidKey(const std::wstring& s) {
    if (s.empty()) return false;
    for (auto c : s) {
        if (!std::iswdigit(c)) return false;
    }
    int key = std::stoi(s);
    return key > 0;
}

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении, 1 при ошибке
 * @details Устанавливает локаль для работы с русским языком, принимает ключ от пользователя,
 * создаёт экземпляр шифра RouteCipher и предоставляет интерактивное меню для операций шифрования/дешифрования
 */
int main() {
    // Настройка локали для поддержки русского языка
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
    std::wcin.imbue(std::locale());
    
    try {
        std::wstring key_str;
        std::wcout << L"Введите ключ (количество столбцов): ";
        std::wcin >> key_str;
        std::wcin.ignore(); 
        
        // Проверка валидности ключа
        if (!isValidKey(key_str)) {
            std::wcerr << L"Ошибка: неверный ключ\n";
            std::wcerr << L"Ключ должен быть положительным целым числом (например: 3, 5, 7)\n";
            return 1;
        }
        
        // Создание экземпляра шифра с указанным ключом
        RouteCipher cipher(key_str);
        std::wcout << L"Ключ загружен: " << key_str << L" столбцов\n";
        
        // Главный цикл программы
        while (true) {
            std::wcout << L"\n=========== МЕНЮ ===========\n";
            std::wcout << L"1 - Шифровать текст\n";
            std::wcout << L"2 - Дешифровать текст\n";
            std::wcout << L"0 - Выход из программы\n";
            std::wcout << L"Выберите операцию: ";
            
            int choice;
            std::wcin >> choice;
            std::wcin.ignore();
            
            // Выход из программы
            if (choice == 0) {
                std::wcout << L"Завершение работы программы.\n";
                break;
            }
            
            // Проверка корректности выбора операции
            if (choice > 2 || choice < 0) {
                std::wcout << L"Неверная операция! Пожалуйста, выберите 0, 1 или 2\n";
                continue;
            }
            
            // Ввод текста для обработки
            std::wstring text;
            std::wcout << L"Введите текст: ";
            std::getline(std::wcin, text);
            
            try {
                if (choice == 1) {
                    // Операция шифрования
                    std::wstring encrypted = cipher.encrypt(text);
                    std::wcout << L"\nРезультат шифрования:\n";
                    std::wcout << L"Исходный текст: " << text << std::endl;
                    std::wcout << L"Зашифрованный текст: " << encrypted << std::endl;
                } else {
                    // Операция дешифрования
                    std::wstring decrypted = cipher.decrypt(text);
                    std::wcout << L"\nРезультат дешифрования:\n";
                    std::wcout << L"Исходный текст: " << text << std::endl;
                    std::wcout << L"Расшифрованный текст: " << decrypted << std::endl;
                }
            } catch (const cipher_error& e) {
                // Обработка ошибок при шифровании/дешифровании
                std::wcerr << L"\nОшибка обработки текста: " << e.what() << std::endl;
                std::wcerr << L"Пожалуйста, проверьте формат введённого текста.\n";
            }
        }
    } catch (const cipher_error& e) {
        // Обработка ошибок инициализации шифра
        std::wcerr << L"Ошибка инициализации шифра: " << e.what() << std::endl;
        std::wcerr << L"Программа завершена из-за ошибки.\n";
        return 1;
    } catch (const std::exception& e) {
        // Обработка неожиданных исключений
        std::wcerr << L"Неожиданная ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
