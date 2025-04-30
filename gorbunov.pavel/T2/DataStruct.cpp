#include "DataStruct.h"
#include <stdexcept>
#include <sstream>

StreamGuard::StreamGuard(std::basic_ios<char>& s) :
    s_(s),
    width_(s.width()),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
{
}

StreamGuard::~StreamGuard()
{
    s_.width(width_);
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
}

std::istream& operator>>(std::istream& in, SeparatorIO sep)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    char c;
    if (in >> c && c != sep.exp)
        in.setstate(std::ios::failbit);
    return in;
}

std::istream& operator>>(std::istream& in, LabelIO& sep)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    std::string label;
    if (in >> label &&
        label.length() == LABEL_LENGTH &&
        label.substr(0, 3) == "key" &&
        isdigit(label[3]))
    {
        sep.exp = label;
    }
    else
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::string getCorrectRound(double num)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << num;
    std::string s = oss.str();
    size_t dot_pos = s.find('.');
    if (dot_pos != std::string::npos)
    {
        s.erase(s.find_last_not_of('0') + 1, std::string::npos);
        if (s.back() == '.') s.pop_back();
    }
    return s;
}

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    DataStruct temp;
    LabelIO label;
    bool valid = true;

    // Проверка на '(' и ':'
    if (!(in >> SeparatorIO{ '(' } >> SeparatorIO{ ':' }))
        valid = false;

    int fields_read = 0;
    while (valid && fields_read < 3 && in >> label)
    {
        switch (label.exp[3])
        {
        case OPTION_ONE: {
            std::string val;
            std::getline(in >> std::ws, val, ':');
            if (std::regex_match(val, std::regex(REGEX_DBL_LIT_DOUBLE))) {
                temp.key1 = std::stod(val);
                fields_read++;
            }
            else if (std::regex_match(val, std::regex(REGEX_DBL_LIT_INT))) {
                temp.key1 = std::stod(val);
                fields_read++;
            }
            else {
                std::cerr << "Invalid format for key1: " << val << std::endl;
                valid = false;
            }
            break;
        }
        case OPTION_TWO: {
            std::string val;
            std::getline(in >> std::ws, val, ':');
            if (std::regex_match(val, std::regex(REGEX_SLL))) {
                temp.key2 = std::stoll(val);
                fields_read++;
            }
            else {
                std::cerr << "Invalid format for key2: " << val << std::endl;
                valid = false;
            }
            break;
        }
        case OPTION_THREE: {
            std::string val;
            if (in >> SeparatorIO{ '\"' } && std::getline(in, val, '\"') &&
                in >> SeparatorIO{ ':' })
            {
                temp.key3 = val;
                fields_read++;
            }
            else {
                std::cerr << "Invalid format for key3: " << val << std::endl;
                valid = false;
            }
            break;
        }
        default:
            valid = false;
        }
    }

    if (valid && fields_read == 3 && (in >> SeparatorIO{ ')' }))
    {
        dest = temp;
    }
    else
    {
        in.setstate(std::ios::failbit);
        dest = { INVALID_DOUBLE_INDICATOR, INVALID_LL_INDICATOR, INVALID_STR_INDICATOR };
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& ds)
{
    std::ostream::sentry sentry(out);
    if (!sentry) return out;

    StreamGuard guard(out);
    out << "(:key1 " << getCorrectRound(ds.key1) << "d"
        << ":key2 " << ds.key2 << "ll"
        << ":key3 \"" << ds.key3 << "\":)";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b)
{
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}
