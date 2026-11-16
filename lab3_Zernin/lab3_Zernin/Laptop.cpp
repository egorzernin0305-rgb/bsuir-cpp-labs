#include "Laptop.h"
#include "TableUtils.h"

#include <stdexcept>

namespace
{
    const int MIN_RAM = 1;
    const int MAX_RAM = 4096;
}

Laptop::Laptop() : PortableVM(), ram_(8)
{
    std::cout << "Laptop() created: RAM = " << ram_ << std::endl;
}

Laptop::Laptop(const String& brand, int year, int battery, int ram)
    : PortableVM(brand, year, battery), ram_(8)
{
    setRam(ram);
    std::cout << "Laptop(brand, year, battery, ram) created: RAM = " << ram_ << std::endl;
}

Laptop::~Laptop()
{
    std::cout << "~Laptop() destroyed" << std::endl;
}

int Laptop::getRam() const
{
    return ram_;
}

void Laptop::setRam(int ram)
{
    if (ram < MIN_RAM || ram > MAX_RAM)
        throw std::invalid_argument("Laptop::setRam: RAM must be in range 1..4096");
    ram_ = ram;
}

const char* Laptop::typeName() const
{
    return "Laptop";
}

void Laptop::printSpecificCells() const
{
    dashes(2);
    cell(getBattery());
    cell(ram_);
    dashes(1);
}

std::ostream& operator<<(std::ostream& out, const Laptop& l)
{
    out << static_cast<const PortableVM&>(l);
    out << ", RAM = " << l.ram_ << " GB";
    return out;
}

std::istream& operator>>(std::istream& in, Laptop& l)
{
    in >> static_cast<PortableVM&>(l);
    if (!in)
        return in;

    int ram;
    std::cout << "RAM, GB [" << MIN_RAM << ".." << MAX_RAM << "]: ";
    in >> ram;
    in.ignore(1000, '\n');

    if (in)
        l.setRam(ram);
    return in;
}
