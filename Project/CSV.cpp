#include "CSV.h"

void CSV::free()
{
    delete[] rows;
    if (previousState != nullptr)
    {
        delete previousState;
    }
    rowsCount = 0;
    rowsCapacity = 0;
    rows = nullptr;
    previousState = nullptr;
}

void CSV::copyFrom(const CSV& other)
{
    lenght = other.lenght;
    nameOfFile.clear();
    nameOfFile = other.nameOfFile;
    rowsCount = other.rowsCount;
    rowsCapacity = other.rowsCapacity;
    rows = new Row[rowsCapacity];
    isMaxLenCorrect = other.isMaxLenCorrect;
    isCorrect = other.isCorrect;
    isHeaderLine = other.isHeaderLine;
    isOpenedAtleastOneTime = other.isOpenedAtleastOneTime;
    for (unsigned i = 0; i < rowsCount; i++)
    {
        rows[i] = other.rows[i];
    }
    
    if (other.previousState != nullptr)
    {
        previousState = new CSV(*other.previousState);
    }
    else
    {
        previousState = nullptr;
    }

    
}

void CSV::resizeRows()
{
    if (!rowsCapacity)
    {
        rows = new Row [++rowsCapacity];
        return;
    }
    Row* temp = new Row[rowsCapacity *= 2];
    for (unsigned i = 0; i < rowsCount; i++)
    {
        temp[i] = rows[i];
    }
    delete[] rows;
    rows = temp;
}

bool CSV::checkForHeader() const
{
    if (rowsCount == 1)
    {
        isHeaderLine = false;
        return true;
    }

    for (unsigned i = 0; i < rowsCount; i++)
    {
        if (rows[0].size != rows[i].size)
        {
            isCorrect = false;
        }
    }


    for (unsigned i = 0; i < rows[0].size; i++)
    {
        if (rows[0].cells[i]->returnType() != Cell::Type::TEXT)
        {
            return false;
        }
    }
    std::vector<Cell::Type> types;

    return false;
}

bool CSV::isCSVValid() const
{
    unsigned columnsCount = rows[0].size;
    if (columnsCount == 0)
    {
        isCorrect = false;
        return false;
    }
    if (rowsCount == 1)
    {
        isHeaderLine = false;
        return true;
    }
    for (unsigned i = 0; i < columnsCount; i++)
    {
        Cell::Type type = rows[1].cells[i]->returnType();
        for (unsigned j = 1; j < rowsCount; j++)
        {
            if (rows[j].size != columnsCount) 
            {
                std::cout << "ROW " << j <<" DOES NOT HAVE THE SAME COLUMNS AS OTHER ROWS\n\n";
                return false;
            }
            if (type != rows[j].cells[i]->returnType())
            {
                std::cout << "ROW " << j <<" CELLS "<<i << " is of different type than the others\n\n";
                return false;
            }
        }
    }
    bool isAllFirstLineTEXT = true;
    for (unsigned i = 0; i < columnsCount; i++)
    {
        if (rows[0].cells[i]->returnType() != Cell::Type::TEXT)
        {
            isAllFirstLineTEXT = false;
            break;
        }
    }
    if (isAllFirstLineTEXT)
    {
        for (unsigned i = 0; i < columnsCount; i++)
        {
            if (rows[1].cells[i]->returnType() != Cell::Type::TEXT)
            {
                isHeaderLine = true;
                return true;
            }
        }
        isHeaderLine = false;  // or ask if header line
        return true;
    }
    else
    {
        for (unsigned i = 0; i < columnsCount; i++)
        {
            if (rows[0].cells[i]->returnType() != rows[1].cells[i]->returnType())
            {
                std::cout << "WRONG TYPES IN " << i << "COLUMN";
                return false;
            }
        }
        isHeaderLine = false;
        return true;
    }

}

unsigned CSV::getMaxLenOfOneColumn(unsigned index) const
{
    unsigned maxLen=0;
    for (unsigned i = 0; i < rowsCount; i++)
    {
        if (rows[i].cells[index]->getLenOfCell() > maxLen)
        {
            maxLen = rows[i].cells[index]->getLenOfCell();
        }
    }
    return maxLen;
}

void CSV::removeRow(unsigned indexOfRow)
{
    rows[indexOfRow].swapRows(rows[rowsCount-1]);
    rows[rowsCount-1].free();
    rowsCount--;
}

