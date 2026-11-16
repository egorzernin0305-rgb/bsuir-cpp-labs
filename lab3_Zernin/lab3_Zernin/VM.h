#pragma once
#include <iostream>
#include "String.h"

// Иерархия (3 уровня):
//
//   VM
//   +-- StationaryVM
//   |     +-- Monoblock
//   +-- PortableVM
//         +-- Laptop
//         +-- Tablet

// ======================= Уровень 1: вычислительная машина =======================
class VM {
private:
    String brand_;                                  // бренд
    int year_;                                      // год выпуска

    static int created_;                            // сколько объектов создано
    static int destroyed_;                          // сколько удалено

public:
    VM();                                           // без параметров
    VM(const String& brand, int year);              // с параметрами
    virtual ~VM();                                  // виртуальный, чтобы delete через VM* вызывал все деструкторы

    VM(const VM&) = delete;                         // копировать объекты иерархии не нужно
    VM& operator=(const VM&) = delete;

    const String& getBrand() const;
    void setBrand(const String& brand);
    int getYear() const;
    void setYear(int year);

    virtual const char* typeName() const;           // название класса для таблицы и вывода

    void printRow() const;                          // одна строка таблицы
    static void printHeader();                      // шапка таблицы (отдельный метод)
    static void printTable(VM* const* items, int count);   // вся таблица: шапка + строки

    static int getCreated();
    static int getDestroyed();
    static int getAlive();

    friend std::ostream& operator<<(std::ostream& out, const VM& vm);
    friend std::istream& operator>>(std::istream& in, VM& vm);

protected:
    virtual void printSpecificCells() const;        // ячейки с характеристиками конкретного класса
};
