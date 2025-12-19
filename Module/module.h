#pragma once
#include <string>
#include <locale>
#include <stdexcept>

/**
 * @file module.h
 * @brief Заголовочный файл класса RouteCipher для шифрования маршрутной перестановкой
 * @author Пресняков Александр
 * @version 1.0
 * @date 2025
 * @warning Реализация для работы с текстами в кодировке UTF-8 (wstring)
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
 * @brief Класс для шифрования методом маршрутной перестановки
 * @details Использует таблицу с заданным числом столбцов.
 * Запись: слева направо, сверху вниз.
 * Считывание: сверху вниз, справа налево.
 */
class RouteCipher {
private:
    int columns; ///< Количество столбцов таблицы (ключ шифрования)
    
    /**
     * @brief Проверка и нормализация ключа
     * @param s - исходный ключ (строка с числом)
     * @return Валидная строка ключа
     * @throw cipher_error если ключ пустой, содержит не цифры, или число <= 0
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
    RouteCipher() = delete; ///< Удалённый конструктор по умолчанию
    
    /**
     * @brief Конструктор с установкой ключа
     * @param key - ключ шифрования (количество столбцов)
     * @throw cipher_error если ключ невалиден
     */
    RouteCipher(const std::wstring& key);
    
    /**
     * @brief Установка нового ключа
     * @param key - новый ключ
     * @throw cipher_error если ключ невалиден
     */
    void setKey(const std::wstring& key);
    
    /**
     * @brief Получение текущего ключа
     * @return Строковое представление ключа
     */
    std::wstring getKey() const;
    
    /**
     * @brief Шифрование текста
     * @param text - открытый текст
     * @return Зашифрованная строка
     * @throw cipher_error если текст пуст после очистки
     */
    std::wstring encrypt(const std::wstring& text);
    
    /**
     * @brief Дешифрование текста
     * @param text - шифртекст
     * @return Расшифрованная строка
     * @throw cipher_error если текст пуст или содержит не заглавные буквы
     */
    std::wstring decrypt(const std::wstring& text);
};
