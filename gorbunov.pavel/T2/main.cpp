#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "custom_struct.hpp"

namespace
{
  bool compareCustomData(const custom_namespace::CustomData & lhs, const custom_namespace::CustomData & rhs);
  bool compareCustomData(const custom_namespace::CustomData & lhs, const custom_namespace::CustomData & rhs)
  {
    if (lhs.firstValue < rhs.firstValue)
    {
      return true;
    }
    else if (lhs.secondValue < rhs.secondValue)
    {
      return true;
    }
    else if (lhs.thirdValue.length() < rhs.thirdValue.length())
    {
      return true;
    }
    return false;
  }
}

int main()
{
  using namespace custom_namespace;
  std::vector<CustomData> dataList;
  while (!std::cin.eof())
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(1024, '\n');
    }
    std::copy(
      std::istream_iterator<CustomData>(std::cin),
      std::istream_iterator<CustomData>(),
      std::back_inserter(dataList)
    );
  }
  std::sort(dataList.begin(), dataList.end(), compareCustomData);
  std::copy(
      std::begin(dataList),
      std::end(dataList),
      std::ostream_iterator<CustomData>(std::cout, "\n")
  );
}