void CSV::initPreviousState()
{
    if (previousState != nullptr)
    {
        delete previousState;
        previousState = nullptr;
    }
    previousState = new CSV(*this);
}



void CSV::writeToFile(std::ofstream& out) const
{
    if (rowsCount == 0)
    {
        return;
    }
    for (unsigned i = 0; i < rowsCount-1; i++)
    {
        rows[i].writeToFile(out);
        out << '\n';
    }
    rows[rowsCount-1].writeToFile(out);
}

void CSV::initMaxLen() const
{
    lenght.clear();
    for (unsigned i = 0; i < rows[0].size; i++)
    {
        lenght.push_back(getMaxLenOfOneColumn(i));
    }
    isMaxLenCorrect = true;
}

void CSV::printDash() const
{
    for (unsigned i = 0; i < lenght.size(); i++)
    {
        for (unsigned j = 0; j < lenght[i]+3; j++)
        {
            std::cout << '-';
        }
    }
    std::cout << '\n';
}

 void CSV::printSpaces(unsigned lenOfCell, unsigned lenOfColumn)
{
    for (unsigned i = 0; i < lenOfColumn - lenOfCell + 2; i++)
    {
        std::cout << ' ';
    }
}

bool CSV::doesVectorHaveDifferentValues(const std::vector<unsigned>& vec)
{
    for (unsigned i = 0; i < vec.size() - 1; i++)
    {
        for (unsigned j = i + 1; j < vec.size(); j++)
        {
            if (vec[i] == vec[j])
            {
                return false;
            }
        }
    }
    return true;
}

bool CSV::isValidOperation(const std::string& operation)
{
    if (operation == "==" ||
        operation == "!=" ||
        operation == ">=" ||
        operation == "<=" ||
        operation == ">"  ||
        operation == "<"   )
    {
        return true;
    }
    return false;
}

void CSV::printCommands()
{
    std::cout << "COMMANDS ARE:\n";
    std::cout << "open\n";
    std::cout << "print\n";
    std::cout << "save\n";
    std::cout << "save as\n";
    std::cout << "copy row\n";
    std::cout << "remove column\n";
    std::cout << "min values\n";
    std::cout << "max values\n";
    std::cout << "change columns\n";
    std::cout << "remove identical rows\n";
    std::cout << "most common\n";
    std::cout << "sort\n";
    std::cout << "filter\n";
    std::cout << "undo\n";
    std::cout << "exit\n";
}

int CSV::indexOfColumnByName(const std::string& name) const
{
    for (unsigned i = 0; i < rows[0].size; i++)
    {
        if (Text(name) == *rows[0].cells[i])
        {
            return i;
        }
    }
    return -1;
}

int CSV::indexOfColumnByText(const std::string& text) const
{
    int indexOfColumn = atoi(text.c_str());
    if (indexOfColumn == 0 && text != "0")
    {
        //=> text
        if (!isHeaderLine)
        {
            throw "THERE IS NO HEADER LINE\n\n";
        }
        indexOfColumn = indexOfColumnByName(text);
    }
    if (indexOfColumn >= rowsCount || indexOfColumn == -1)
    {
        throw "THERE IS NO SUCH INDEX\n\n";
    }
    return indexOfColumn;
}

void CSV::getMaxOrMin(std::string& operation)
{
    if (rowsCount + 1 > rowsCapacity)
    {
        resizeRows();
    }
    rowsCount++;
    Cell* element;
    for (unsigned i = 0; i < rows[0].size; i++) // columns=rows[0].size
    {
        element = rows[isHeaderLine].cells[i];
        for (unsigned j = isHeaderLine + 1; j < rowsCount - 1; j++)
        {
            if (compare(*element, *rows[j].cells[i], operation))
            {
                element = rows[j].cells[i];
            }
        }
        rows[rowsCount - 1].addCellToRow(element->clone());
    }
}

CSV::CSV():rowsCount(0),rowsCapacity(1),rows(new Row[1]),isMaxLenCorrect(false),isCorrect(false),nameOfFile(""),isHeaderLine(false), previousState(nullptr),isOpenedAtleastOneTime(false)
{
}

