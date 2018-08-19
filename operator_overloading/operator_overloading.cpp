#include <iostream>
using namespace std;

class Point2D{
public:
    Point2D();
    Point2D(int, int);
    int x(){return _x;}
    int y(){return _y;}
    Point2D operator+(const Point2D&);
    Point2D operator-(const Point2D&);

    Point2D& operator++();  //++p
    Point2D operator++(int);  //p++


private:
    int _x;
    int _y;
};

int main()
{
    Point2D p1(5, 5);
    Point2D p2(10,10);
    Point2D p3;

    p3 = p1 + p2;
    cout << "(x,y): (" << p3.x() << ", " << p3.y() << ")" << endl; //(x,y): (15, 15)

    p3 = p1++;
    cout << "(x,y): (" << p3.x() << ", " << p3.y() << ")" << endl; //(x,y): (5, 5)

    p3 = ++p1;
    cout << "(x,y): (" << p3.x() << ", " << p3.y() << ")" << endl; //(x,y): (7, 7)
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    return 0;//return a.exec();
}


Point2D::Point2D(){
    _x = 0;
    _y = 0;
}

Point2D::Point2D(int x, int y){
    _x = x;
    _y = y;
}
Point2D Point2D::operator+(const Point2D& p){
    Point2D tmp(this->_x + p._x, this->_y + p._y);
    return tmp;
}
Point2D Point2D::operator-(const Point2D& p){
    Point2D tmp(this->_x - p._x, this->_y - p._y);
    return tmp;
}

Point2D& Point2D::operator++(){
    this->_x++;
    this->_y++;
    return *this;
}

Point2D Point2D::operator++(int){
    Point2D tmp(_x,_y);
    this->_x++;
    this->_y++;
    return tmp;
}
