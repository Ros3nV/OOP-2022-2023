#pragma once
#include "BaseClass.h"
class Book:public BaseClass
{
	MyString author;
	MyString publisher;
	unsigned char genre[17];

public:
	Book();
	Book(const MyString& author, const MyString& publish, const unsigned char* genre, const MyString& summary, const MyString& title, unsigned year, unsigned ID);
};

