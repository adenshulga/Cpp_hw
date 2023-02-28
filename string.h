#pragma once

#include <cstring>
#include <iostream>

class String {

  private:
    // строку хранить буду в массиве из чаров
    // нужен указатель на массив из чаров
    char* arr = nullptr;
    // нужна переменная с количеством символов
    size_t sz = 0;
    // нужна переменная с количеством выделенной памяти
    size_t cap = 0;

  public:
    // конструктор от C-style строки
    String(const char* cs);

    // Конструктор от двух параметров: число n и символ c - создает строку из n копий символа c.
    String(size_t n, char c);
    // Конструктор по умолчанию
    String();
    // Копирующий конструктор
    String(const String& s);
    String(char c);
    // Деструктор
    ~String();
    // Оператор присваивания должен корректно обрабатывать присваивание самому себе.
    void swap(String& str);
    String& operator=(String str);
    // перегрузить оператор ввода/вывода строки

    friend std::ostream& operator<<(std::ostream& out, const String& s);
    friend std::istream& operator>>(std::istream& in, String& s);

    // методы length(), size(), capacity()
    const size_t& length() const;

    const size_t& size() const;

    const size_t& capacity() const;

    friend bool operator==(const String& s1, const String& s2);
    friend bool operator<(const String& a, const String& b);

    void push_back(char c);

    void pop_back();

    char& operator[](size_t index);

    const char& operator[](size_t index) const;

    char& front();

    const char& front() const;

    const char& back() const;

    char& back();

    String& operator+=(const String& other);

    size_t find(const String& substring) const;

    size_t rfind(const String& substring) const;

    String substr(const size_t& start, const size_t& count) const;

    bool empty() const;

    void clear();

    void shrink_to_fit();

    const char* data() const;

    char* data();
};

bool operator==(const String& s1, const String& s2);

bool operator!=(const String& s1, const String& s2);

bool operator<(const String& a, const String& b);

bool operator>(const String& a, const String& b);

bool operator>=(const String& a, const String& b);

bool operator<=(const String& a, const String& b);

std::ostream& operator<<(std::ostream& out, const String& s);

std::istream& operator>>(std::istream& in, String& s);

String operator+(String a, const String& b);
