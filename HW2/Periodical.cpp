#include "Periodical.h"

Periodical::Periodical() : Periodical("TITLE","",2004,3,Frequency::YEARLY,3)
{
}

Periodical::Periodical(const MyString& title, const MyString& summary, unsigned year, unsigned ID, Frequency frequency, unsigned number) : BaseClass(title,summary,year,ID),frequency(frequency),number(number)
{
}
