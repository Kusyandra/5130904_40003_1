#ifndef CUSTOM_STRUCT_HPP
#define CUSTOM_STRUCT_HPP

#include <iostream>
#include <string>
#include <iomanip>

namespace custom_namespace
{
  struct CustomData
  {
    double firstValue;
    long long secondValue;
    std::string thirdValue;
  };

  struct TokenSeparator
  {
    char delimiter;
  };

  struct DoubleInput
  {
    double & value;
  };

  struct LongLongInput
  {
    long long & value;
  };

  struct StringInput
  {
    std::string & value;
  };

  class StreamManager
  {
  public:
    explicit StreamManager(std::basic_ios< char > & stream);
    ~StreamManager();
  private:
    std::basic_ios< char > & stream_;
    std::streamsize width_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags format_;
  };

  std::istream & operator>>(std::istream & in, TokenSeparator && token);
  std::istream & operator>>(std::istream & in, DoubleInput && input);
  std::istream & operator>>(std::istream & in, StringInput && input);
  std::istream & operator>>(std::istream & in, CustomData & data);
  std::ostream & operator<<(std::ostream & out, const CustomData & data);
}

#endif