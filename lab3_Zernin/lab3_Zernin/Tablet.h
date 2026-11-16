#pragma once
#include "PortableVM.h"

// ======================= Уровень 3: планшет =======================
class Tablet : public PortableVM {
private:
    bool stylus_;                                   // есть ли стилус

public:
    Tablet();
    Tablet(const String& brand, int year, int battery, bool stylus);
    ~Tablet();

    bool hasStylus() const;
    void setStylus(bool stylus);

    const char* typeName() const override;

    friend std::ostream& operator<<(std::ostream& out, const Tablet& t);
    friend std::istream& operator>>(std::istream& in, Tablet& t);

protected:
    void printSpecificCells() const override;
};
