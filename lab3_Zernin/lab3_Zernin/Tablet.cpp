#include "Tablet.h"
#include "TableUtils.h"

Tablet::Tablet() : PortableVM(), stylus_(false)
{
    std::cout << "Tablet() created: stylus = " << (stylus_ ? "yes" : "no") << std::endl;
}

Tablet::Tablet(const String& brand, int year, int battery, bool stylus)
    : PortableVM(brand, year, battery), stylus_(false)
{
    setStylus(stylus);
    std::cout << "Tablet(brand, year, battery, stylus) created: stylus = " << (stylus_ ? "yes" : "no") << std::endl;
}

Tablet::~Tablet()
{
    std::cout << "~Tablet() destroyed" << std::endl;
}

bool Tablet::hasStylus() const
{
    return stylus_;
}

void Tablet::setStylus(bool stylus)
{
    stylus_ = stylus;
}

const char* Tablet::typeName() const
{
    return "Tablet";
}

void Tablet::printSpecificCells() const
{
    dashes(2);
    cell(getBattery());
    dashes(1);
    cell(stylus_ ? "yes" : "no");
}

std::ostream& operator<<(std::ostream& out, const Tablet& t)
{
    out << static_cast<const PortableVM&>(t);
    out << ", stylus = " << (t.stylus_ ? "yes" : "no");
    return out;
}

std::istream& operator>>(std::istream& in, Tablet& t)
{
    in >> static_cast<PortableVM&>(t);
    if (!in)
        return in;

    int stylus;
    std::cout << "stylus (1 - yes, 0 - no): ";
    in >> stylus;
    in.ignore(1000, '\n');

    if (in)
        t.setStylus(stylus == 1);
    return in;
}
