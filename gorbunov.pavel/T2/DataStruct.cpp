#include "DataStruct.h"
#include <sstream>
#include <regex>
#include <iomanip>

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
    std::string label;
    std::string val;

    if (!(in >> label)) return in;

    if (label == ":key1")
    {
        in >> val;
        dest.key1 = std::stod(val);
    }
    else if (label == ":key2")
    {
        in >> val;
        dest.key2 = std::stoll(val);
    }
    else if (label == ":key3")
    {
        std::getline(in, dest.key3, ':');
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
    out << "(:key1 " << src.key1 << "d: ";
    out << ":key2 " << src.key2 << "ll: ";
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b)
{
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3 < b.key3;
}
