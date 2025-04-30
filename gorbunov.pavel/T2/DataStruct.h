#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <string>
#include <complex>
#include <utility>

struct DataStruct
{
    double key1; // Для DBL LIT и DBL SCI
    long long key2; // Для SLL LIT
    std::string key3; // Для строк
};

std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& src);

bool compareDataStruct(const DataStruct& a, const DataStruct& b);

#endif // DATASTRUCT_H
