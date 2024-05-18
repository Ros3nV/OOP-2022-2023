#include "Date.h"

Date::Date(unsigned day, unsigned month, unsigned year): day(day), month(month), year(year)
{
}

Date::Date(const std::string& text)
{
    year = atoi((text.substr(0, 4)).c_str());
    month= atoi((text.substr(5, 2)).c_str());
    day= atoi((text.substr(8)).c_str());
}

unsigned Date::getLenOfCell() const
{
    return 10; //2020-02-10 = 10 len
}

Cell* Date::clone() const
{
    return new Date(*this);
}

Cell::Type Date::returnType() const
{
    return Cell::Type::DATE;
}

void Date::print(std::ostream& out) const
{
    out << year << '-';
    if (month < 10)
    {
        out << 0;
    }
    out << month << '-';
    if (day < 10)
    {
        out << 0;
    }
    out << day;
}

bool Date::operator==(const Cell& other) const
{
    return operator==(dynamic_cast<const Date&>(other));
}

bool Date::operator>(const Cell& other) const
{
    return operator>(dynamic_cast<const Date&>(other));
}

bool Date::operator<(const Cell& other) const
{
    return operator<(dynamic_cast<const Date&>(other));
}

bool Date::operator!=(const Cell& other) const
{
    return operator!=(dynamic_cast<const Date&>(other));
}

bool Date::operator>=(const Cell& other) const
{
    return operator>=(dynamic_cast<const Date&>(other));
}

bool Date::operator<=(const Cell& other) const
{
    return operator<=(dynamic_cast<const Date&>(other));
}

bool Date::operator==(const Date& other) const
{
    return year == other.year && month == other.month && day == other.day;
}

bool Date::operator>(const Date& other) const
{
        if (year > other.year)
            {
        return false;
          }
        if (year == other.year) 
        {
            if (month > other.month)
            {
                return false;
            }
            else 
            {
                if (month == other.month)
                {       
                    return day < other.day;
                }
            }
        }
    return true;
    
}

bool Date::operator<(const Date& other) const
{
    if (year < other.year)
    {
        return false;
    }
    if (year == other.year)
    {
        if (month < other.month)
        {
            return false;
        }
        else
        {
            if (month == other.month)
            {
                return day > other.day;
            }
        }
    }
    return true;
}
//sort date
bool Date::operator!=(const Date& other) const
{
    return  !(*this==other);
}

bool Date::operator>=(const Date& other) const
{
    return (*this>other)||(*this==other);
}

bool Date::operator<=(const Date& other) const
{
    return (*this < other) || (*this == other);
}