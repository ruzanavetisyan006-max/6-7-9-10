#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;

#ifndef POINT3_H
#define POINT3_H

class Point3 {
public:
    Point3(int xValue = 0, int yValue = 0) : x(xValue), y(yValue) {}

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

#endif

#ifndef CIRCLE4_H
#define CIRCLE4_H

class Circle4 {
public:
    Circle4(int xValue = 0, int yValue = 0, double radiusValue = 0.0)
        : center(xValue, yValue), radius(radiusValue < 0.0 ? 0.0 : radiusValue) {}

    void setCenter(int xValue, int yValue) {
        center.setX(xValue);
        center.setY(yValue);
    }

    void setRadius(double radiusValue) {
        radius = (radiusValue < 0.0 ? 0.0 : radiusValue);
    }

    double getRadius() const { return radius; }
    Point3 getCenter() const { return center; }

    double getDiameter() const { return 2 * radius; }
    double getCircumference() const { return 3.14159 * getDiameter(); }
    double getArea() const { return 3.14159 * radius * radius; }

    void print() const {
        cout << "Center = ";
        center.print();
        cout << "; Radius = " << radius;
    }

private:
    Point3 center;
    double radius;
};

#endif

#ifndef CYLINDER_H
#define CYLINDER_H

class Cylinder {
public:
    Cylinder(int xValue = 0, int yValue = 0, double radiusValue = 0.0, double heightValue = 0.0)
        : baseCircle(xValue, yValue, radiusValue), height(heightValue < 0.0 ? 0.0 : heightValue) {}

    void setBase(int xValue, int yValue, double radiusValue) {
        baseCircle.setCenter(xValue, yValue);
        baseCircle.setRadius(radiusValue);
    }

    void setHeight(double heightValue) {
        height = (heightValue < 0.0 ? 0.0 : heightValue);
    }

    double getHeight() const { return height; }
    Circle4 getBase() const { return baseCircle; }

    double getArea() const {
        return 2 * baseCircle.getArea() + baseCircle.getCircumference() * height;
    }

    double getVolume() const {
        return baseCircle.getArea() * height;
    }

    void print() const {
        baseCircle.print();
        cout << "; Height = " << height;
    }

private:
    Circle4 baseCircle;
    double height;
};

#endif

int main() {
    Cylinder cylinder(12, 23, 2.5, 5.7);

    cout << "Initial cylinder:" << endl;
    cylinder.print();
    cout << endl;

    cylinder.setBase(2, 2, 4.25);
    cylinder.setHeight(10.0);

    cout << "\nUpdated cylinder:" << endl;
    cylinder.print();

    cout << fixed << setprecision(2);
    cout << "\nArea: " << cylinder.getArea() << endl;
    cout << "Volume: " << cylinder.getVolume() << endl;

    return 0;
}