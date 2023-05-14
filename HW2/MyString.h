#pragma once
#include <iostream>
#include <ostream>


class MyString
{
	char* string;

	void free();
	void copyFrom(const MyString& other);

public:
	MyString();
	MyString(const char* copy);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	MyString& operator+=(const MyString& other);
	MyString operator+(const MyString& rhs);

	friend std::ostream& operator<<(std::ostream& stream, const MyString& other);
	friend std::istream& operator>>(std::istream& stream, MyString& other);
	friend bool operator==(const MyString& lhs, const MyString& rhs);

	const char* c_str()const;
	~MyString();
};


