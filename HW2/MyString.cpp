#include "MyString.h"

void MyString::free()
{
	delete[]string;
}

void MyString::copyFrom(const MyString& other)
{
	unsigned len = strlen(other.string);
	string = new char[len + 1];
	strcpy_s(string, len+1, other.string);
}

MyString::MyString(): MyString("")
{
}

MyString::MyString(const char* copy)
{
	unsigned len = strlen(copy);
	string = new char[len + 1];
	strcpy_s(string, len+1, copy);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}


MyString& MyString::operator+=(const MyString& other)
{
	unsigned len = strlen(string) + strlen(other.string) + 1;
	char* temp = new char[len];
	temp[0] = '\0';
	strcat_s(temp, len, string);
	strcat_s(temp, len, other.string);
	free();
	string = temp;
	return *this;
}

MyString MyString::operator+(const MyString& rhs)
{
	MyString tempString(string);
	tempString += rhs;
	return tempString;
}

const char* MyString::c_str() const
{
	return string;
}

MyString::~MyString()
{
	free();
}

std::ostream& operator<<(std::ostream& stream, const MyString& other)
{
	stream << other.c_str();
	return stream;
}

std::istream& operator>>(std::istream& stream, MyString& other)
{
	char buff[30];
	std::cin.getline(buff,30);
	other.free();
	other.copyFrom(MyString(buff));
	return stream;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	return (strcmp(lhs.c_str(), rhs.c_str()) == 0);
}