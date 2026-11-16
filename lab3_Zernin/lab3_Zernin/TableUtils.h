#pragma once
#include <iostream>
#include "String.h"

// Функции для рисования таблицы. Нужны всем классам, поэтому лежат отдельно.

const int COLUMNS = 8;                              // число столбцов таблицы

void cell(const char* text);                        // одна ячейка с текстом
void cell(const String& s);                         // ячейка со String
void cell(int value);                               // ячейка с целым числом
void cell(double value);                            // ячейка с дробным числом
void dashes(int count);                             // count ячеек "-" (у класса нет такой характеристики)
void print_separator();                             // линия +----+----+
