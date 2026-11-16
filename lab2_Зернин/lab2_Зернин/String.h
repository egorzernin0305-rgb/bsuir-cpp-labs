#pragma once
#include <iostream>

const int MAX_LENGTH = 80;                          // максимальная длина вводимой строки

class String {
private:
    char* data_;
    int length_;

public:

    String();                                       // без параметров: пустая строка
    explicit String(const char* str);               // с параметром (строка, не длина)
    String(const String& other);                    // копирования (глубокое)


    String& operator=(const String& other);
    ~String();


    String& operator+=(const String& rhs);          // дописать rhs в конец
    String operator-(const String& rhs) const;      // удалить все вхождения rhs
    String& operator++();                           // ++a: перевести в верхний регистр
    String operator++(int);                         // a++: то же, вернуть значение до изменения
    String& operator--();                           // --a: перевести в нижний регистр
    String operator--(int);                         // a--: то же, вернуть значение до изменения
    char& operator[](int i);                        // символ по индексу (с проверкой границ)
    const char& operator[](int i) const;            // то же для константной строки
    String operator()(int from, int count) const;   // подстрока длины count, начиная с from


    friend String operator+(const String& a, const String& b);
    friend String operator+(const String& a, const char* b);
    friend String operator+(const char* a, const String& b);

    friend bool operator<(const String& a, const String& b);
    friend bool operator>(const String& a, const String& b);
    friend bool operator<=(const String& a, const String& b);
    friend bool operator>=(const String& a, const String& b);

    friend std::istream& operator>>(std::istream& in, String& s);
    friend std::ostream& operator<<(std::ostream& out, const String& s);
};
