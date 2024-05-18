#include "CellFactory.h"

bool CellFactory::isDate(const std::string& text)
{
	unsigned len = text.length();
	if (len == 10 && text[4] == '-' && text[7] == '-')
	{
		bool date = true;
		for (int i = 0; i < 10; i++)
		{
			if (i != 4 && i != 7 && (text[i] < '0' || text[i] > '9'))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool CellFactory::isFN(const std::string& text)
{ 
	unsigned len = text.length();
	if ((text[0] == '"' && text[len - 1] == '"') || (text[0] == '\'' && text[len - 1] == '\''))
	{	//new FN
		if (len == 12 && text[2] == 'M' && text[3] == 'I' && (text[5] == '4' || text[5] == '8' || text[5] == '7' || text[5] == '6'))
		{
			bool newFN = true;
			for (int i = 1; i < len - 1; i++)
			{
				if (i != 2 && i != 3 && (text[i] < '0' || text[i] > '9'))
				{
					break;
					newFN = false;
				}
			}
			if (newFN)
			{
				return true;
			}
		}

		//old FN
		if (len == 7 &&
			((text[1] == '4' && text[2] == '5') ||
				(text[1] == '7' && text[2] == '2') ||
				(text[1] == '8' && text[2] == '1') ||
				(text[1] == '6' && text[2] == '3'))) // SI - proizvono izbrani chisla
		{
			for (int i = 1; i < len - 1; i++)
			{
				if ((text[i] < '0' || text[i] > '9'))
				{
					return false;
				}
			}
			return true;
		}
	}
	return false;
}

bool CellFactory::isNumber(const std::string& text)
{
	unsigned len = text.length();
	if (len == 0)
	{
		return false;
	}
	double number = atof(text.c_str());
	for (int i = 0; i < len; i++)
	{
		if ((text[i] < '0' || text[i] > '9') && text[i] != '.')
		{
			return false;
		}
	}
	return true;
}

Cell* CellFactory::createNewCell(const std::string& text)
{
	if (isFN(text))
	{
		return new FN(text);
	}
	if (isDate(text))
	{
		return new Date(text);
	}
	if (isNumber(text))
	{
		return new Number(text);
	}
	return new Text(text);
}
