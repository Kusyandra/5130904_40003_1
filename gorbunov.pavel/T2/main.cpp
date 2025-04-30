#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "DataStruct.h"

void cleanVector(std::vector<DataStruct>& vec)
{
    vec.erase(
        std::remove_if(vec.begin(), vec.end(),
            [](const DataStruct& ds) {
                return ds.key1 == INVALID_DOUBLE_INDICATOR &&
                    ds.key2 == INVALID_LL_INDICATOR &&
                    ds.key3 == INVALID_STR_INDICATOR;
            }),
        vec.end());
}

int main()
{
    std::vector<DataStruct> data;

    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data)
    );

    cleanVector(data);

if (data.empty()) {
    std::cerr << "Warning: No valid data structures found\n";
    std::cerr << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
    return 1;
}

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
