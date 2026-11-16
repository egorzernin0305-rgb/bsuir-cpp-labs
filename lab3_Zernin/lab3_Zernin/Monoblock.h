#pragma once
#include "StationaryVM.h"

// ======================= Уровень 3: моноблок =======================
class Monoblock : public StationaryVM {
private:
    double diagonal_;                               // диагональ экрана, дюймы

public:
    Monoblock();
    Monoblock(const String& brand, int year, int power, double diagonal);
    ~Monoblock();

    double getDiagonal() const;
    void setDiagonal(double diagonal);

    const char* typeName() const override;

    friend std::ostream& operator<<(std::ostream& out, const Monoblock& m);
    friend std::istream& operator>>(std::istream& in, Monoblock& m);

protected:
    void printSpecificCells() const override;
};
