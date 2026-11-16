#include "String.h"

#include <cctype>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <limits>

String::String() : data_(new char[1]), length_(0)
{
    data_[0] = '\0';
}

String::String(const char* str)
{
    if (str == nullptr)
        str = "";

    const std::size_t raw = std::strlen(str);
    if (raw > static_cast<std::size_t>(std::numeric_limits<int>::max() - 1))
        throw std::length_error("String: input too long");

    length_ = static_cast<int>(raw);
    data_ = new char[length_ + 1];
    std::memcpy(data_, str, raw);
    data_[length_] = '\0';
}

String::String(const String& other) : length_(other.length_)
{
    data_ = new char[length_ + 1];
    std::memcpy(data_, other.data_, length_);
    data_[length_] = '\0';
}

String& String::operator=(const String& other)
{
    if (this != &other)
    {
        char* new_data = new char[other.length_ + 1];
        std::memcpy(new_data, other.data_, other.length_);
        new_data[other.length_] = '\0';

        delete[] data_;
        data_ = new_data;
        length_ = other.length_;
    }
    return *this;
}

String::~String()
{
    delete[] data_;
}

String& String::operator+=(const String& rhs)
{
    if (rhs.length_ > std::numeric_limits<int>::max() - length_ - 1)
        throw std::length_error("String::operator+=: result too long");

    const int new_len = length_ + rhs.length_;
    char* new_data = new char[new_len + 1];

    std::memcpy(new_data, data_, length_);
    std::memcpy(new_data + length_, rhs.data_, rhs.length_);
    new_data[new_len] = '\0';

    delete[] data_;
    data_ = new_data;
    length_ = new_len;
    return *this;
}

String String::operator-(const String& rhs) const
{
    if (rhs.length_ == 0)
        return *this;

    char* buffer = new char[length_ + 1];
    int out = 0;
    const char* current = data_;
    const char* end = data_ + length_;

    while (current < end)
    {
        const char* found = std::strstr(current, rhs.data_);
        if (found == nullptr || found >= end)
        {
            const int rest = static_cast<int>(end - current);
            std::memcpy(buffer + out, current, rest);
            out += rest;
            break;
        }

        const int part = static_cast<int>(found - current);
        std::memcpy(buffer + out, current, part);
        out += part;
        current = found + rhs.length_;
    }
    buffer[out] = '\0';

    String result(buffer);
    delete[] buffer;
    return result;
}

String& String::operator++()
{
    for (int i = 0; i < length_; i++)
        data_[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(data_[i])));
    return *this;
}

String String::operator++(int)
{
    String old(*this);
    ++(*this);
    return old;
}

String& String::operator--()
{
    for (int i = 0; i < length_; i++)
        data_[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(data_[i])));
    return *this;
}

String String::operator--(int)
{
    String old(*this);
    --(*this);
    return old;
}

char& String::operator[](int i)
{
    if (i < 0 || i >= length_)
        throw std::out_of_range("String::operator[]: index out of range");
    return data_[i];
}

const char& String::operator[](int i) const
{
    if (i < 0 || i >= length_)
        throw std::out_of_range("String::operator[]: index out of range");
    return data_[i];
}

String String::operator()(int from, int count) const
{
    if (from < 0 || count < 0 || from > length_ || count > length_ - from)
        throw std::out_of_range("String::operator(): invalid substring bounds");

    char* buffer = new char[count + 1];
    std::memcpy(buffer, data_ + from, count);
    buffer[count] = '\0';

    String result(buffer);
    delete[] buffer;
    return result;
}

String operator+(const String& a, const String& b)
{
    if (b.length_ > std::numeric_limits<int>::max() - a.length_ - 1)
        throw std::length_error("operator+(String, String): result too long");

    const int new_len = a.length_ + b.length_;
    char* buffer = new char[new_len + 1];

    std::memcpy(buffer, a.data_, a.length_);
    std::memcpy(buffer + a.length_, b.data_, b.length_);
    buffer[new_len] = '\0';

    String result(buffer);
    delete[] buffer;
    return result;
}

String operator+(const String& a, const char* b)
{
    return a + String(b);
}

String operator+(const char* a, const String& b)
{
    return String(a) + b;
}

bool operator<(const String& a, const String& b)
{
    return std::strcmp(a.data_, b.data_) < 0;
}

bool operator>(const String& a, const String& b)
{
    return std::strcmp(a.data_, b.data_) > 0;
}

bool operator<=(const String& a, const String& b)
{
    return std::strcmp(a.data_, b.data_) <= 0;
}

bool operator>=(const String& a, const String& b)
{
    return std::strcmp(a.data_, b.data_) >= 0;
}

std::istream& operator>>(std::istream& in, String& s)
{
    char buffer[MAX_LENGTH + 1];
    in.getline(buffer, MAX_LENGTH + 1);

    if (in)
        s = String(buffer);
    return in;
}

std::ostream& operator<<(std::ostream& out, const String& s)
{
    out << s.data_;
    return out;
}