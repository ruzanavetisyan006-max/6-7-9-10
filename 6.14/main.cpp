#include <iostream>
#include <cmath>
#include <algorithm>

using std::cout;
using std::endl;

struct Point {
    double x;
    double y;

    Point(double xVal = 0.0, double yVal = 0.0) : x(xVal), y(yVal) {}
};

class Rectangle {
public:
    Rectangle(Point p1, Point p2, Point p3, Point p4, char fillColor = '*', char perimeterColor = 'x');

    bool setCoordinates(Point p1, Point p2, Point p3, Point p4);
    
    void setFillCharacter(char c);
    void setPerimeterCharacter(char c);

    double getLength() const;
    double getWidth() const;
    double perimeter() const;
    double area() const;
    bool square() const;

    void draw() const;
    void print() const;

private:
    Point corners[4];
    char fillChar;
    char perimeterChar;

    bool isValidCoordinate(double val) const;
    double distance(Point a, Point b) const;
    double distanceToSegment(Point p, Point a, Point b) const;
    bool isInsideOrOn(Point p) const;
};

Rectangle::Rectangle(Point p1, Point p2, Point p3, Point p4, char fillColor, char perimeterColor) {
    fillChar = fillColor;
    perimeterChar = perimeterColor;

    if (!setCoordinates(p1, p2, p3, p4)) {
        cout << "Error: Invalid coordinates! Defaulting to a standard rectangle." << endl;
        corners[0] = Point(2.0, 8.0);
        corners[1] = Point(8.0, 8.0);
        corners[2] = Point(8.0, 2.0);
        corners[3] = Point(2.0, 2.0);
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

void Rectangle::setFillCharacter(char c) {
    fillChar = c;
}

void Rectangle::setPerimeterCharacter(char c) {
    perimeterChar = c;
}

bool Rectangle::isValidCoordinate(double val) const {
    return (val >= 0.0 && val <= 20.0);
}

double Rectangle::distance(Point a, Point b) const {
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

double Rectangle::distanceToSegment(Point p, Point a, Point b) const {
    double l2 = std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2);
    if (l2 == 0.0) return distance(p, a);

    double t = ((p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y)) / l2;
    t = std::max(0.0, std::min(1.0, t));

    Point projection(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y));
    return distance(p, projection);
}

bool Rectangle::isInsideOrOn(Point p) const {
    bool hasPos = false;
    bool hasNeg = false;

    for (int i = 0; i < 4; i++) {
        Point a = corners[i];
        Point b = corners[(i + 1) % 4];

        double cross = (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);

        if (cross > 0.0001) hasPos = true;
        if (cross < -0.0001) hasNeg = true;

        if (hasPos && hasNeg) return false;
    }
    return true;
}

void Rectangle::draw() const {
    cout << "Drawing Rectangle (Perimeter: '" << perimeterChar << "', Fill: '" << fillChar << "'):" << endl;
    
    for (int row = 0; row < 25; row++) {
        double y = 24.0 - row;
        for (int col = 0; col < 25; col++) {
            double x = col;
            Point p(x, y);

            bool onPerimeter = false;
            for (int i = 0; i < 4; i++) {
                if (distanceToSegment(p, corners[i], corners[(i + 1) % 4]) <= 0.45) {
                    onPerimeter = true;
                    break;
                }
            }

            if (onPerimeter) {
                cout << perimeterChar << ' ';
            } else if (isInsideOrOn(p)) {
                cout << fillChar << ' ';
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
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
    Point p1(2.0, 10.0);
    Point p2(12.0, 10.0);
    Point p3(12.0, 4.0);
    Point p4(2.0, 4.0);

    Rectangle rect(p1, p2, p3, p4, 'o', '#');

    rect.print();
    cout << "Length: " << rect.getLength() << ", Width: " << rect.getWidth() << endl;
    cout << "Perimeter: " << rect.perimeter() << ", Area: " << rect.area() << endl << endl;

    rect.draw();

    cout << "Changing characters and redrawing:" << endl;
    rect.setFillCharacter('+');
    rect.setPerimeterCharacter('X');
    rect.draw();

    return 0;
}