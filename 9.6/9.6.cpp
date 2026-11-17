#include <iostream>
#include <iomanip>
#include <cmath>

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;

class Point {
public:
    Point(double xVal = 0.0, double yVal = 0.0) : x(xVal), y(yVal) {}

    void setX(double xVal) { x = xVal; }
    double getX() const { return x; }

    void setY(double yVal) { y = yVal; }
    double getY() const { return y; }

    void print() const {
        cout << '[' << x << ", " << y << ']';
    }

private:
    double x;
    double y;
};

class Quadrilateral {
public:
    Quadrilateral(double x1, double y1, double x2, double y2,
                  double x3, double y3, double x4, double y4)
        : p1(x1, y1), p2(x2, y2), p3(x3, y3), p4(x4, y4) {}

    Point getPoint1() const { return p1; }
    Point getPoint2() const { return p2; }
    Point getPoint3() const { return p3; }
    Point getPoint4() const { return p4; }

    void print() const {
        cout << "Points: ";
        p1.print(); cout << ", ";
        p2.print(); cout << ", ";
        p3.print(); cout << ", ";
        p4.print();
    }

private:
    Point p1;
    Point p2;
    Point p3;
    Point p4;
};

class Trapezoid : public Quadrilateral {
public:
    Trapezoid(double x1, double y1, double x2, double y2,
              double x3, double y3, double x4, double y4, double h = 0.0)
        : Quadrilateral(x1, y1, x2, y2, x3, y3, x4, y4), height(h < 0.0 ? 0.0 : h) {}

    void setHeight(double h) { height = (h < 0.0 ? 0.0 : h); }
    double getHeight() const { return height; }

    void print() const {
        Quadrilateral::print();
        cout << "; Height = " << height;
    }

private:
    double height;
};

class Parallelogram : public Trapezoid {
public:
    Parallelogram(double x1, double y1, double x2, double y2,
                  double x3, double y3, double x4, double y4, double h = 0.0)
        : Trapezoid(x1, y1, x2, y2, x3, y3, x4, y4, h) {}

    double getArea() const {
        Point p1 = getPoint1();
        Point p2 = getPoint2();
        double base = std::sqrt(std::pow(p2.getX() - p1.getX(), 2) + std::pow(p2.getY() - p1.getY(), 2));
        return base * getHeight();
    }
};

class Rectangle : public Parallelogram {
public:
    Rectangle(double x1, double y1, double x2, double y2,
              double x3, double y3, double x4, double y4)
        : Parallelogram(x1, y1, x2, y2, x3, y3, x4, y4, 
                        std::sqrt(std::pow(x3 - x2, 2) + std::pow(y3 - y2, 2))) {}

    double getArea() const {
        Point p1 = getPoint1();
        Point p2 = getPoint2();
        Point p3 = getPoint3();
        double width = std::sqrt(std::pow(p2.getX() - p1.getX(), 2) + std::pow(p2.getY() - p1.getY(), 2));
        double length = std::sqrt(std::pow(p3.getX() - p2.getX(), 2) + std::pow(p3.getY() - p2.getY(), 2));
        return width * length;
    }
};

class Square : public Rectangle {
public:
    Square(double x1, double y1, double x2, double y2,
           double x3, double y3, double x4, double y4)
        : Rectangle(x1, y1, x2, y2, x3, y3, x4, y4) {}

    double getArea() const {
        Point p1 = getPoint1();
        Point p2 = getPoint2();
        double side = std::sqrt(std::pow(p2.getX() - p1.getX(), 2) + std::pow(p2.getY() - p1.getY(), 2));
        return side * side;
    }
};

int main() {
    cout << fixed << setprecision(2);

    cout << "=== Testing Trapezoid ===" << endl;
    Trapezoid trap(0, 0, 4, 0, 3, 2, 1, 2, 2.0);
    trap.print();
    cout << endl;

    cout << "\n=== Testing Square ===" << endl;
    Square sq(0, 0, 4, 0, 4, 4, 0, 4);
    sq.print();
    cout << "\nSquare Area: " << sq.getArea() << endl;

    return 0;
}