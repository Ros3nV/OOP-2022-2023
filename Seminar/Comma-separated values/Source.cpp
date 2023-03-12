#include <iostream>
#include <fstream>

const size_t MAX_SIZE = 128;

struct Student
{
	char* firstName=nullptr;
	char* lastName=nullptr;
	char* email=nullptr;
	char* FN=nullptr;
};

void deleteStudent(Student& s)
{
	delete[] s.firstName;
	delete[] s.lastName;
	delete[] s.email ;
	delete[] s.FN;
}

struct groupOfStudents
{
	Student* group;
	size_t numberOfStudents;
};

void deleteGroup(groupOfStudents& grp)
{
	for (size_t i = 0; i < grp.numberOfStudents; i++)
	{
		deleteStudent(grp.group[i]);
	}
}

void initialiseCharPointer(char*& pointer, const char* buff)
{
	if (pointer != nullptr)
	{
		delete[] pointer;
	}
	size_t sizeOfBuff = strlen(buff) + 1;
	pointer = new char[sizeOfBuff];
	strcpy_s(pointer, sizeOfBuff, buff);
}

size_t returnNumberOfStudents(std::ifstream& file)
{
	file.seekg(39, std::ios::beg);
	char buff[MAX_SIZE];
	size_t counter = 0;
	while (!file.eof())
	{
		file.getline(buff,MAX_SIZE);
		counter++;
	}
	return counter;
}

void readStudentFromStream(Student& s, std::ifstream& file)
{
	char buff[MAX_SIZE];
	file.getline(buff, MAX_SIZE, ',');
	initialiseCharPointer(s.firstName, buff);

	file.getline(buff, MAX_SIZE, ',');
	initialiseCharPointer(s.lastName, buff);

	file.getline(buff, MAX_SIZE, ',');
	initialiseCharPointer(s.email, buff);

	file.getline(buff, MAX_SIZE);
	initialiseCharPointer(s.FN, buff);
}

void readGroupFromFile(groupOfStudents& grp, std::ifstream& file)
{
	grp.numberOfStudents = returnNumberOfStudents(file);
	grp.group = new Student[grp.numberOfStudents];
	file.seekg(39, std::ios::beg);


	for (size_t i = 0; i < grp.numberOfStudents; i++)
	{
		readStudentFromStream(grp.group[i], file);
	}

}

void printStudent(const Student& s)
{
	std::cout << "Name: " << 
		s.firstName << ' ' << 
		s.lastName << ", Email: " << 
		s.email << ", FN: " <<
		s.FN << std::endl;
}

void printStudentByFN(const groupOfStudents& a, const char* FN)
{
	const char* ptr;
	for (int i = 0; i < a.numberOfStudents; i++)
	{
		ptr = a.group[i].FN;
		if (strcmp(ptr, FN) == 0)
		{
			printStudent(a.group[i]);
			return;
		}
	}
	std::cout << "No such FN!" << std::endl;
}

void changeEmailByFn(groupOfStudents& a, const char* FN,const char* EMAIL)
{
	const char* ptr;
	int indexOfStudent = -1;
	for (int i = 0; i < a.numberOfStudents; i++)
	{
		ptr = a.group[i].FN;
		if (strcmp(ptr, FN) == 0)
		{
			indexOfStudent = i;
			break;
		}
	}
	if (indexOfStudent == -1) { std::cout << "No such FN!" << std::endl; return; }

	initialiseCharPointer(a.group[indexOfStudent].email, EMAIL);
}

void writeStudentToFile(const Student& s, std::ofstream& file)
{
	file << s.firstName << ',' << s.lastName << ',' << s.email << ',' << s.FN;
}

void writeGroupToFile(const groupOfStudents& grp, const char* nameFile)
{
	std::ofstream file(nameFile);
	if(!file.is_open())
	{
		std::cout<<"ERROR IN OPENING FILE";
		return;
	}
	file << "First name,Last name,Email address,FN";
	for (size_t i = 0; i < grp.numberOfStudents; i++)
	{
		file << '\n';
		writeStudentToFile(grp.group[i], file);
	}
	file.close();
}

void returnToNextSpace(const char* buff, size_t& index,char*& word)
{
	char buff2[MAX_SIZE];
	size_t counter = 0;
	while (buff[index] !=' ' && buff[index] != '\0')
	{
		buff2[counter] = buff[index];
		counter++;
		index++;
	}
	buff2[counter] = '\0';
	index++;
	//std::cout << buff2<<std::endl<<std::endl;
	initialiseCharPointer(word, buff2);
}

bool comandExecution(const char* buff,groupOfStudents& a)
{
	if (strlen(buff) < 6)
	{
		std::cout << "WRONG COMMAND TRY AGAIN!" << std::endl; return true;
	}


	char comand[MAX_SIZE];
	int i = 0;
	while (buff[i] != ' ' && buff[i] != '\0')
	{
		comand[i] = buff[i];
		i++;
	}
	comand[i] = '\0';

	if (strcmp(comand, "print") == 0)
	{
		char* FN=nullptr;
		size_t indexOfSpace = 6; // lenght of print +1;
		returnToNextSpace(buff, indexOfSpace,FN);
		printStudentByFN(a,FN);
		delete[] FN;
		return true;
	}
	else
	{
		if (strcmp(comand, "edit") == 0)
		{
			char* FN = nullptr;
			char* email = nullptr;
			size_t indexOfSpace = 5;
			returnToNextSpace(buff, indexOfSpace, FN);
			returnToNextSpace(buff, indexOfSpace, email);
			changeEmailByFn(a, FN, email);
			delete[]FN;
			delete[]email;
			return true;
		}
		else
		{
			if (strcmp(comand, "save") == 0)
			{
				char* nameOfFile = nullptr;
				size_t indexOfSpace = 5;
				returnToNextSpace(buff, indexOfSpace, nameOfFile);
				writeGroupToFile(a, nameOfFile);
				delete[]nameOfFile;
				return false;
			}
		}

	}

	
	std::cout << "WRONG COMMAND TRY AGAIN!" << std::endl; return true;
}



int main()
{
	char buff[MAX_SIZE];
	std::cout << "Open File:";
	std::cin.getline(buff, 256);

	std::ifstream file(buff);

	if (!file.is_open())
	{
		std::cout << "ERROR";
		return -1;
	}
	groupOfStudents a;
	readGroupFromFile(a, file);
	file.close();
	bool repeat = true;
	while (repeat)
	{
		std::cout << "Enter Comand: ";
		std::cin.getline(buff, 256);
	    repeat=comandExecution(buff, a);
	}
	deleteGroup(a);
	return 1;
}
