#pragma once
#include <iostream>
#include <fstream>
class Cell
{
protected:
	friend class CSV;
	friend class CellFactory;
	enum class Type
	{
		DATE,
		FN,
		NUMBER,
		TEXT
	};
public:
	virtual Cell* clone()const = 0;
	virtual Type returnType()const=0;
	virtual unsigned getLenOfCell()const = 0;
	void writeToFile(std::ofstream& out)const;
	virtual void print(std::ostream& out)const = 0;
	virtual bool operator==(const Cell& other)const =0;
	virtual bool operator>(const Cell& other)const=0;
	virtual bool operator<(const Cell& other)const=0;
	virtual bool operator!=(const Cell& other)const=0;
	virtual bool operator>=(const Cell& other)const=0;
	virtual bool operator<=(const Cell& other)const=0;
	friend bool compare(const Cell& lhs, const Cell& rhs, const std::string& operation);
	virtual ~Cell() = default;
};