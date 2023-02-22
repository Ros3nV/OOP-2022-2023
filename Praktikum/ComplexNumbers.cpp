#include <iostream>

struct ComplexNumber
{
    double real;
    double img;
};


void printComplexNumber(const ComplexNumber& c1)
{
    std::cout << "Real : " << c1.real << " Img: " << c1.img<<std::endl;
}

void initialiseComplexNumber(ComplexNumber& c1)
{
    std::cout << "Type Real: ";
    std::cin >> c1.real;
    std::cout << " Type Img:";
    std::cin >> c1.img;
    std::cout << std::endl;

}

ComplexNumber sumOfComplexNumber(const ComplexNumber& c1, const ComplexNumber& c2)
{
    ComplexNumber c3 ={ c1.real + c2.real,c1.img + c2.img };
    return c3;
}

int main()
{

    ComplexNumber c1;
    initialiseComplexNumber(c1);
    printComplexNumber(c1);
    ComplexNumber c2;
    initialiseComplexNumber(c2);
   ComplexNumber c3 = sumOfComplexNumber(c1, c2);
    printComplexNumber(c3);

}
