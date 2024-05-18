#pragma once
#include "Cell.h"
class Number:public Cell
{
	double number;
public:
	Number(double number);
	Number(const std::string& text);
	virtual Cell* clone()const override;
	virtual Cell::Type returnType()const override;
	virtual unsigned getLenOfCell()const override;
	virtual void print(std::ostream& out)const override;

	bool operator==(const Number& other)const;
	bool operator>(const Number& other)const;
	bool operator<(const Number& other)const;
	bool operator!=(const Number& other)const;
	bool operator>=(const Number& other)const;
	bool operator<=(const Number& other)const;

	virtual bool operator==(const Cell& other)const override;
	virtual bool operator>(const Cell& other)const override;
	virtual bool operator<(const Cell& other)const override;
	virtual bool operator!=(const Cell& other)const override;
	virtual bool operator>=(const Cell& other)const override;
	virtual bool operator<=(const Cell& other)const override;
};

