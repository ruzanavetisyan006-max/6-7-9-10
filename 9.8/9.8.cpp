#include <iostream>
#include <iomanip>
#include <cmath>

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;

class Shape {
public:
    virtual double getArea() const { return 0.0; }
    virtual double getVolume() const { return 0.0; }
    virtual void print() const = 0;
    virtual ~Shape() {}
};

class TwoDimensionalShape : public Shape {
public:
    double getVolume() const override { return 0.0; }
};

class ThreeDimensionalShape : public Shape {
public:
    virtual double getArea() const override = 0;
    virtual double getVolume() const override = 0;
};

class Circle : public TwoDimensionalShape {
public:
    Circle(double r = 0.0) : radius(r < 0.0 ? 0.0 : r) {}

    void setRadius(double r) { radius = (r < 0.0 ? 0.0 : r); }
    double getRadius() const { return radius; }

    double getArea() const override {
        return 3.14159 * radius * radius;
    }

    void print() const override {
        cout << "Circle with radius: " << radius;
    }

private:
    double radius;
};

class Square : public TwoDimensionalShape {
public:
    Square(double s = 0.0) : side(s < 0.0 ? 0.0 : s) {}

    void setSide(double s) { side = (s < 0.0 ? 0.0 : s); }
    double getSide() const { return side; }

    double getArea() const override {
        return side * side;
    }

    void print() const override {
        cout << "Square with side: " << side;
    }

private:
    double side;
};

class Sphere : public ThreeDimensionalShape {
public:
    Sphere(double r = 0.0) : radius(r < 0.0 ? 0.0 : r) {}

    void setRadius(double r) { radius = (r < 0.0 ? 0.0 : r); }
    double getRadius() const { return radius; }

    double getArea() const override {
        return 4 * 3.14159 * radius * radius;
    }

    double getVolume() const override {
        return (4.0 / 3.0) * 3.14159 * radius * radius * radius;
    }

    void print() const override {
        cout << "Sphere with radius: " << radius;
    }

private:
    double radius;
};

class Cube : public ThreeDimensionalShape {
public:
    Cube(double s = 0.0) : side(s < 0.0 ? 0.0 : s) {}

    void setSide(double s) { side = (s < 0.0 ? 0.0 : s); }
    double getSide() const { return side; }

    double getArea() const override {
        return 6 * side * side;
    }

    double getVolume() const override {
        return side * side * side;
    }

    void print() const override {
        cout << "Cube with side: " << side;
    }

private:
    double side;
};

int main() {
    cout << fixed << setprecision(2);

    Shape *shapes[4];
    shapes[0] = new Circle(5.0);
    shapes[1] = new Square(4.0);
    shapes[2] = new Sphere(3.0);
    shapes[3] = new Cube(3.0);

    for (int i = 0; i < 4; ++i) {
        shapes[i]->print();
        cout << "\nArea: " << shapes[i]->getArea();
        cout << "\nVolume: " << shapes[i]->getVolume() << "\n\n";
        delete shapes[i];
    }

    return 0;
}