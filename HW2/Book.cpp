#include "Book.h"


Book::Book() : Book("UNKNOWN","FMI",nullptr,"","TITLE",2003,2)
{
}


Book::Book  (const MyString& author, const MyString& publish, const unsigned char* genre,
	const MyString& summary, const MyString& title,unsigned year,unsigned ID) :
		author(author),publisher(publish),BaseClass(title,summary,year,ID)
{
	if (genre && strlen((const char*)(genre))==16)
	{
		strcpy_s((char*)(this->genre), 17, (const char*)(genre));
	}
	else
	{
		strcpy_s((char*)(this->genre), 17, "0000000000000000");;
	}
}