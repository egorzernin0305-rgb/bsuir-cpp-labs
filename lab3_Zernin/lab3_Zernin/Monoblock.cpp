#include "Monoblock.h"
#include "TableUtils.h"

#include <stdexcept>

namespace
{
    const double MIN_DIAGONAL = 5.0;
    const double MAX_DIAGONAL = 100.0;
}

Monoblock::Monoblock() : StationaryVM(), diagonal_(24.0)
{
    std::cout << "Monoblock() created: diagonal = " << diagonal_ << std::endl;
}

Monoblock::Monoblock(const String& brand, int year, int power, double diagonal)
    : StationaryVM(brand, year, power), diagonal_(24.0)
{
    setDiagonal(diagonal);
    std::cout << "Monoblock(brand, year, power, diagonal) created: diagonal = " << diagonal_ << std::endl;
}

Monoblock::~Monoblock()
{
    std::cout << "~Monoblock() destroyed" << std::endl;
}

double Monoblock::getDiagonal() const
{
    return diagonal_;
}

void Monoblock::setDiagonal(double diagonal)
{
    if (diagonal < MIN_DIAGONAL || diagonal > MAX_DIAGONAL)
        throw std::invalid_argument("Monoblock::setDiagonal: diagonal must be in range 5..100");
    diagonal_ = diagonal;
}

const char* Monoblock::typeName() const
{
    return "Monoblock";
}

void Monoblock::printSpecificCells() const
{
    cell(getPower());
    cell(diagonal_);
    dashes(3);
}

std::ostream& operator<<(std::ostream& out, const Monoblock& m)
{
    out << static_cast<const StationaryVM&>(m);
    out << ", diagonal = " << m.diagonal_ << " in";
    return out;
}

std::istream& operator>>(std::istream& in, Monoblock& m)
{
    in >> static_cast<StationaryVM&>(m);
    if (!in)
        return in;

    double diagonal;
    std::cout << "diagonal, in [" << MIN_DIAGONAL << ".." << MAX_DIAGONAL << "]: ";
    in >> diagonal;
    in.ignore(1000, '\n');

    if (in)
        m.setDiagonal(diagonal);
    return in;
}
