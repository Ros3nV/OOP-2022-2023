#include "Cell.h"

void Cell::writeToFile(std::ofstream& out) const
{
	print(out);
}

bool compare(const Cell& lhs, const Cell& rhs, const std::string& operation)
{
	if (operation == "==")
	{
		return lhs == rhs;
	}
	if (operation == "!=")
	{
		return lhs == rhs;
	}
	if (operation == ">=")
	{
		return lhs >= rhs;
	}
	if (operation == "<=")
	{
		return lhs <= rhs;
	}
	if (operation == ">")
	{
		return lhs > rhs;
	}
	if (operation == "<")
	{
		return lhs < rhs;
	}
}
