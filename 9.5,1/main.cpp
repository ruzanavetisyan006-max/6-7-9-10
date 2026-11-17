#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;

class Point {
public:
    Point(int xValue = 0, int yValue = 0) : x(xValue), y(yValue) {}

    void setX(int xValue) { x = xValue; }
    int getX() const { return x; }

    void setY(int yValue) { y = yValue; }
    int getY() const { return y; }

    void print() const {
        cout << '[' << x << ", " << y << ']';
    }

private:
    int x;
    int y;
};

class Square : public Point {
public:
    Square(int xValue = 0, int yValue = 0, double sideValue = 0.0)
        : Point(xValue, yValue), side(sideValue < 0.0 ? 0.0 : sideValue) {}

    void setSide(double sideValue) {
        side = (sideValue < 0.0 ? 0.0 : sideValue);
    }

    double getSide() const { return side; }

    double getArea() const {
        return side * side;
    }

    double getPerimeter() const {
        return 4 * side;
    }

    void print() const {
        cout << "Corner = ";
        Point::print();
        cout << "; Side = " << side;
    }

private:
    double side;
};

class Cube : public Square {
public:
    Cube(int xValue = 0, int yValue = 0, double sideValue = 0.0, double depthValue = 0.0)
        : Square(xValue, yValue, sideValue), depth(depthValue < 0.0 ? 0.0 : depthValue) {}

    void setDepth(double depthValue) {
        depth = (depthValue < 0.0 ? 0.0 : depthValue);
    }

    double getDepth() const { return depth; }

    double getArea() const {
        return 6 * Square::getArea();
    }

    double getVolume() const {
        return Square::getArea() * depth;
    }

    void print() const {
        Square::print();
        cout << "; Depth = " << depth;
    }

private:
    double depth;
};

class PointComp {
public:
    PointComp(int xValue = 0, int yValue = 0) : x(xValue), y(yValue) {}

    void setX(int xValue) { x = xValue; }
    int getX() const { return x; }

    void setY(int yValue) { y = yValue; }
    int getY() const { return y; }

    void print() const {
        cout << '[' << x << ", " << y << ']';
    }

private:
    int x;
    int y;
};

class SquareComp {
public:
    SquareComp(int xValue = 0, int yValue = 0, double sideValue = 0.0)
        : corner(xValue, yValue), side(sideValue < 0.0 ? 0.0 : sideValue) {}

    void setCorner(int xValue, int yValue) {
        corner.setX(xValue);
        corner.setY(yValue);
    }

    void setSide(double sideValue) {
        side = (sideValue < 0.0 ? 0.0 : sideValue);
    }

    double getSide() const { return side; }
    PointComp getCorner() const { return corner; }

    double getArea() const {
        return side * side;
    }

    double getPerimeter() const {
        return 4 * side;
    }

    void print() const {
        cout << "Corner = ";
        corner.print();
        cout << "; Side = " << side;
    }

private:
    PointComp corner;
    double side;
};

class CubeComp {
public:
    CubeComp(int xValue = 0, int yValue = 0, double sideValue = 0.0, double depthValue = 0.0)
        : baseSquare(xValue, yValue, sideValue), depth(depthValue < 0.0 ? 0.0 : depthValue) {}

    void setBase(int xValue, int yValue, double sideValue) {
        baseSquare.setCorner(xValue, yValue);
        baseSquare.setSide(sideValue);
    }

    void setDepth(double depthValue) {
        depth = (depthValue < 0.0 ? 0.0 : depthValue);
    }

    double getDepth() const { return depth; }
    SquareComp getBaseSquare() const { return baseSquare; }

    double getArea() const {
        return 6 * baseSquare.getArea();
    }

    double getVolume() const {
        return baseSquare.getArea() * depth;
    }

    void print() const {
        baseSquare.print();
        cout << "; Depth = " << depth;
    }

private:
    SquareComp baseSquare;
    double depth;
};

int main() {
    cout << "=== 1. Testing Inheritance (Cube) ===" << endl;
    Cube inheritedCube(1, 1, 3.0, 3.0);
    inheritedCube.print();
    cout << fixed << setprecision(2);
    cout << "\nSurface Area: " << inheritedCube.getArea() << endl;
    cout << "Volume: " << inheritedCube.getVolume() << endl;

    cout << "\n=== 2. Testing Composition (CubeComp) ===" << endl;
    CubeComp composedCube(2, 2, 4.0, 4.0);
    composedCube.print();
    cout << "\nSurface Area: " << composedCube.getArea() << endl;
    cout << "Volume: " << composedCube.getVolume() << endl;

    return 0;
}