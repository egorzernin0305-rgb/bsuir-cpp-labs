#include "VM.h"
#include "TableUtils.h"

#include <iomanip>
#include <stdexcept>

namespace
{
    const int MIN_YEAR = 1940;
    const int MAX_YEAR = 2100;
}

int VM::created_ = 0;
int VM::destroyed_ = 0;

VM::VM() : brand_("noname"), year_(2000)
{
    ++created_;
    std::cout << "VM() created: " << brand_ << std::endl;
}

VM::VM(const String& brand, int year) : brand_(brand), year_(2000)
{
    setYear(year);                                  // проверка через сеттер
    ++created_;
    std::cout << "VM(brand, year) created: " << brand_ << ", " << year_ << std::endl;
}

VM::~VM()
{
    ++destroyed_;
    std::cout << "~VM() destroyed: " << brand_ << std::endl;
}

const String& VM::getBrand() const
{
    return brand_;
}

void VM::setBrand(const String& brand)
{
    brand_ = brand;
}

int VM::getYear() const
{
    return year_;
}

void VM::setYear(int year)
{
    if (year < MIN_YEAR || year > MAX_YEAR)
        throw std::invalid_argument("VM::setYear: year must be in range 1940..2100");
    year_ = year;
}

const char* VM::typeName() const
{
    return "VM";
}

void VM::printSpecificCells() const
{
    dashes(5);                                      // у базового класса характеристик нет
}

void VM::printRow() const
{
    cell(typeName());
    cell(brand_);
    cell(year_);
    printSpecificCells();                           // виртуальный вызов: для каждого класса своя версия
    std::cout << '|' << std::endl;
}

void VM::printHeader()
{
    static const char* titles[COLUMNS] = {
        "Type", "Brand", "Year", "PSU, W", "Diagonal, in", "Battery, mAh", "RAM, GB", "Stylus"
    };

    print_separator();
    std::cout << "  # ";
    for (int i = 0; i < COLUMNS; i++)
        cell(titles[i]);
    std::cout << '|' << std::endl;
    print_separator();
}

void VM::printTable(VM* const* items, int count)
{
    printHeader();
    for (int i = 0; i < count; i++)
    {
        std::cout << std::right << std::setw(3) << i + 1 << ' ';
        items[i]->printRow();
    }
    print_separator();
}

int VM::getCreated()
{
    return created_;
}

int VM::getDestroyed()
{
    return destroyed_;
}

int VM::getAlive()
{
    return created_ - destroyed_;
}

// ---------- перегрузка вывода и ввода ----------
std::ostream& operator<<(std::ostream& out, const VM& vm)
{
    out << vm.typeName() << ": brand = " << vm.brand_ << ", year = " << vm.year_;
    return out;
}

std::istream& operator>>(std::istream& in, VM& vm)
{
    String brand;
    int year;

    std::cout << "brand: ";
    in >> brand;                                    // это operator>> из String (читает строку целиком)
    std::cout << "year [" << MIN_YEAR << ".." << MAX_YEAR << "]: ";
    in >> year;
    in.ignore(1000, '\n');                          // убрать остаток строки (перенос после числа)

    if (in)                                         // ввод прошёл без ошибок
    {
        vm.setBrand(brand);
        vm.setYear(year);                           // сеттер проверит диапазон
    }
    return in;
}