void CSV::open(const std::string& file)
{   
    std::ifstream in(file);
    if (!in.is_open())
    {
        std::cout<<"NOT OPENED FILE\n\n";
        return;
    }
    initPreviousState();
    if (isOpenedAtleastOneTime)
    {
        CSV* temp = previousState;
        previousState = nullptr;
        free();
        previousState = temp;
    }
    nameOfFile = file;
    
    in.seekg(0,std::ios::end);
    unsigned indexOfLast = in.tellg();
    if (indexOfLast == 0)
    {
        isCorrect = false;
        in.close();
        return;
    }
    in.seekg(std::ios::beg);
    while (!in.eof())
    {
        char buff[512];
        in.getline(buff, 512);
        if (rowsCount + 1 > rowsCapacity)
        {
            resizeRows();
        }
        rows[rowsCount++].initRow(buff);
    }
    in.close();
    isCorrect = isCSVValid();
    isOpenedAtleastOneTime = true;
    isMaxLenCorrect = false;
}

void CSV::changeColumns(const std::string& permutation)
{
    if (!isCorrect)
    {
        std::cout << "FILE IS NOT CORRECT\n\n";
        return;
    }
    if (permutation.length() != (2 * rows[0].size - 1))
    {
        std::cout << "WRONG PERMUTATION\n\n";
        return;
    }
    
    std::vector<unsigned>order;
    unsigned max = permutation[0] - '0';
    order.push_back(permutation[0] - '0');

    // get numbers of permutation
    for (unsigned i = 2; i < permutation.length(); i++) 
    {
        if (i % 2 == 0)
        {
            if (permutation[i] < '0' || permutation[i]>'9')
            {
                std::cout << "WRONG PERMUTATION\n\n";
                return;
            }
          
            if (permutation[i] - '0' > max)
            {
                max = permutation[i] - '0';
            }
            order.push_back(permutation[i] - '0');
        }
    }

    //check if permutation is wrong
    if ((max+1)!=order.size() || (max+1)!=rows[0].size || !doesVectorHaveDifferentValues(order))
    {
        std::cout << "WRONG PERMUTATION"<<'\n';
        return;
    } 

    //swap
    initPreviousState();
    Row* temp = new Row[rowsCount];
    for (unsigned i = 0; i < rowsCount; i++)
    {
        for (unsigned j = 0; j < rows[i].size; j++)
        {
            temp[i].addCellToRow( rows[i].cells[order[j]]);
            rows[i].cells[order[j]] = nullptr;
        }
    }
    isMaxLenCorrect = false;
    delete[] rows;
    rows = temp;
}

void CSV::removeIdenticalRows()
{
    if (!isCorrect)
    {
        std::cout << "FILE IS NOT CORRECT\n\n";
        return;
    }
    initPreviousState();
    for (unsigned i = isHeaderLine; i < rowsCount; i++)
    {
        for (unsigned j =  i + 1; j < rowsCount; j++)
        {
            if (rows[i] == rows[j])
            {
                removeRow(j);
            }
        }
    }
}

void CSV::removeColumn(const std::string& text)
{
    if (!isCorrect)
    {
        std::cout << "FILE IS NOT CORRECT\n\n";
        return;
    }
    int indexOfColumn;
    try
    {
        indexOfColumn = indexOfColumnByText(text);
    }
    catch (const char* error)
    {
        std::cout << error;
        return;
    }
    initPreviousState();
    for (unsigned i = 0; i < rowsCount; i++)
    {
        rows[i].removeCell(indexOfColumn);
        for (int j = indexOfColumn; j < rows[i].size - 1; j++)
        {
            rows[i].swapCells(j, j + 1);
        }
        rows[i].size--;
    }
    isMaxLenCorrect = false;
}

void CSV::addMinValues()
{
    if (!isCorrect)
    {
        std::cout << "FILE IS NOT CORRECT\n\n";
        return;
    }
    std::string operation = ">"; 
    initPreviousState();
    getMaxOrMin(operation);
}

void CSV::addMaxValues()
{
    if (!isCorrect)
    {
        std::cout << "FILE IS NOT CORRECT\n\n";
        return;
    }
    std::string operation = "<";
    initPreviousState();
    getMaxOrMin(operation);

}

