#include "string.h"

#include <cstring>
#include <iostream>

// строку хранить буду в массиве из чаров

// конструктор от C-style строки
String::String(const char* cs)
    : arr(new char[std::strlen(cs) + 1]),
      sz(std::strlen(cs)),
      cap(std::strlen(cs)) {
    memcpy(arr, cs, cap);
    arr[sz] = '\0';
}

// Конструктор от двух параметров: число n и символ c - создает строку из n копий символа c.
String::String(size_t n, char c)
    : arr(new char[n + 1]),  // n+1 так как нужен ноль в конце
      sz(n),
      cap(n) {
    memset(arr, c, n);
    arr[n] = '\0';
}
// Конструктор по умолчанию
String::String() : arr(new char[1]), sz(0), cap(0) {
    arr[0] = '\0';
}
// Копирующий конструктор
String::String(const String& s) : arr(new char[s.sz + 1]), sz(s.sz), cap(s.sz) {
    memcpy(arr, s.arr, sz + 1);
}
String::String(char c) : String(1, c) {}

// Деструктор
String::~String() {
    delete[] arr;
}
// Оператор присваивания должен корректно обрабатывать присваивание самому себе.
void String::swap(String& str) {
    std::swap(arr, str.arr);
    std::swap(sz, str.sz);
    std::swap(cap, str.cap);
}
String& String::operator=(String str) {  // копия передается!
    swap(str);
    return *this;
}

// методы length(), size(), capacity()
const size_t& String::length() const {
    return sz;
}

const size_t& String::size() const {
    return sz;
}

const size_t& String::capacity() const {
    return cap;
}

void String::push_back(char c) {
    if (sz < cap) {
        arr[sz] = c;
        arr[sz + 1] = '\0';  // тута
        ++sz;
        return;
    } else {
        char* arr2 = new char[(cap + 1) * 2 + 1];  // и тута
        for (size_t i = 0; i < sz; ++i) {
            arr2[i] = arr[i];
        }
        delete[] arr;
        arr = arr2;
        arr[sz] = c;
        arr[sz + 1] = '\0';
        cap = (cap + 1) * 2;
        ++sz;
    }
}

void String::pop_back() {
    arr[sz - 1] = '\0';
    sz -= 1;
}

char& String::operator[](size_t index) {
    return arr[index];
}

const char& String::operator[](size_t index) const {
    return arr[index];
}

char& String::front() {
    return arr[0];
}

const char& String::front() const {
    return arr[0];
}

const char& String::back() const {
    if (sz != 0) {
        return arr[sz - 1];
    } else {
        return arr[0];
    }
}

char& String::back() {
    if (sz != 0) {
        return arr[sz - 1];
    } else {
        return arr[0];
    }
}

String& String::operator+=(const String& other) {
    if (sz + other.sz < cap) {
        for (size_t i = 0; i < other.sz + 1; ++i) {
            arr[sz + i] = other.arr[i];
        }
        sz += other.sz;
        return *this;
    } else {
        if (other.sz + sz < 2 * (cap)) {
            cap = (cap + 1) * 2;
        } else {
            cap = (other.sz + 1) * 2;
        }

        char* arr2 = new char[cap + 1];
        for (size_t i = 0; i < sz; ++i) {
            arr2[i] = arr[i];
        }
        delete[] arr;
        arr = arr2;
        for (size_t i = 0; i < other.sz + 1; ++i) {
            arr[sz + i] = other.arr[i];
        }
        sz += other.sz;
        return *this;
    }
}

size_t String::find(const String& substring) const {
    if (substring.sz > sz) {
        return sz;
    }
    size_t i0 = sz;
    size_t diff = sz - substring.sz + 1;
    for (size_t j = 0; j < diff; ++j) {
        if (arr[j] == substring.arr[0]) {
            i0 = j;
            bool ispresent = true;
            for (size_t i = 1; i < substring.sz; ++i) {
                if (arr[i0 + i] != substring.arr[i]) {
                    ispresent = false;
                    i0 = sz;
                    break;
                }
            }
            if (ispresent) {
                return i0;
            }
        }
    }

    return i0;
}

size_t String::rfind(const String& substring) const {
    if (substring.sz > sz) {
        return sz;
    }
    size_t i0 = 0;
    size_t diff = sz - substring.sz + 1;
    for (size_t j = diff; j > 0; j -= 1) {
        if (arr[j] == substring.arr[0]) {
            i0 = j;
            bool ispresent = true;
            for (size_t i = 1; i < substring.sz; ++i) {
                if (arr[i0 + i] != substring.arr[i]) {
                    ispresent = false;
                    i0 = 0;
                    break;
                }
            }
            if (ispresent) {
                return i0;
            }
        }
    }

    return sz - i0;
}

String String::substr(const size_t& start, const size_t& count) const {
    String substring(count, 'a');
    for (size_t i = 0; i < count; ++i) {
        substring.arr[i] = arr[start + i];
    }
    return substring;
}

bool String::empty() const {
    return sz == 0;
}

void String::clear() {
    sz = 0;
    arr[0] = '\0';
}

void String::shrink_to_fit() {
    char* arr2 = new char[sz + 1];
    for (size_t i = 0; i < sz + 1; ++i) {
        arr2[i] = arr[i];
    }
    delete[] arr;
    arr = arr2;
    cap = sz;
}

const char* String::data() const {
    return arr;
}

char* String::data() {
    return arr;
}

bool operator==(const String& s1, const String& s2) {
    if (s1.sz != s2.sz) {
        return false;
    } else {
        for (size_t i = 0; i < s1.sz; ++i) {
            if (s1.arr[i] != s2.arr[i]) {
                return false;
            }
        }
        return true;
    }
}

bool operator!=(const String& s1, const String& s2) {
    return !(s1 == s2);
}

bool operator<(const String& a, const String& b) {
    int i = 0;
    while (true) {
        if (a.arr[i] == b.arr[i]) {
            if (a.arr[i] == '\0') {
                return false;
            }
            ++i;
            continue;
        } else {
            return a.arr[i] < b.arr[i];
        }
    }
}

bool operator>(const String& a, const String& b) {
    return b < a;
}

bool operator>=(const String& a, const String& b) {
    return !(a < b);
}

bool operator<=(const String& a, const String& b) {
    return !(a > b);
}

std::ostream& operator<<(std::ostream& out, const String& s) {
    for (u_int i = 0; i < s.sz; ++i) {
        out << s.arr[i];
    }
    return out;
}

std::istream& operator>>(std::istream& in, String& s) {
    char input;
    while (in.get(input)) {
        if (input == '\n') {
            break;
        }
        s.push_back(input);
    }
    return in;
}

String operator+(String a, const String& b) {
    a += b;
    return a;
}
