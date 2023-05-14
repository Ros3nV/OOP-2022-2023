#include "Comic.h"

Comic::Comic(): Comic("TITLE","",2005,4,"UNKNOWN","FMI",Frequency::MONTHLY,nullptr,12)
{
}

Comic::Comic(const MyString& title, const MyString& summary, unsigned year, 
	unsigned ID, const MyString& author, const MyString& publisher, Frequency frequency,
	const unsigned char* genre, unsigned number):
	BaseClass(title,summary,year,ID),publisher(publisher),frequency(frequency),author(author),number(number)
{
	if (genre && strlen((const char*)(genre)) == 16)
	{
		strcpy_s((char*)(this->genre), 17, (const char*)(genre));
	}
	else
	{
		strcpy_s((char*)(this->genre), 17, "0000000000000000");;
	}
}