#pragma once
#include "VM.h"

// ======================= Уровень 2: портативная ВМ =======================
class PortableVM : public VM {
private:
    int battery_;                                   // ёмкость батареи, мА*ч

public:
    PortableVM();
    PortableVM(const String& brand, int year, int battery);
    ~PortableVM();

    int getBattery() const;
    void setBattery(int battery);

    const char* typeName() const override;

    friend std::ostream& operator<<(std::ostream& out, const PortableVM& p);
    friend std::istream& operator>>(std::istream& in, PortableVM& p);

protected:
    void printSpecificCells() const override;
};
