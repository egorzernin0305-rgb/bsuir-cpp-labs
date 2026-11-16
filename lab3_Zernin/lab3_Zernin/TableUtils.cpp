#include "TableUtils.h"

#include <iomanip>
#include <sstream>
#include <string>

namespace
{
    const int CELL_WIDTH = 12;                      // ширина ячейки таблицы
}

void cell(const char* text)
{
    std::cout << "| " << std::left << std::setw(CELL_WIDTH) << text << ' ';
}

void cell(const String& s)
{
    std::cout << "| " << std::left << std::setw(CELL_WIDTH) << s << ' ';
}

void cell(int value)
{
    std::cout << "| " << std::left << std::setw(CELL_WIDTH) << value << ' ';
}

void cell(double value)
{
    std::ostringstream text;
    text << std::fixed << std::setprecision(1) << value;
    cell(text.str().c_str());
}

void dashes(int count)
{
    for (int i = 0; i < count; i++)
        cell("-");
}

void print_separator()
{
    std::cout << "    ";
    for (int i = 0; i < COLUMNS; i++)
        std::cout << '+' << std::string(CELL_WIDTH + 2, '-');
    std::cout << '+' << std::endl;
}
