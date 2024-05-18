#include "Number.h"


Number::Number(double number): number(number)
{
}

Number::Number(const std::string& text) : number(atof(text.c_str()))
{
}

bool Number::operator==(const Number& other) const
{
    return number == other.number;
}

bool Number::operator>(const Number& other) const
{
    return number > other.number;
}

bool Number::operator<(const Number& other) const
{
    return number < other.number;
}

bool Number::operator!=(const Number& other) const
{
    return number!=other.number;
}

bool Number::operator>=(const Number& other) const
{
    return number >= other.number;
}

bool Number::operator<=(const Number& other) const
{
    return number <= other.number;
}

Cell* Number::clone() const
{
    return new Number(*this);
}

Cell::Type Number::returnType() const
{
    return Cell::Type::NUMBER;
}



unsigned Number::getLenOfCell() const
{
    char buff[32];
    sprintf_s(buff, 32, "%f", number); //tazi funciq q vzeh ot internet
    for (int i = strlen(buff) - 1; i >= 1; --i)
    {
        if (buff[i] == '.')
        {
            buff[i] = '\0';
            break;
        }
        if (buff[i] == '0')
        {
            buff[i] = '\0';
        }
        else
        {
            break;
        }
    }
    return strlen(buff);
}

void Number::print(std::ostream& out) const
{
    out << number;
}

bool Number::operator==(const Cell& other) const
{
 return operator==(dynamic_cast<const Number&>(other));
}

bool Number::operator>(const Cell& other) const
{
    return operator>(dynamic_cast<const Number&>(other));
}

bool Number::operator<(const Cell& other) const
{
    return operator<(dynamic_cast<const Number&>(other));
}

bool Number::operator!=(const Cell& other) const
{
    return operator!=(dynamic_cast<const Number&>(other));
}

bool Number::operator>=(const Cell& other) const
{
    return operator>=(dynamic_cast<const Number&>(other));
}

bool Number::operator<=(const Cell& other) const
{
    return operator<=(dynamic_cast<const Number&>(other));
}