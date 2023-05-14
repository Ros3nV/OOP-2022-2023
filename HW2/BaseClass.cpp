#include "BaseClass.h"

BaseClass::BaseClass() : BaseClass("","",2002,0)
{
}

BaseClass::BaseClass(const MyString& title, const MyString& summary, unsigned year, unsigned ID): title(title),summary(summary),year(year),ID(ID)
{
}
