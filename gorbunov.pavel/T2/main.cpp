#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iostream>
#include "data_structure.hpp"

namespace
{
  bool compareContainers(const custom_namespace::DataContainer & lhs, const custom_namespace::DataContainer & rhs);
  bool compareContainers(const custom_namespace::DataContainer & lhs, const custom_namespace::DataContainer & rhs)
  {
    if (lhs.firstKey < rhs.secondKey)
    {
      return true;
    }
    else if (lhs.secondKey < rhs.secondKey)
    {
      return true;
    }
    else if (lhs.thirdKey.length() < rhs.thirdKey.length())
    {
      return true;
    }
    return false;
  }
}

int main()
{
  using namespace custom_namespace;
  std::vector<DataContainer> data;
  while (!std::cin.eof())
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(1024, '\n');
    }
    std::copy(
      std::istream_iterator<DataContainer>(std::cin),
      std::istream_iterator<DataContainer>(),
      std::back_inserter(data)
    );
  }
  std::sort(data.begin(), data.end(), compareContainers);
  std::copy(
      std::begin(data),
      std::end(data),
      std::ostream_iterator<DataContainer>(std::cout, "\n")
  );
}