void CSV::mostCommon()
{    
    if (!isCorrect)
    {
        std::cout << "FILE IS NOT CORRECT\n\n";
        return;
    }

    initPreviousState();
    if (rowsCount + 1 > rowsCapacity)
    {
        resizeRows();
    }
    rowsCount++;
    std::vector<unsigned>timesFound;
    for (unsigned i = 0; i < rows[0].size; i++) // columns=rows[0].size
    {
        unsigned maxOfRow = 0;
        unsigned indexOfMaxForRow = 0;
        for (unsigned j = isHeaderLine; j < rowsCount - 1; j++)
        {
            unsigned Found = 0;
            for (unsigned z = isHeaderLine; z < rowsCount - 1; z++)
            {
                if(compare(*rows[j].cells[i], *rows[z].cells[i], "=="))
                {
                    Found++;
                }
            }
            if (maxOfRow < Found)
            {
                maxOfRow = Found;
                indexOfMaxForRow = timesFound.size();
            }
            timesFound.push_back(Found);
        }
        Cell* minEL = rows[indexOfMaxForRow].cells[i];
        for (unsigned k = isHeaderLine; k < timesFound.size(); k++)
        {
            if (timesFound[k] == maxOfRow && compare(*minEL,*rows[k].cells[i],">"))
            {
                minEL = rows[k].cells[i];
            }
        }
        rows[rowsCount - 1].addCellToRow(minEL->clone());
        timesFound.clear();
    }
}

void CSV::sortByNumberOrName(const std::string& text)
{
    int indexOfFirstSpace = text.find(',');
    if (indexOfFirstSpace == -1)
    {
        std::cout << "NOT CORRECT\n\n";
        return;
    }

    int indexOfColumn;
    try
    {
        indexOfColumn = indexOfColumnByText(text.substr(0, indexOfFirstSpace));
    }
    catch (const char* error)
    {
        std::cout << error;
        return;
    }

    std::string operation = "";
    operation = text[text.length() - 1];
    if (!isValidOperation(operation))
    {
        std::cout << "THERE IS NO SUCH OPERATION\n\n";
        return;
    }
   
    initPreviousState();
  
    for (unsigned i = isHeaderLine; i < rowsCount-1; i++)
    {
        for (unsigned j = isHeaderLine; j < rowsCount-1; j++)
        {
            if(compare(*rows[j].cells[indexOfColumn], *rows[j + 1].cells[indexOfColumn], operation))
            {
                rows[j].swapRows(rows[j + 1]);
            }
        }
    }
}

void CSV::undo()
{
    if (previousState != nullptr)
    {
        CSV* temp = previousState;
        previousState = nullptr;
        *this = *temp;
        delete temp;
    }
    else
    {
        std::cout << "THERE IS NO MORE UNDO\n\n";
    }
}

void CSV::filterByValue(const std::string& text)
{
    if (!isCorrect)
    {
        std::cout << "FILE IS NOT CORRECT\n\n";
        return;
    }
    int indexOfFirstSpace = text.find(',');
    if (indexOfFirstSpace == -1)
    {
        std::cout << "NOT CORRECT\n\n";
        return;
    }
    int indexOfColumn;
    try
    {
        indexOfColumn = indexOfColumnByText(text.substr(0, indexOfFirstSpace));
    }
    catch (const char* error)
    {
        std::cout << error;
        return;
    }
    int secondOfFirstSpace = text.find(',', indexOfFirstSpace + 1);
    std::string operation = text.substr(indexOfFirstSpace + 1, secondOfFirstSpace - indexOfFirstSpace - 1);
    if (!isValidOperation(operation))
    {
        std::cout << "THERE IS NO SUCH OPERATION\n\n";
        return;
    }
    Cell* requirement =factory.createNewCell(text.substr(secondOfFirstSpace + 1));
    if (requirement->returnType() != rows[isHeaderLine].cells[indexOfColumn]->returnType())
    {
        std::cout << "REQUIREMENT IS OF DIFFERENT TYPE\n\n";
        delete requirement;
        return;
    }
    initPreviousState();
    for (unsigned i = isHeaderLine; i < rowsCount; i++)
    {
        if (!compare(*rows[i].cells[indexOfColumn], *requirement, operation))
        {
            removeRow(i);
        }
    }
    delete requirement;
}

CSV& CSV::operator=(const CSV& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return*this;
}

CSV::CSV(const CSV& other)
{
    copyFrom(other);
}

CSV::~CSV()
{
    free();
}

