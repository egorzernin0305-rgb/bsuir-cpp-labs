#include <iostream>
#include <stdexcept>
#include "String.h"
#include "VM.h"
#include "StationaryVM.h"
#include "Monoblock.h"
#include "PortableVM.h"
#include "Laptop.h"
#include "Tablet.h"

// Ввод одного объекта через operator>>. Если ввод неверный, спрашиваем этот объект заново.
// Возвращает false, если ввод закончился.
template <typename T>
static bool input_object(const char* title, T& obj)
{
    std::cout << std::endl << "--- input " << title << " ---" << std::endl;
    while (true)
    {
        try
        {
            std::cin >> obj;
            if (std::cin)
                return true;
            if (std::cin.eof())
                return false;

            std::cin.clear();                       // ошибка формата (например, буквы вместо числа)
            std::cin.ignore(1000, '\n');
            std::cout << "wrong input, try again" << std::endl;
        }
        catch (const std::invalid_argument& e)      // сеттер не принял значение
        {
            std::cout << "error: " << e.what() << ", try again" << std::endl;
        }
    }
}

// Удаляет все объекты (деструкторы вызываются в обратном порядке создания)
// и показывает, сколько объектов создано и удалено.
static void destroy_all(VM* const* items, int count)
{
    std::cout << std::endl << "--- deleting all objects (reverse order) ---" << std::endl;
    for (int i = count - 1; i >= 0; --i)
        delete items[i];

    std::cout << "created:   " << VM::getCreated() << std::endl;
    std::cout << "destroyed: " << VM::getDestroyed() << std::endl;
    std::cout << "alive:     " << VM::getAlive() << std::endl;
}

int main()
{
    // ---------- 1. Создаём объекты и массив ----------
    std::cout << "--- creating objects ---" << std::endl;
    VM* vm = new VM;
    StationaryVM* stationary = new StationaryVM;
    Monoblock* monoblock = new Monoblock;
    PortableVM* portable = new PortableVM;
    Laptop* laptop = new Laptop;
    Tablet* tablet = new Tablet;

    const int count = 6;
    VM* items[count] = { vm, stationary, monoblock, portable, laptop, tablet };

    // ---------- 2. Ввод (operator>> каждого класса) ----------
    if (!input_object("VM", *vm) ||
        !input_object("StationaryVM", *stationary) ||
        !input_object("Monoblock", *monoblock) ||
        !input_object("PortableVM", *portable) ||
        !input_object("Laptop", *laptop) ||
        !input_object("Tablet", *tablet))
    {
        destroy_all(items, count);
        return 0;
    }

    // ---------- 3. Вывод таблицей (цикл по массиву) ----------
    std::cout << std::endl;
    VM::printTable(items, count);

    // ---------- 4. Меняем параметры сеттерами ----------
    try
    {
        vm->setBrand(String("Acer"));
        vm->setYear(2015);

        stationary->setPower(500);

        monoblock->setBrand(String("Apple"));
        monoblock->setDiagonal(27.0);

        portable->setBattery(5200);

        laptop->setRam(32);

        tablet->setStylus(false);
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }

    // ---------- 5. Выводим ещё раз: через operator<< и таблицей ----------
    std::cout << std::endl << "--- after changes ---" << std::endl;
    std::cout << "1) " << *vm << std::endl;
    std::cout << "2) " << *stationary << std::endl;
    std::cout << "3) " << *monoblock << std::endl;
    std::cout << "4) " << *portable << std::endl;
    std::cout << "5) " << *laptop << std::endl;
    std::cout << "6) " << *tablet << std::endl;

    std::cout << std::endl;
    VM::printTable(items, count);

    // ---------- 6. Удаляем ----------
    destroy_all(items, count);

    return 0;
}
