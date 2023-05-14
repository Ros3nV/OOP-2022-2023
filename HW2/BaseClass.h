#pragma once
#include "MyString.h"

enum class Frequency
{
	WEEKLY,
	MONTHLY,
	YEARLY
};

class BaseClass
{
protected:
	MyString summary;
	MyString title;
	unsigned year;
	unsigned ID;
public:
	BaseClass();
	BaseClass(const MyString& title, const MyString& summary,unsigned year,unsigned ID);

};

