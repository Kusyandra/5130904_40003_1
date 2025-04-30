#include "custom_struct.hpp"

custom_namespace::StreamManager::StreamManager(std::basic_ios< char > & stream):
  stream_(stream),
  width_(stream.width()),
  fill_(stream.fill()),
  precision_(stream.precision()),
  format_(stream.flags())
{}

custom_namespace::StreamManager::~StreamManager()
{
  stream_.width(width_);
  stream_.fill(fill_);
  stream_.precision(precision_);
  stream_.flags(format_);
}

namespace custom_namespace
{
  std::istream & operator>>(std::istream & in, TokenSeparator && token)
  {
      std::istream::sentry sentry(in);
      if (!sentry)
      {
        return in;
      }
      char ch = '0';
      in >> ch;
      if (in && (ch != token.delimiter))
      {
        in.setstate(std::ios::failbit);
      }
      return in;
  }

  std::istream & operator>>(std::istream & in, DoubleInput && input)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> input.value;
    char ch = '0';
    in >> ch;
    if (in && ch != 'd' && ch != 'D')
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream & operator>>(std::istream & in, LongLongInput && input)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> input.value;
    char ch = '0';
    in >> ch;
    if (in && (ch == 'l' || ch == 'L'))
    {
      return in >> TokenSeparator{ ch };
    }
    else if (in)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream & operator>>(std::istream & in, StringInput && input)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> TokenSeparator{ '"' }, input.value, '"');
  }

  std::istream & operator>>(std::istream & in, CustomData & data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    CustomData inputData;
    std::string key = "";
    {
      using separator = TokenSeparator;
      using dblInput = DoubleInput;
      using llInput = LongLongInput;
      using strInput = StringInput;
      in >> separator{ '(' };
      in >> separator{ ':' };
      for (size_t i = 1; i <= 3; i++)
      {
        in >> key;
        if (key == "firstValue")
        {
          in >> dblInput{ inputData.firstValue };
          in >> separator{ ':' };
        }
        else if (key == "secondValue")
        {
          in >> llInput{ inputData.secondValue };
          in >> separator{ ':' };
        }
        else if (key == "thirdValue")
        {
          in >> strInput{ inputData.thirdValue };
          in >> separator{ ':' };
        }
        else
        {
          in.setstate(std::ios::failbit);
        }
      }
      in >> separator{ ')' };
    }
    if (in)
    {
      data = inputData;
    }
    return in;
  }

  std::ostream & operator<<(std::ostream & out, const CustomData & data)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    StreamManager outGuard(out);
    out << "(:";
    out << "firstValue " << std::fixed << std::setprecision(1) << data.firstValue << "d";
    out << ":secondValue " << data.secondValue << "ll";
    out << ":thirdValue \"" << data.thirdValue << "\"";
    out << ":)";
    return out;
  }
}

