//Да се имплементира структура Student, характеризираща се с :
//
//факултетен номер
//име
//среден успех
//
//Да се реализират методи write / read, приемащи някакъв поток,
//които съответно да четат данни за студента и да могат да записват студент във файл.
//
//Да се направят функции writeStudents / readStudents, 
//които получават масив от студенти и поток към файл, 
//от който могат да четат данни за студентите и да записват данни.



#include <iostream>
#include <fstream>


struct Student
{
    char* FN;
    char* Name;
    double grade;
};

void freeStudent(Student& s)
{
    delete[] s.FN;
    delete[] s.Name;
}


size_t returnNumberOfStudents(std::ifstream& stream)
{
    char buff[256];
    size_t counter = 0;
    while (!stream.eof())
    {
        stream.getline(buff, 256);
        counter++;
    }
    stream.clear();
    stream.seekg(0, std::ios::beg);
    return counter;
}

struct groupOfStudents
{
    Student* group = nullptr;
    size_t numberOfStudents;
};

void printStudent(const Student& s)
{
    std::cout << "NAME: " << s.Name << " FN: " << s.FN << " Grade : " << s.grade;
}

void initialiseCharPointer(char*& a, const char* b)
{
    size_t size = strlen(b);
    size++;
    a = new char[size];
    strcpy_s(a, size, b);
}

void readStudent(std::ifstream& stream, Student& s)
{
    char buff[256];
    stream.getline(buff, 256, ';');
    initialiseCharPointer(s.Name, buff);

    stream.getline(buff, 256, ';');
    initialiseCharPointer(s.FN, buff);

    stream >> s.grade;
}

void freeStudents(groupOfStudents& G)
{
    for (int i = 0; i < G.numberOfStudents; i++)
    {
        freeStudent(G.group[i]);
    }
}

void writeStudent(const Student& s, std::ofstream& stream)
{
    stream << s.Name << ';';
    stream << s.FN << ';';
    stream << s.grade << ';' << '\n';
}

void writeStudentSS(const groupOfStudents& grp, std::ofstream& stream)
{
    for (size_t i = 0; i < grp.numberOfStudents; i++)
    {
        writeStudent(grp.group[i], stream);
    }
}

void write(const groupOfStudents& grp, std::ofstream& stream)
{   
    stream.seekp(0, std::ios::end);
    for (size_t i = 0; i < grp.numberOfStudents; i++)
    {
        writeStudent(grp.group[i], stream);
    }
}

void read(std::ifstream& stream, groupOfStudents& grp)
{
    size_t numberOfStudentsInFile = returnNumberOfStudents(stream);
    grp.group = new Student[numberOfStudentsInFile];
    grp.numberOfStudents = numberOfStudentsInFile;
    size_t i = 0;
    size_t counter = 0;
   
    for(int i =0;i< numberOfStudentsInFile;i++)
    {   stream.seekg(counter, std::ios::cur);
       readStudent(stream, grp.group[i]);
       counter = 3;
    }
}

void printStudetSS(const groupOfStudents& grp)
{
    for (size_t i = 0; i < grp.numberOfStudents; i++)
    {
        printStudent(grp.group[i]);
        std::cout << std::endl;
    }
}

void initialiseStuden(const char* line, Student& s)
{
    char buff[256];
    size_t i = 0;
    size_t k = 0;


    for (int z = 0; z < 3; z++)
    {
        while (line[i] != ';' && line[i] != '\0')
        {
            buff[k] = line[i];
            k++;
            i++;
        }
        buff[k] = '\0';
        i++;
        
        switch (z)
        {
        case 0: {
            initialiseCharPointer(s.Name, buff); break;
        }
        case 1: {initialiseCharPointer(s.FN, buff); break; }
        case 2: {s.grade = atof(buff); break; }
        default:
            break;
        }


        buff[0] = '\0';
        k = 0;
    }




}

void initialiseStudent(Student& s, const char* name, const char* FN, double grade)
{
    size_t sizeOfString = strlen(name);
    sizeOfString++;
    s.Name = new char[sizeOfString];
    strcpy_s(s.Name, sizeOfString, name);


    sizeOfString = strlen(FN);
    sizeOfString++;
    s.FN = new char[sizeOfString];
    strcpy_s(s.FN, sizeOfString, FN);

    s.grade = grade;

}

int main()
{
    int* ptr;

    if (ptr == NULL)
    {
        std::cout << "ZDR";
    }
}
