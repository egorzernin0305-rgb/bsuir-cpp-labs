#include "PortableVM.h"
#include "TableUtils.h"

#include <stdexcept>

namespace
{
    const int MIN_BATTERY = 100;
    const int MAX_BATTERY = 100000;
}

PortableVM::PortableVM() : VM(), battery_(4000)
{
    std::cout << "PortableVM() created: battery = " << battery_ << std::endl;
}

PortableVM::PortableVM(const String& brand, int year, int battery) : VM(brand, year), battery_(4000)
{
    setBattery(battery);
    std::cout << "PortableVM(brand, year, battery) created: battery = " << battery_ << std::endl;
}

PortableVM::~PortableVM()
{
    std::cout << "~PortableVM() destroyed" << std::endl;
}

int PortableVM::getBattery() const
{
    return battery_;
}

void PortableVM::setBattery(int battery)
{
    if (battery < MIN_BATTERY || battery > MAX_BATTERY)
        throw std::invalid_argument("PortableVM::setBattery: battery must be in range 100..100000");
    battery_ = battery;
}

const char* PortableVM::typeName() const
{
    return "PortableVM";
}

void PortableVM::printSpecificCells() const
{
    dashes(2);
    cell(battery_);
    dashes(2);
}

std::ostream& operator<<(std::ostream& out, const PortableVM& p)
{
    out << static_cast<const VM&>(p);
    out << ", battery = " << p.battery_ << " mAh";
    return out;
}

std::istream& operator>>(std::istream& in, PortableVM& p)
{
    in >> static_cast<VM&>(p);
    if (!in)
        return in;

    int battery;
    std::cout << "battery, mAh [" << MIN_BATTERY << ".." << MAX_BATTERY << "]: ";
    in >> battery;
    in.ignore(1000, '\n');

    if (in)
        p.setBattery(battery);
    return in;
}
