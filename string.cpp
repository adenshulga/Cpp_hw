#include "string.h"

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
    String(const char* cs)
        : arr(new char[std::strlen(cs) + 1]), sz(std::strlen(cs)), cap(std::strlen(cs) + 1) {
        memcpy(arr, cs, cap);
    }

    // Конструктор от двух параметров: число n и символ c - создает строку из n копий символа c.
    String(size_t n, char c)
        : arr(new char[n + 1]),
          sz(n),
          cap(n + 1) {  // n+1 так как нужен ноль в конце
        memset(arr, c, n);
        arr[n + 1] = '\0';
    }
    // Конструктор по умолчанию
    String() : arr(new char[1]), sz(0), cap(1) {
        arr[0] = '\0';
    }
    // Копирующий конструктор
    String(const String& s) : arr(new char[s.cap + 1]), sz(s.sz), cap(s.cap) {
        memcpy(arr, s.arr, sz + 1);
    }
    String(char c) : String(1, c) {}

    // Деструктор
    ~String() {
        delete[] arr;
    }
    // Оператор присваивания должен корректно обрабатывать присваивание самому себе.
    void swap(String& str) {
        std::swap(arr, str.arr);
        std::swap(sz, str.sz);
        std::swap(cap, str.cap);
    }
    String& operator=(String str) {  // копия передается!
        swap(str);
        return *this;
    }
    // перегрузить оператор ввода/вывода строки

    friend std::ostream& operator<<(std::ostream& out, const String& s);
    friend std::istream& operator>>(std::istream& in, String& s);

    // методы length(), size(), capacity()
    const size_t& length() const {
        return sz;
    }

    const size_t& size() const {
        return sz;
    }

    const size_t& capacity() const {
        return cap;
    }

    friend bool operator==(const String& s1, const String& s2);
    friend bool operator<(const String& a, const String& b);

    void push_back(char c) {
        if (sz < cap - 1) {
            arr[sz] = c;
            arr[sz + 1] = '\0';
            ++sz;
            return;
        } else {
            char* arr2 = new char[cap * 2];
            for (size_t i = 0; i < sz; ++i) {
                arr2[i] = arr[i];
            }
            delete[] arr;
            arr = arr2;
            arr[sz] = c;
            arr[sz + 1] = '\0';
            cap *= 2;
            ++sz;
        }
    }

    void pop_back() {
        arr[sz - 1] = '\0';
        sz -= 1;
    }

    char& operator[](size_t index) {
        return arr[index];
    }

    const char& operator[](size_t index) const {
        return arr[index];
    }

    char& front() {
        return arr[0];
    }

    const char& front() const {
        return arr[0];
    }

    const char& back() const {
        if (sz != 0) {
            return arr[sz - 1];
        } else {
            return arr[0];
        }
    }

    char& back() {
        if (sz != 0) {
            return arr[sz - 1];
        } else {
            return arr[0];
        }
    }

    String& operator+=(const String& other) {
        if (sz + other.sz < cap) {
            for (size_t i = 0; i < other.sz + 1; ++i) {
                arr[sz + i] = other.arr[i];
            }
            sz += other.sz;
            return *this;
        } else {
            if (other.sz + sz < 2 * (cap)) {
                cap = cap * 2;
            } else {
                cap = other.sz * 2;
            }

            char* arr2 = new char[cap];
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

    size_t find(const String& substring) const {
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

    size_t rfind(const String& substring) const {
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

    String substr(const size_t& start, const size_t& count) const {
        String substring(count, 'a');
        for (size_t i = 0; i < count; ++i) {
            substring.arr[i] = arr[start + i];
        }
        return substring;
    }

    bool empty() const {
        return sz == 0;
    }

    void clear() {
        sz = 0;
        arr[0] = '\0';
    }

    void shrink_to_fit() {
        char* arr2 = new char[sz + 1];
        for (size_t i = 0; i < sz + 1; ++i) {
            arr2[i] = arr[i];
        }
        delete[] arr;
        arr = arr2;
        cap = sz + 1;
    }

    const char* data() const {
        return arr;
    }

    char* data() {
        return arr;
    }
};

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
    in >> s.arr;
    s.sz = std::strlen(s.arr);
    s.cap = s.sz + 1;
    return in;
}

String operator+(String a, const String& b) {
    a += b;
    return a;
}