void CSV::enterCommand()
{
    char command[64];
    while (true)
    {   
        command[0] = '\0';
        printCommands();
        std::cout << "ENTER COMMAND: ";
        std::cin.getline(command,64);

        if (!strcmp(command, "open"))
        {
            std::cout << "ENTER NAME OF FILE:";
            std::cin.getline(command, 64);
            open(command);
            continue;
        }
        if (!strcmp(command, "print"))
        {
            print();
            continue;
        }
        if (!strcmp(command, "save"))
        {
            save();
            continue;
        }
        if (!strcmp(command, "save as"))
        {
            saveAs();
            continue;
        }
        if (!strcmp(command, "copy row"))
        {
            std::cout << "ENTER INDEX OF ROW:";
            std::cin.getline(command, 64);
            copyRow(command);
            continue;
        }
        if (!strcmp(command, "change columns"))
        {
            std::cout << "ENTER PERUTATION:";
            std::cin.getline(command, 64);
            changeColumns(command);
            continue;
        }
        if (!strcmp(command, "remove identical rows"))
        {
            removeIdenticalRows();
            continue;
        }
        if (!strcmp(command, "remove column"))
        {
            std::cout << "ENTER NAME OR NUMBER OF COLUMN: ";
            std::cin.getline(command, 64);
            removeColumn(command);
            continue;
        }
        if (!strcmp(command, "min values"))
        {
            addMinValues();
            continue;
        }
        if (!strcmp(command, "max values"))
        {
            addMaxValues();
            continue;
        }
        if (!strcmp(command, "most common"))
        {
            mostCommon();
            continue;
        }
        if (!strcmp(command, "sort"))
        {
            std::cout << "ENTER SORT(NAME\\INDEX,OPERATION)";
            std::cin.getline(command, 64);
            sortByNumberOrName(command);
        }
        if (!strcmp(command, "filter"))
        {
            std::cout << "ENTER FILTER(NAME\\INDEX,OPERATION,VALUE)";
            std::cin.getline(command, 64);
            filterByValue(command);
        }
        if (!strcmp(command, "undo"))
        {
            undo();
        }
        if (!strcmp(command, "exit"))
        {
            exit();
            break;
        }
    }
}

void CSV::print() const
{
    if (rowsCount == 0 || !isOpenedAtleastOneTime)
    {
        std::cout << "FILE IS EMPTY\n\n";
        return;
    }
    if (!isCorrect)
    {
        std::cout << "FILE IS NOT CORRECT\n\n";
        return;
    }
   

    if (!isMaxLenCorrect)
    {
        initMaxLen();
    }
    for (unsigned i = 0; i < Number(rowsCount).getLenOfCell()+3; i++)
    {
        std::cout << ' ';
    }
    for (unsigned i = 0; i < lenght.size(); i++)
    {
        std::cout << i;
        printSpaces(Number(i).getLenOfCell(), lenght[i]);
    }
    std::cout << '\n';
    printDash();
    for (unsigned i = 0; i < rowsCount; i++)
    {
        if (i == 0 && isHeaderLine)
        {
            std::cout << "H|  ";
        }
        else
        {
            std::cout << i << "|  ";
        }
        for (unsigned j = 0; j < rows[i].size - 1; j++)
        {
            rows[i].cells[j]->print(std::cout);
            printSpaces(rows[i].cells[j]->getLenOfCell(), lenght[j]);
        }
        rows[i].cells[rows[i].size - 1]->print(std::cout);
        std::cout << '\n';
    }
    printDash();
    std::cout << '\n' << '\n';
}

void CSV::save() const
{
    if (!isOpenedAtleastOneTime)
    {
        std::cout << "FILE IS EMPTY AND NOWHERE TO BE SAVED!\n\n";
        return;
    }
    std::ofstream out(nameOfFile);
    if (!out.is_open())
    {
        throw "FILE NOT OPENED";
    }
    writeToFile(out);
    out.close();
}

void CSV::saveAs() const
{
    std::cout << "WRITE NEW NAME OF FILE: ";
    char newName[32];
    std::cin.ignore();
    std::cin.getline(newName, 32);
    
    
    std::ofstream out(newName);
    if (!out.is_open())
    {
        std::cout<< "FILE NOT OPENED\n\n";
        return;
    }
    if (rowsCount == 0)
    {
        out.close();
        return;
    }
    writeToFile(out);
    out.close();
}

