#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

struct Point {
    double x;
    double y;

    Point(double xVal = 0.0, double yVal = 0.0) : x(xVal), y(yVal) {}
};

class Rectangle {
public:
    Rectangle(Point p1, Point p2, Point p3, Point p4);

    bool setCoordinates(Point p1, Point p2, Point p3, Point p4);

    double getLength() const;
    double getWidth() const;
    double perimeter() const;
    double area() const;
    bool square() const;

    void print() const;

private:
    Point corners[4];

    bool isValidCoordinate(double val) const;
    double distance(Point a, Point b) const;
};

Rectangle::Rectangle(Point p1, Point p2, Point p3, Point p4) {
    if (!setCoordinates(p1, p2, p3, p4)) {
        cout << "Error: Invalid coordinates! Defaulting to a standard rectangle." << endl;
        corners[0] = Point(0.0, 2.0);
        corners[1] = Point(2.0, 2.0);
        corners[2] = Point(2.0, 0.0);
        corners[3] = Point(0.0, 0.0);
    }
}

bool Rectangle::setCoordinates(Point p1, Point p2, Point p3, Point p4) {
    Point temp[4] = {p1, p2, p3, p4};
    for (int i = 0; i < 4; i++) {
        if (!isValidCoordinate(temp[i].x) || !isValidCoordinate(temp[i].y)) {
            return false;
        }
    }

    double d01 = distance(temp[0], temp[1]);
    double d12 = distance(temp[1], temp[2]);
    double d23 = distance(temp[2], temp[3]);
    double d30 = distance(temp[3], temp[0]);
    double d02 = distance(temp[0], temp[2]);
    double d13 = distance(temp[1], temp[3]);


    const double eps = 0.0001;
    bool oppositeSidesEqual = (std::abs(d01 - d23) < eps) && (std::abs(d12 - d30) < eps);
    bool diagonalsEqual = std::abs(d02 - d13) < eps;

    if (oppositeSidesEqual && diagonalsEqual && d01 > 0 && d12 > 0) {
        for (int i = 0; i < 4; i++) {
            corners[i] = temp[i];
        }
        return true;
    }

    return false;
}

bool Rectangle::isValidCoordinate(double val) const {
    return (val >= 0.0 && val <= 20.0);
}

double Rectangle::distance(Point a, Point b) const {
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

double Rectangle::getLength() const {
    double side1 = distance(corners[0], corners[1]);
    double side2 = distance(corners[1], corners[2]);
    return (side1 > side2) ? side1 : side2;
}

double Rectangle::getWidth() const {
    double side1 = distance(corners[0], corners[1]);
    double side2 = distance(corners[1], corners[2]);
    return (side1 < side2) ? side1 : side2;
}

double Rectangle::perimeter() const {
    return 2.0 * (getLength() + getWidth());
}

double Rectangle::area() const {
    return getLength() * getWidth();
}

bool Rectangle::square() const {
    const double eps = 0.0001;
    return std::abs(getLength() - getWidth()) < eps;
}

void Rectangle::print() const {
    cout << "Corners: ";
    for (int i = 0; i < 4; i++) {
        cout << "(" << corners[i].x << ", " << corners[i].y << ") ";
    }
    cout << endl;
}

int main() {
    Point p1(1.0, 4.0);
    Point p2(5.0, 4.0);
    Point p3(5.0, 1.0);
    Point p4(1.0, 1.0);

    Rectangle rect(p1, p2, p3, p4);
    cout << "Test 1 Valid Rectangle:" << endl;
    rect.print();
    cout << "Length: " << rect.getLength() << endl;
    cout << "Width: " << rect.getWidth() << endl;
    cout << "Perimeter: " << rect.perimeter() << endl;
    cout << "Area: " << rect.area() << endl;
    cout << "Is Square? " << (rect.square() ? "Yes" : "No") << endl << endl;

    cout << "Test 2 Invalid Coordinates (> 20.0):" << endl;
    Point badP1(25.0, 5.0);
    Point badP2(30.0, 5.0);
    Point badP3(30.0, 1.0);
    Point badP4(25.0, 1.0);

    Rectangle invalidRect(badP1, badP2, badP3, badP4);
    invalidRect.print();

    return 0;
}