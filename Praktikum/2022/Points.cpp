//Създайте нов тип, Point представяща се чрез две координати в декартова система.Да се реализират следните функции за работа с точките :
//
//четене на данните от стандартния вход
//отпечатване на данните на стандартния изход
//разстояние до центъра(0, 0)
//разстояние между две точки
//създайте масив от точки
//прочита и извежда масив от точки



#include <iostream>

struct Point
{
    double X;
    double Y;
};


Point initialisePoint(double X, double Y)
{
    Point p1 = { X,Y };
    return  p1;
}

void printPoint(const Point& p1)
{
    std::cout << "X: " << p1.X << " Y: " << p1.Y;
}


double distanceFromCenter(const Point& p1)
{
    return sqrt(pow(p1.X, 2) + pow(p1.Y, 2));
}

double distanceFromOnePointToAnother(const Point& p1, const Point& p2)
{
    return sqrt(pow(p2.X-p1.X, 2) + pow(p2.Y-p1.X, 2));
}


int main()
{
    std::cout << "Enter Number of Points: ";
    size_t number;
    std::cin >> number;

    Point* arrayOfPoints = new Point [number];
    arrayOfPoints[0]=initialisePoint(3,3);
    arrayOfPoints[1]=initialisePoint(4,4);
    std::cout << distanceFromOnePointToAnother(arrayOfPoints[0], arrayOfPoints[1]);

    delete [] arrayOfPoints;
}
