#include "StationaryVM.h"
#include "TableUtils.h"

#include <stdexcept>

namespace
{
    const int MIN_POWER = 1;
    const int MAX_POWER = 5000;
}

StationaryVM::StationaryVM() : VM(), power_(300)
{
    std::cout << "StationaryVM() created: power = " << power_ << std::endl;
}

StationaryVM::StationaryVM(const String& brand, int year, int power) : VM(brand, year), power_(300)
{
    setPower(power);
    std::cout << "StationaryVM(brand, year, power) created: power = " << power_ << std::endl;
}

StationaryVM::~StationaryVM()
{
    std::cout << "~StationaryVM() destroyed" << std::endl;
}

int StationaryVM::getPower() const
{
    return power_;
}

void StationaryVM::setPower(int power)
{
    if (power < MIN_POWER || power > MAX_POWER)
        throw std::invalid_argument("StationaryVM::setPower: power must be in range 1..5000");
    power_ = power;
}

const char* StationaryVM::typeName() const
{
    return "StationaryVM";
}

void StationaryVM::printSpecificCells() const
{
    cell(power_);
    dashes(4);
}

std::ostream& operator<<(std::ostream& out, const StationaryVM& s)
{
    out << static_cast<const VM&>(s);               // сначала часть родителя
    out << ", PSU = " << s.power_ << " W";
    return out;
}

std::istream& operator>>(std::istream& in, StationaryVM& s)
{
    in >> static_cast<VM&>(s);                      // сначала часть родителя
    if (!in)
        return in;

    int power;
    std::cout << "power supply, W [" << MIN_POWER << ".." << MAX_POWER << "]: ";
    in >> power;
    in.ignore(1000, '\n');

    if (in)
        s.setPower(power);
    return in;
}
