#include "module.h"
#include <stdexcept>
#include <locale>
#include <string>
#include <cwctype>

/**
 * @file module.cpp
 * @brief Реализация класса RouteCipher
 * @author Пресняков Александр
 * @version 1.0
 * @date 2025
 */

/**
 * @brief Конструктор RouteCipher
 * @param key - ключ шифрования (количество столбцов)
 * @throw cipher_error если ключ невалиден
 */
RouteCipher::RouteCipher(const std::wstring& key) {
    std::wstring valid_key = getValidKey(key);
    columns = std::stoi(valid_key);
}

/**
 * @brief Проверка ключа на валидность
 * @param s - исходный ключ
 * @return Нормализованная строка ключа
 * @throw cipher_error если ключ невалиден
 */
std::wstring RouteCipher::getValidKey(const std::wstring& s) {
    if (s.empty())
        throw cipher_error("Empty key");
    
    for (auto c : s) {
        if (!std::iswdigit(c))
            throw cipher_error("Invalid key - must contain only digits");
    }
    
    int key_value = std::stoi(s);
    if (key_value <= 0)
        throw cipher_error("Key must be greater than 0");
    
    return s;
}

/**
 * @brief Проверка и очистка открытого текста
 * @param s - исходный текст
 * @return Текст в верхнем регистре без не-букв
 * @throw cipher_error если текст пуст после очистки
 */
std::wstring RouteCipher::getValidOpenText(const std::wstring& s) {
    std::wstring tmp;
    for (auto c : s) {
        if (std::iswalpha(c)) {
            if (std::iswlower(c))
                tmp.push_back(std::towupper(c));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}

/**
 * @brief Проверка шифртекста
 * @param s - шифртекст
 * @return Текст без изменений
 * @throw cipher_error если текст пуст или содержит не заглавные буквы
 */
std::wstring RouteCipher::getValidCipherText(const std::wstring& s) {
    if (s.empty())
        throw cipher_error("Empty cipher text");
    
    for (auto c : s) {
        if (!std::iswupper(c))
            throw cipher_error("Invalid cipher text - must contain only uppercase letters");
    }
    return s;
}

/**
 * @brief Установка нового ключа
 * @param key - новый ключ
 * @throw cipher_error если ключ невалиден
 */
void RouteCipher::setKey(const std::wstring& key) {
    std::wstring valid_key = getValidKey(key);
    columns = std::stoi(valid_key);
}

/**
 * @brief Получение текущего ключа
 * @return Строковое представление ключа
 */
std::wstring RouteCipher::getKey() const {
    return std::to_wstring(columns);
}

/**
 * @brief Шифрование текста методом маршрутной перестановки
 * @param text - открытый текст
 * @return Зашифрованная строка
 * @throw cipher_error если текст пуст после очистки
 */
std::wstring RouteCipher::encrypt(const std::wstring& text) {
    std::wstring clean_text = getValidOpenText(text);
    
    std::size_t text_length = clean_text.length();
    std::size_t rows = (text_length + columns - 1) / columns;
    std::wstring result;
    
    for (int col = columns - 1; col >= 0; col--) {
        for (std::size_t row = 0; row < rows; row++) {
            std::size_t pos = row * columns + col;
            if (pos < text_length) {
                result += clean_text[pos];
            }
        }
    }
    return result;
}

/**
 * @brief Дешифрование текста методом маршрутной перестановки
 * @param text - шифртекст
 * @return Расшифрованная строка
 * @throw cipher_error если текст пуст или содержит не заглавные буквы
 */
std::wstring RouteCipher::decrypt(const std::wstring& text) {
    std::wstring clean_text = getValidCipherText(text);
   
    std::size_t text_length = clean_text.length();
    std::size_t rows = (text_length + columns - 1) / columns;
    std::wstring result(text_length, L' ');
    std::size_t index = 0;

    for (int col = columns - 1; col >= 0; col--) {
        for (std::size_t row = 0; row < rows; row++) {
            std::size_t pos = row * columns + col;
            if (pos < text_length && index < text_length) {
                result[pos] = clean_text[index++];
            }
        }
    }
    return result;
}
