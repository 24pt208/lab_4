#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <locale>
#include <codecvt>

/**
 * @file modAlphaCipher.h
 * @brief Заголовочный файл класса modAlphaCipher для шифрования методом Гронсфельда
 * @author Пресняков Александр
 * @version 1.0
 * @date 2025
 * @warning Реализация для русского алфавита (33 буквы)
 */

/**
 * @brief Класс исключения для ошибок шифрования
 * @details Наследуется от std::invalid_argument
 */
class cipher_error : public std::invalid_argument {
public:
    /**
     * @brief Конструктор исключения с передачей строки
     * @param what_arg - сообщение об ошибке
     */
    explicit cipher_error(const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    
    /**
     * @brief Конструктор исключения с передачей строки (C-стиль)
     * @param what_arg - сообщение об ошибке
     */
    explicit cipher_error(const char* what_arg):
        std::invalid_argument(what_arg) {}
};

/**
 * @brief Класс для шифрования методом Гронсфельда
 * @details Использует сложение символов сообщения с символами ключа по модулю 33
 * Алфавит: АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ (33 символа)
 */
class modAlphaCipher
{
private:
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; ///< Русский алфавит по порядку
    std::map <wchar_t, int> alphaNum; ///< Ассоциативный массив "символ → номер"
    std::vector <int> key; ///< Ключ в числовом виде
    
    /**
     * @brief Преобразование строки в числовой вектор
     * @param s - строка для преобразования
     * @return Вектор чисел (номеров символов в алфавите)
     */
    std::vector<int> convert(const std::wstring& s);
    
    /**
     * @brief Преобразование числового вектора в строку
     * @param v - вектор чисел
     * @return Строка, соответствующая вектору
     */
    std::wstring convert(const std::vector<int>& v);
    
    /**
     * @brief Проверка и нормализация ключа
     * @param s - исходный ключ
     * @return Валидный ключ в верхнем регистре
     * @throw cipher_error если ключ пустой или содержит не-буквы
     */
    std::wstring getValidKey(const std::wstring& s);
    
    /**
     * @brief Проверка и нормализация открытого текста
     * @param s - исходный текст
     * @return Текст в верхнем регистре без не-букв
     * @throw cipher_error если после очистки текст пуст
     */
    std::wstring getValidOpenText(const std::wstring& s);
    
    /**
     * @brief Проверка шифртекста
     * @param s - шифртекст
     * @return Текст без изменений
     * @throw cipher_error если текст пуст или содержит не заглавные буквы
     */
    std::wstring getValidCipherText(const std::wstring& s);

public:
    modAlphaCipher() = delete; ///< Удалённый конструктор по умолчанию
    
    /**
     * @brief Конструктор с установкой ключа
     * @param skey - ключ шифрования
     * @throw cipher_error если ключ невалиден
     */
    modAlphaCipher(const std::wstring& skey);
    
    /**
     * @brief Шифрование текста
     * @param open_text - открытый текст
     * @return Зашифрованная строка
     * @throw cipher_error если текст невалиден
     */
    std::wstring encrypt(const std::wstring& open_text);
    
    /**
     * @brief Дешифрование текста
     * @param cipher_text - шифртекст
     * @return Расшифрованная строка
     * @throw cipher_error если текст невалиден
     */
    std::wstring decrypt(const std::wstring& cipher_text);
};
