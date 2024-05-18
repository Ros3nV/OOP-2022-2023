#pragma once
#include <iostream>
#include "Cell.h"
class Text :public Cell
{
	std::string text;
public:
	Text(const std::string& text);
	Text() = default;
	virtual Cell* clone()const override;
	virtual Cell::Type returnType()const override;
	virtual unsigned getLenOfCell()const override;
	virtual void print(std::ostream& out)const override;

	bool operator==(const Text& other)const;
	bool operator>(const Text& other)const;
	bool operator<(const Text& other)const;
	bool operator!=(const Text& other)const;
	bool operator>=(const Text& other)const;
	bool operator<=(const Text& other)const;

	virtual bool operator==(const Cell& other)const override;
	virtual bool operator>(const Cell& other)const override;
	virtual bool operator<(const Cell& other)const override;
	virtual bool operator!=(const Cell& other)const override;
	virtual bool operator>=(const Cell& other)const override;
	virtual bool operator<=(const Cell& other)const override;

};