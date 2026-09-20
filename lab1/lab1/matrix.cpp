#include "Matrix.h"
#include <iostream>

Matrix::Matrix(int r, int c)
{
    rows = r;
    cols = c;
    data = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        data[i] = new int[cols];
        for (int j = 0; j < cols; j++)
        {
            data[i][j] = 0;
        }
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}

void Matrix::input()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << "Введите элемент [" << i << "][" << j << "]: ";
            std::cin >> data[i][j];
        }
    }
}

void Matrix::print() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << data[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}


/*Matrix* Matrix::multiply(const Matrix& other) const
{
    if (this->cols != other.rows)
    {
        std::cout << "Ошибка: умножение невозможно (столбцы первой != строкам второй)" << std::endl;
        return nullptr;
    }

    Matrix* result = new Matrix(this->rows, other.cols);

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < other.cols; j++)
        {
            result->data[i][j] = 0;
            for (int k = 0; k < this->cols; k++)
            {
                result->data[i][j] += this->data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}*/

Matrix Matrix::multiply(const Matrix& other) const
{
    Matrix result(this->rows, other.cols);

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < other.cols; j++)
        {
            result.data[i][j] = 0;
            for (int k = 0; k < this->cols; k++)
            {
                result.data[i][j] += this->data[i][k] * other.data[k][j];
            }
        }
    }

    return result;
}
