#include "FN.h"

FN::FN(const std::string& number) : number(number), isNewFN(true)
{
    if (number.length() == 7)
    {
        //"45756"
        //"81756"
              if (number[1] == '4' && number[2] == '5')       spec = Speciality::INFORMATICS; 
        else  if (number[1] == '7' && number[2] == '2')       spec = Speciality::INFO_SYSTEMS; 
        else  if (number[1] == '8' && number[2] == '1')       spec = Speciality::COMPUTER_SCIENCE; 
        else                                                  spec = Speciality::SOFTWARE_ENGINEERING; 
        isNewFN = false;
    }

    if (isNewFN)
    {
        switch (number[5])
        {
        case '4': {spec = Speciality::INFORMATICS;  break; }
        case '7': {spec = Speciality::INFO_SYSTEMS;  break; }
        case '8': {spec = Speciality::COMPUTER_SCIENCE;  break; }
        case '6': {spec = Speciality::SOFTWARE_ENGINEERING;  break; }
        default:
            break;
        }
    }
}

unsigned FN::getSpec() const
{
    return unsigned(spec);
}

unsigned FN::getLenOfCell() const
{
    if (isNewFN)
    {
        return 12;
    }
    return 7;
}

void FN::print(std::ostream& out) const
{
    out << number;
}


Cell* FN::clone() const
{
    return new FN(*this);
}

Cell::Type FN::returnType() const
{
    return Cell::Type::FN;
}

bool FN::operator==(const Cell& other) const
{
    return operator==(dynamic_cast<const FN&>(other));
}

bool FN::operator>(const Cell& other) const
{
    return operator>(dynamic_cast<const FN&>(other));

}

bool FN::operator<(const Cell& other) const
{
    return operator<(dynamic_cast<const FN&>(other));
}

bool FN::operator!=(const Cell& other) const
{
    return operator!=(dynamic_cast<const FN&>(other));
}

bool FN::operator>=(const Cell& other) const
{
    return operator>=(dynamic_cast<const FN&>(other));
}

bool FN::operator<=(const Cell& other) const
{
    return operator<=(dynamic_cast<const FN&>(other));
}

bool FN::operator==(const FN& other)const
{
    return number == other.number;
}

bool FN::operator>(const FN& other) const
{
    if(spec==other.spec)   
    { 
        return !isNewFN > !other.isNewFN;
    }
    return spec > other.spec;
}

bool FN::operator<(const FN& other) const
{
    if (spec == other.spec)
    {
        return !isNewFN < !other.isNewFN;
    }
    return spec < other.spec;
}

bool FN:: operator!=(const FN& other)const
{
    return !(*this == other);
}

bool FN:: operator>=(const FN& other)const
{
    return (*this > other) || (*this==other);
}
bool FN:: operator<=(const FN& other)const
{
    return (*this < other) || (*this == other);
}