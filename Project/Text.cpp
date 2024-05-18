#include "Text.h"

Text::Text(const std::string& text):text(text)
{
}

Cell* Text::clone() const
{
    return new Text(*this);
}

Cell::Type Text::returnType() const
{
    return Cell::Type::TEXT;
}

unsigned Text::getLenOfCell() const
{
    return text.length();
}

void Text::print(std::ostream& out) const
{
    out << text;
}

bool Text::operator==(const Cell& other) const
{
    return operator==(dynamic_cast<const Text&>(other));

}

bool Text::operator>(const Cell& other) const
{
    return operator>(dynamic_cast<const Text&>(other));
}

bool Text::operator<(const Cell& other) const
{
    return operator<(dynamic_cast<const Text&>(other));
}

bool Text::operator!=(const Cell& other) const
{
    return operator!=(dynamic_cast<const Text&>(other));
}

bool Text::operator>=(const Cell& other) const
{
    return operator>=(dynamic_cast<const Text&>(other));
}

bool Text::operator<=(const Cell& other) const
{
    return operator<=(dynamic_cast<const Text&>(other));
}

bool Text::operator==(const Text& other) const
{
    return text == other.text;
}

bool Text::operator>(const Text& other) const
{
    return text>other.text;
}

bool Text::operator<(const Text& other) const
{
    return text<other.text;
}

bool Text::operator!=(const Text& other) const
{
    return !(*this==other);
}

bool Text::operator>=(const Text& other) const
{
    return (*this==other) || (*this>other);
}

bool Text::operator<=(const Text& other) const
{
      return (*this == other) || (*this < other);;
}