void CSV::exit() const
{
    std::cout << "SAVE\\SAVEAS\\EXIT:\n";
    std::string command;
    std::cin >> command;
    if (command == "EXIT")
    {
        return;
    }
    if (command == "SAVE")
    {
        save();
    }
    if (command == "SAVEAS")
    {
        saveAs();
    }
}

void CSV::copyRow(const std::string& text)
{
    if (!isCorrect)
    {
        std::cout << "FILE IS NOT CORRECT\n\n";
        return;
    }
    int index = atoi(text.c_str());
    if (index >= rowsCount || (index==0 && text!="0"))
    {
        std::cout << "WRONG INDEX\n\n";
        return;
    }
    if (isHeaderLine && index == 0)
    {
        std::cout << "CANT COPY HEADER LINE\n\n";
        return;
    }

    initPreviousState();
    if (rowsCount + 1 > rowsCapacity)
    {
        resizeRows();
    }
    ++rowsCount;
    rows[rowsCount - 1] = rows[index];
}
void CSV::Row::resize()
{
    if (!capacity)
    {
        cells= new Cell * [++capacity];
        return;
    }
    Cell** temp = new Cell * [capacity *= 2];
    for (unsigned i = 0; i < size; i++)
    {
        temp[i] = cells[i];
    }
    delete[] cells;
    cells = temp;
}

void CSV::Row::free()
{
    for (unsigned i = 0; i < size; i++)
    {
        if (cells[i] != nullptr)
        {
            delete cells[i];
        }
    }
    if (cells != nullptr)
    {
        delete[] cells;
    }
    cells = nullptr;
    size = 0;
    capacity = 0;
}

void CSV::Row::copyFrom(const Row& other)
{
    size = other.size;
    capacity = other.capacity;
    cells = new Cell*[capacity];
    for (unsigned i = 0; i < size; i++)
    {
        cells[i] = other.cells[i]->clone();
    }
}

void CSV::Row::addCellToRow(const std::string& text)
{
    if (size + 1 > capacity)
    {
        resize();
    }
    cells[size++] = factory.createNewCell(text);
}

void CSV::Row::addCellToRow(Cell* cell)
{
    if (size + 1 > capacity)
    {
        resize();
    }
    cells[size++] = cell;
}

void CSV::Row::initRow(const std::string& text)
{
    int indexOfFound = text.find(',', 0);
    int indexStart = 0;
    while (indexOfFound != -1)
    {
        addCellToRow(text.substr(indexStart, indexOfFound - indexStart));
    	indexStart = indexOfFound + 1;
    	indexOfFound = text.find(',', indexStart + 1);
    }
    addCellToRow(text.substr(indexStart));
}

void CSV::Row::writeToFile(std::ofstream& out) const
{
    for (unsigned i = 0; i < size-1; i++)
    {
        cells[i]->writeToFile(out);   
        out << ',';
    }
    cells[size-1]->writeToFile(out);
}

void CSV::Row::removeCell(unsigned index)
{
    if (cells[index] != nullptr)
    {
        delete cells[index];
    }
    cells[index] = nullptr;
}

void CSV::Row::swapCells(unsigned indexOfFirst, unsigned indexOfSecond)
{ 
    Cell* temp = cells[indexOfFirst];
    cells[indexOfFirst] = cells[indexOfSecond];
    cells[indexOfSecond] = temp;
}

bool CSV::Row::operator==(const Row& other) const
{
    for (unsigned i = 0; i < size; i++)
    {
        if (!compare(*cells[i],*other.cells[i],"=="))
        {
            return false;
        }
    }
    return true;
}

void CSV::Row::swapRows(const Row& other)
{
    if (size != other.size && capacity != other.size)
    {
        return;
    }
    Cell* temp;
    for (unsigned i = 0; i < size; i++)
    {
        temp = cells[i];
        cells[i] = other.cells[i];
        other.cells[i] = temp;
    }
}


CSV::Row::Row()
{
    size = 0;
    capacity = 1;
    cells = new Cell * [capacity] {nullptr};
}

CSV::Row::Row(unsigned capacity) : size(0), capacity(capacity)
{
    cells = new Cell *[capacity] {nullptr};
}

CSV::Row& CSV::Row::operator=(const Row& other)
{
    if (this != &other)
    {
        Row::free();
        Row::copyFrom(other);
    }
    return *this;
}

CSV::Row::Row(const Row& other)
{
    Row::copyFrom(other);
}

CSV::Row::~Row()
{
    Row::free();
}