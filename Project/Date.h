#pragma once
#include "Cell.h"
class Date:public Cell
{
	unsigned day;
	unsigned month;
	unsigned year;

public:
	Date(unsigned day,unsigned month,unsigned year);
	Date(const std::string& text);
	Date()=default;

	virtual unsigned getLenOfCell()const override;
	virtual Cell* clone()const override;
	virtual Cell::Type returnType()const override;
	virtual void print(std::ostream& out)const override;

	bool operator==(const Date& other)const;
	bool operator>(const Date& other)const;
	bool operator<(const Date& other)const;
	bool operator!=(const Date& other)const;
	bool operator>=(const Date& other)const;
	bool operator<=(const Date& other)const;


	virtual bool operator==(const Cell& other)const override;
	virtual bool operator>(const Cell& other)const override;
	virtual bool operator<(const Cell& other)const override;
	virtual bool operator!=(const Cell& other)const override;
	virtual bool operator>=(const Cell& other)const override;
	virtual bool operator<=(const Cell& other)const override;
};