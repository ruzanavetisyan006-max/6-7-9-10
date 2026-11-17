#include <iostream>

using std::cout;
using std::endl;

class Rectangle {
public:
    Rectangle(double length = 1.0, double width = 1.0);

    bool setLength(double length);
    bool setWidth(double width);

    double getLength() const;
    double getWidth() const;

    double perimeter() const;
    double area() const;

private:
    double length;
    double width;
};

Rectangle::Rectangle(double len, double wid) {
    setLength(len);
    setWidth(wid);
}

bool Rectangle::setLength(double len) {
    if (len > 0.0 && len < 20.0) {
        length = len;
        return true;
    }
    length = 1.0;
    return false;
}

bool Rectangle::setWidth(double wid) {
    if (wid > 0.0 && wid < 20.0) {
        width = wid;
        return true;
    }
    width = 1.0;
    return false;
}

double Rectangle::getLength() const {
    return length;
}

double Rectangle::getWidth() const {
    return width;
}

double Rectangle::perimeter() const {
    return 2.0 * (length + width);
}

double Rectangle::area() const {
    return length * width;
}

int main() {
    Rectangle rect(5.5, 3.0);

    cout << "Rectangle created with length = " << rect.getLength() 
         << " and width = " << rect.getWidth() << endl;
    cout << "Perimeter: " << rect.perimeter() << endl;
    cout << "Area: " << rect.area() << endl << endl;

    cout << "Attempting to set invalid length (25.0):" << endl;
    if (rect.setLength(25.0)) {
        cout << "Success!" << endl;
    } else {
        cout << "Error: Length must be > 0.0 and < 20.0! Set failed." << endl;
    }
    cout << "Current length: " << rect.getLength() << endl << endl;

    cout << "Attempting to set valid values (12.5, 4.2):" << endl;
    rect.setLength(12.5);
    rect.setWidth(4.2);
    cout << "New length = " << rect.getLength() << ", new width = " << rect.getWidth() << endl;
    cout << "New Perimeter: " << rect.perimeter() << endl;
    cout << "New Area: " << rect.area() << endl;

    return 0;
}