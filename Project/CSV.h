#pragma once
#include <fstream>
#include "Cell.h"
#include "CellFactory.h"
#include <vector>
class CSV
{
private:
	static CellFactory factory;
	struct Row
	{
		Cell** cells;
		unsigned size;
		unsigned capacity;
		
		void resize();
		void free();
		void copyFrom(const Row& other);

		void addCellToRow(const std::string& text);
		void addCellToRow(Cell* cell);
		void initRow(const std::string& text);
		void writeToFile(std::ofstream& out)const;
		void removeCell(unsigned index);
		void swapCells(unsigned indexOfFirst,unsigned indexOfSecond);

		bool operator==(const Row& other)const;
		void swapRows(const Row& other);

		Row();
		Row(unsigned capacity);
		Row& operator=(const Row& other);
		Row(const Row& other);
		~Row();
	};
	mutable bool isMaxLenCorrect;
	mutable bool isCorrect;
	mutable bool isHeaderLine;
	bool isOpenedAtleastOneTime;
	unsigned rowsCount;
	unsigned rowsCapacity;
	std::string nameOfFile;
	mutable std::vector<unsigned> lenght; // mutable za da moje print da e const(inMaxLen ne moje da se izvika)
	Row* rows;
	CSV* previousState;
	

	void free();
	void copyFrom(const CSV& other);
	void resizeRows();

	bool checkForHeader()const;
	bool isCSVValid()const;
	void writeToFile(std::ofstream& out)const;
	unsigned getMaxLenOfOneColumn(unsigned index)const;
	int indexOfColumnByName(const std::string& name)const;
	int indexOfColumnByText(const std::string& text)const;
	void initMaxLen() const;
	void printDash()const;

	static void printSpaces(unsigned lenOfCell, unsigned lenOfColumn);
	static bool doesVectorHaveDifferentValues(const std::vector<unsigned>& vec);
	static bool isValidOperation(const std::string& operation);
	static void printCommands();
	void getMaxOrMin(std::string& operation);
	void removeRow(unsigned indexOfRow);
	void initPreviousState();


	void print()const;
	void save()const;
	void saveAs()const;
	void exit()const;
	void open(const std::string& file);


	void copyRow(const std::string& text);
	void changeColumns(const std::string& permutation);
	void removeIdenticalRows();
	void removeColumn(const std::string& text);
	void addMinValues();
	void addMaxValues();
	void mostCommon();
	void sortByNumberOrName(const std::string& text); //done
	void filterByValue(const std::string& text);
	void undo();
public:
	CSV();
	CSV& operator=(const CSV& other);
	CSV(const CSV& other);
	~CSV();

	void enterCommand();
};