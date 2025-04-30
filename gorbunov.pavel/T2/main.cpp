#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "DataStruct.h"

int main() {
    std::vector<DataStruct> data;
    std::istream_iterator<DataStruct> begin(std::cin);
    std::istream_iterator<DataStruct> end;

    std::copy(begin, end, std::back_inserter(data));

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
