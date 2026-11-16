#pragma once
#include "VM.h"

// ======================= Уровень 2: стационарная ВМ =======================
class StationaryVM : public VM {
private:
    int power_;                                     // мощность блока питания, Вт

public:
    StationaryVM();
    StationaryVM(const String& brand, int year, int power);
    ~StationaryVM();

    int getPower() const;
    void setPower(int power);

    const char* typeName() const override;

    friend std::ostream& operator<<(std::ostream& out, const StationaryVM& s);
    friend std::istream& operator>>(std::istream& in, StationaryVM& s);

protected:
    void printSpecificCells() const override;
};
