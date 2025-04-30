#ifndef DATA_STRUCTURE_HPP
#define DATA_STRUCTURE_HPP

#include <iostream>
#include <string>
#include <iomanip>

namespace custom_namespace
{
  struct DataContainer
  {
    double firstKey;
    long long secondKey;
    std::string thirdKey;
  };

  struct Separator
  {
    char delimiter;
  };

  struct DoubleValue
  {
    double & reference;
  };

  struct LongLongValue
  {
    long long & reference;
  };

  struct StringValue
  {
    std::string & reference;
  };

  class StreamSaver
  {
  public:
    explicit StreamSaver(std::basic_ios< char > & stream);
    ~StreamSaver();
  private:
    std::basic_ios< char > & stream_;
    std::streamsize width_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags format_;
  };

  std::istream & operator>>(std::istream & in, Separator && separator);
  std::istream & operator>>(std::istream & in, DoubleValue && value);
  std::istream & operator>>(std::istream & in, StringValue && value);
  std::istream & operator>>(std::istream & in, DataContainer & container);
  std::ostream & operator<<(std::ostream & out, const DataContainer & container);
}

#endif