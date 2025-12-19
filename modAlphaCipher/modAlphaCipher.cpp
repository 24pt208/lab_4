#include "modAlphaCipher.h"
#include <algorithm>
#include <cwctype>

/**
 * @file modAlphaCipher.cpp
 * @brief Реализация класса modAlphaCipher
 * @author Пресняков Александр
 * @version 1.0
 * @date 2025
 */

/**
 * @brief Конструктор класса
 * @param skey - ключ шифрования
 * @throw cipher_error если ключ невалиден
 * @details Инициализирует алфавит и преобразует ключ в числовой вид
 */
modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    for (unsigned i=0; i<numAlpha.size(); i++) {
        alphaNum[numAlpha[i]]=i;
    }
    key = convert(getValidKey(skey));
}

/**
 * @brief Шифрование текста методом Гронсфельда
 * @param open_text - открытый текст
 * @return Зашифрованная строка
 * @throw cipher_error если текст пуст после очистки
 * @details Текст очищается, преобразуется в числа, складывается с ключом по модулю 33
 */
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> work = convert(getValidOpenText(open_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

/**
 * @brief Дешифрование текста методом Гронсфельда
 * @param cipher_text - шифртекст
 * @return Расшифрованная строка
 * @throw cipher_error если текст пуст или содержит не заглавные буквы
 * @details Выполняется обратное сложение с ключом по модулю 33
 */
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

/**
 * @brief Преобразование строки в числовой вектор
 * @param s - строка для преобразования
 * @return Вектор номеров символов
 */
std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for(auto c:s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

/**
 * @brief Преобразование числового вектора в строку
 * @param v - вектор чисел
 * @return Строка, соответствующая вектору
 */
std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for(auto i:v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

/**
 * @brief Проверка и нормализация ключа
 * @param s - исходный ключ
 * @return Ключ в верхнем регистре
 * @throw cipher_error если ключ пустой или содержит не-буквы
 */
std::wstring modAlphaCipher::getValidKey(const std::wstring& s)
{
    if (s.empty())
        throw cipher_error("Empty key");
    std::wstring tmp(s);
    for (auto & c:tmp) {
        if (!iswalpha(c))
            throw cipher_error("Invalid key");
        if (iswlower(c))
            c = towupper(c);
    }
    return tmp;
}

/**
 * @brief Проверка и очистка открытого текста
 * @param s - исходный текст
 * @return Текст в верхнем регистре без не-букв
 * @throw cipher_error если текст пуст после очистки
 */
std::wstring modAlphaCipher::getValidOpenText(const std::wstring& s)
{
    std::wstring tmp;
    for (auto c:s) {
        if (iswalpha(c)) {
            if (iswlower(c))
                tmp.push_back(towupper(c));
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
std::wstring modAlphaCipher::getValidCipherText(const std::wstring& s)
{
    if (s.empty())
        throw cipher_error("Empty cipher text");
    for (auto c:s) {
        if (!iswupper(c))
            throw cipher_error("Invalid cipher text");
    }
    return s;
}
