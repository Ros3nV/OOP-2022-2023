#pragma once
#include "FN.h"
#include "Date.h"
#include "Text.h"
#include "Number.h"
class CellFactory
{
private:
	static bool isDate(const std::string& text);
	static bool isFN(const std::string& text);
	static bool isNumber(const std::string& text);
public:
	static Cell* createNewCell(const std::string& text);
	CellFactory& operator=(const CellFactory& other) = delete;
	CellFactory(const CellFactory& other) = delete;
	CellFactory() = default;
};

