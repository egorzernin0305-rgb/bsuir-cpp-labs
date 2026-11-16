#pragma once
#include "PortableVM.h"

// ======================= Уровень 3: ноутбук =======================
class Laptop : public PortableVM {
private:
    int ram_;                                       // оперативная память, ГБ

public:
    Laptop();
    Laptop(const String& brand, int year, int battery, int ram);
    ~Laptop();

    int getRam() const;
    void setRam(int ram);

    const char* typeName() const override;

    friend std::ostream& operator<<(std::ostream& out, const Laptop& l);
    friend std::istream& operator>>(std::istream& in, Laptop& l);

protected:
    void printSpecificCells() const override;
};
