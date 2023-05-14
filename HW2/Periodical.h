#pragma once
#include "BaseClass.h"

class Periodical:public BaseClass
{
	Frequency frequency;
	unsigned number;
public:
	Periodical();
	Periodical(const MyString& title, const MyString& summary, unsigned year, unsigned ID, Frequency frequency, unsigned number);
};

