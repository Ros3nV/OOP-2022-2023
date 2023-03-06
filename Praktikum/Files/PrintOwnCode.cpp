#include <iostream>
#include <fstream>


int main()
{
    std::ifstream stream  ("ConsoleApplication1.cpp");
    if (!stream.is_open())
    {
    std::cout << "Not opened correctly";
    }

    char buff[256];

    while(!stream.eof())
    {
        stream.getline(buff, 256);
        std::cout << buff<<std::endl;
    }

    stream.close();
}
