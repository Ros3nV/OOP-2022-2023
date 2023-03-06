//Създайте нов тип, RationalNumber, който представя рационално число.Да се реализират следните функции за работа с рационално число :
//
//събират и умножават две рационални числа
//отпечатва рационално число по подходящ начин на стандартния изход
//установява дали рационално число x е по - голямо от рационално число y
//създайте масив от рационални числа
//намира най - голямото от рационалните числа
//сортира в низходящ ред елементите на редицата от рационални числа
#include <iostream>

struct RationalNumber
{
    int numerator;
    int denominator;
};

RationalNumber sumOfTwoRationalNumber(const RationalNumber& r1, const RationalNumber& r2)
{
    RationalNumber r3 = { r1.numerator + r2.numerator,r1.denominator + r2.denominator };
    return r3;
}

RationalNumber productOfTwoRationalNumber(const RationalNumber& r1, const RationalNumber& r2)
{
    RationalNumber r3 = { r1.numerator*r2.numerator,r1.denominator*r2.denominator };
    return r3;
}

void printRationalNumber(const RationalNumber& r1)
{
    std::cout << r1.numerator << '/' << r1.denominator<<std::endl;
}

bool isFirstNumberBiggerThanSecond(const RationalNumber& r1, const RationalNumber& r2)
{
    double first = 1.0*r1.numerator / r1.denominator;
    double second = 1.0*r2.numerator / r2.denominator;

    if (first > second)
        return true;
    return false;
}

void biggestRationalNumberOfArray(RationalNumber* arrayOfRN, size_t numbers)
{
    RationalNumber r = arrayOfRN[0];
    
    for (int i = 1; i < numbers; i++)
    {
        if (isFirstNumberBiggerThanSecond(r, arrayOfRN[i]))
        {
            r = arrayOfRN[i];
        }
    }
    printRationalNumber(r);

}

void sortRationalNumberOfArray(RationalNumber* arrayOfRN, size_t numbers)
{
    for (int i = 0; i < numbers - 1; i++)
    {
        for (int k = 0; k < numbers - 1; k++)
        {
            if (isFirstNumberBiggerThanSecond(arrayOfRN[k], arrayOfRN[k+1]))
            {
                RationalNumber r = arrayOfRN[k];
                arrayOfRN[k] = arrayOfRN[k+1];
                arrayOfRN[k+1] = r;
            }
        }
    }

    for (int i = 0; i < numbers ; i++)
    {
        printRationalNumber(arrayOfRN[i]);
        std::cout << std::endl;
    }
}




int main()
{
    std::cout << "Enter number of Rational Numbers: ";
    size_t numbers=5;
    /*std::cin >> numbers;*/

    RationalNumber* arrayOfRN = new RationalNumber[numbers];

    arrayOfRN[0] = { 1,4 };
    arrayOfRN[1] = { 6,2 };
    arrayOfRN[2] = { 3,7 };
    arrayOfRN[3] = { 5,2 };
    arrayOfRN[4] = { 1,2 };


    sortRationalNumberOfArray(arrayOfRN, numbers);

    delete[] arrayOfRN;

}
