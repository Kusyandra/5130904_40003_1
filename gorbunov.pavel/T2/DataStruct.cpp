#include "data_structure.hpp"

custom_namespace::StreamSaver::StreamSaver(std::basic_ios< char > & stream):
  stream_(stream),
  width_(stream.width()),
  fill_(stream.fill()),
  precision_(stream.precision()),
  format_(stream.flags())
{}

custom_namespace::StreamSaver::~StreamSaver()
{
  stream_.width(width_);
  stream_.fill(fill_);
  stream_.precision(precision_);
  stream_.flags(format_);
}

namespace custom_namespace
{
  std::istream & operator>>(std::istream & in, Separator && separator)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char tempChar = '0';
    in >> tempChar;
    if (in && (tempChar != separator.delimiter))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream & operator>>(std::istream & in, DoubleValue && value)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> value.reference;
    char postfix = '0';
    in >> postfix;
    if (in && (postfix != 'd' && postfix != 'D'))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream & operator>>(std::istream & in, LongLongValue && value)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> value.reference;
    char postfix = '0';
    in >> postfix;
    if (in && (postfix == 'l' || postfix == 'L'))
    {
      return in >> Separator{ postfix };
    }
    else if (in)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream & operator>>(std::istream & in, StringValue && value)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> Separator{ '"' }, value.reference, '"');
  }

  std::istream & operator>>(std::istream & in, DataContainer & container)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataContainer tempContainer;
    std::string key = "";
    {
      using sep = Separator;
      using dbl = DoubleValue;
      using lli = LongLongValue;
      using str = StringValue;
      in >> sep{ '(' };
      in >> sep{ ':' };
      for (size_t i = 1; i <= 3; i++)
      {
        in >> key;
        if (key == "firstKey")
        {
          in >> dbl{ tempContainer.firstKey };
          in >> sep{ ':' };
        }
        else if (key == "secondKey")
        {
          in >> lli{ tempContainer.secondKey };
          in >> sep{ ':' };
        }
        else if (key == "thirdKey")
        {
          in >> str{ tempContainer.thirdKey };
          in >> sep{ ':' };
        }
        else
        {
          in.setstate(std::ios::failbit);
        }
      }
      in >> sep{ ')' };
    }
    if (in)
    {
      container = tempContainer;
    }
    return in;
  }

  std::ostream & operator<<(std::ostream & out, const DataContainer & container)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    StreamSaver saver(out);
    out << "(:";
    out << "firstKey " << std::fixed << std::setprecision(1) << container.firstKey << "d";
    out << ":secondKey " << container.secondKey << "ll";
    out << ":thirdKey \"" << container.thirdKey << "\"";
    out << ":)";
    return out;