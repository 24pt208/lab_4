#include <iostream>
#include <locale>
#include <codecvt>
#include "modAlphaCipher.h"

/**
 * @file main.cpp
 * @brief Главный модуль программы для тестирования шифра Гронсфельда
 * @author Пресняков Александр
 * @version 1.0
 * @date 2025
 */

/**
 * @brief Функция для проверки работы шифра
 * @param Text - исходный текст
 * @param key - ключ шифрования
 * @param destructCipherText - флаг для порчи шифртекста (тестирование обработки ошибок)
 * @details Шифрует текст, опционально портит его, затем расшифровывает и сравнивает
 */
void check(const std::wstring& Text, const std::wstring& key, bool destructCipherText = false)
{
    try {
        std::wstring cipherText;
        std::wstring decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text);
        
        if (destructCipherText)
            cipherText[0] = towlower(cipherText[0]);
            
        decryptedText = cipher.decrypt(cipherText);
        
        std::wcout << L"key=" << key << std::endl;
        std::wcout << L"Text=" << Text << std::endl;
        std::wcout << L"cipherText=" << cipherText << std::endl;
        std::wcout << L"decryptedText=" << decryptedText << std::endl;
        
        if (Text == decryptedText)
            std::wcout << L"Ok\n";
        else
            std::wcout << L"Err\n";
            
    } catch (const cipher_error& e) {
        std::wcout << L"Error: " << e.what() << std::endl;
    }
    std::wcout << std::endl;
}

/**
 * @brief Интерактивный режим работы программы
 * @details Позволяет пользователю вводить ключ, шифровать/дешифровать тексты
 * и запускать автоматическое тестирование
 */
void interactiveMode()
{
    std::wstring key;
    std::wcout << L"Введите ключ: ";
    std::getline(std::wcin, key);
    
    try {
        modAlphaCipher cipher(key);
        std::wcout << L"Ключ успешно установлен!" << std::endl;
        
        int operation;
        do {
            std::wcout << L"\nВыберите операцию:\n";
            std::wcout << L"1 - Зашифровать текст\n";
            std::wcout << L"2 - Расшифровать текст\n"; 
            std::wcout << L"3 - Протестировать (как в методичке)\n";
            std::wcout << L"0 - Выход\n";
            std::wcout << L"Ваш выбор: ";
            std::wcin >> operation;
            std::wcin.ignore();
            
            if (operation == 1 || operation == 2) {
                std::wstring text;
                std::wcout << L"Введите текст: ";
                std::getline(std::wcin, text);
                
                try {
                    if (operation == 1) {
                        std::wstring result = cipher.encrypt(text);
                        std::wcout << L"Зашифрованный текст: " << result << std::endl;
                    } else {
                        std::wstring result = cipher.decrypt(text);
                        std::wcout << L"Расшифрованный текст: " << result << std::endl;
                    }
                } catch (const cipher_error& e) {
                    std::wcout << L"Error: " << e.what() << std::endl;
                }
            } else if (operation == 3) {
                std::wcout << L"\n=== Автоматическое тестирование ===" << std::endl;
                check(L"ПРИВЕТ", key);
                check(L"ПРИВЕТ", L"ЭХО123");
                check(L"ПРИВЕТ", L"");
                check(L"123456", key);
                check(L"", key);
                check(L"ПРИВЕТ", key, true);
            } else if (operation != 0) {
                std::wcout << L"Неверная операция!" << std::endl;
            }
            
        } while (operation != 0);
        
    } catch (const cipher_error& e) {
        std::wcout << L"Error: " << e.what() << std::endl;
        std::wcout << L"Программа завершена из-за ошибки в ключе." << std::endl;
    }
}

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении
 * @details Устанавливает локаль и запускает интерактивный режим
 */
int main()
{
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
    
    std::wcout << L"=== Шифр Гронсфельда с обработкой ошибок ===" << std::endl;
    interactiveMode();
    
    return 0;
}
