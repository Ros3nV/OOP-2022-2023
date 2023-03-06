//Напишете функция, която приема име на съществуващ файл и име и копира съдържанието на същестуващия файл в нов файл.

#include <iostream>
#include <fstream>


int main()
{
    std::ifstream OriginalFile("OriginalFile.txt");

    if (!OriginalFile.is_open())
    {
        return -1;
    }
    std::ofstream CopyFile("CopyFile.txt");

    char buff[256];


    while (!OriginalFile.eof())
    {
        OriginalFile.getline(buff, 256);

        CopyFile << buff<<'\n';
    }

    OriginalFile.close();
    CopyFile.close();

}
