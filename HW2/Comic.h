#pragma once
#include "BaseClass.h"

class Comic : public BaseClass
{
	MyString author;
	MyString publisher;
	Frequency frequency;
	unsigned char genre[17];
	unsigned number;
public:
	Comic();
	Comic(const MyString& title, const MyString& summary, unsigned year, unsigned ID,const MyString& author, const MyString& publisher, Frequency frequency, const unsigned char* genre, unsigned number);
};

