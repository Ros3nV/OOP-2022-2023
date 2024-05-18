#pragma once
#include "Cell.h"
#include <iostream>
class FN :public Cell
{
	enum class Speciality
	{
		INFORMATICS,
		INFO_SYSTEMS,
		COMPUTER_SCIENCE,
		SOFTWARE_ENGINEERING
	};
	bool isNewFN;
	Speciality spec;
	std::string number;
public:
	FN(const std::string& number);
	virtual void print(std::ostream& out)const override;
	virtual unsigned getLenOfCell()const override;
	unsigned getSpec()const;
	virtual Cell* clone()const override;
	virtual Cell::Type returnType()const override;

	bool operator==(const FN& other)const;
	bool operator>(const FN& other)const;
	bool operator<(const FN& other)const;
	bool operator!=(const FN& other)const;
	bool operator>=(const FN& other)const;
	bool operator<=(const FN& other)const;

	virtual bool operator==(const Cell& other)const override;
	virtual bool operator>(const Cell& other)const override;
	virtual bool operator<(const Cell& other)const override;
	virtual bool operator!=(const Cell& other)const override;
	virtual bool operator>=(const Cell& other)const override;
	virtual bool operator<=(const Cell& other)const override;
};