#include <iostream>
#include "Matrix.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    int r1, c1, r2, c2;

    std::cout << "Введите размеры первой матрицы (строки и столбцы): ";
    std::cin >> r1 >> c1;
    Matrix m1(r1, c1);
    m1.input();

    std::cout << "Введите размеры второй матрицы (строки и столбцы): ";
    std::cin >> r2 >> c2;
    Matrix m2(r2, c2);
    m2.input();

    std::cout << "\nПервая матрица:\n";
    m1.print();

    std::cout << "\nВторая матрица:\n";
    m2.print();

    /* Matrix* result = m1.multiply(m2);

    if (result != nullptr)
    {
        std::cout << "\nРезультат умножения:\n";
        result->print();
        delete result; 
    }*/

    Matrix result = m1.multiply(m2);

    std::cout << "\nРезультат умножения:\n";
    result.print();
    return 0;
}