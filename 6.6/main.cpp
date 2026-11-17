#include <iostream>

using std::cout;
using std::endl;

class Complex {
public:
    Complex(double real = 0.0, double imaginary = 0.0);

    Complex add(const Complex &right) const;
    Complex subtract(const Complex &right) const;
    void print() const;

private:
    double realPart;
    double imaginaryPart;
};

Complex::Complex(double real, double imaginary) {
    realPart = real;
    imaginaryPart = imaginary;
}

Complex Complex::add(const Complex &right) const {
    return Complex(realPart + right.realPart, imaginaryPart + right.imaginaryPart);
}

Complex Complex::subtract(const Complex &right) const {
    return Complex(realPart - right.realPart, imaginaryPart - right.imaginaryPart);
}

void Complex::print() const {
    cout << "(" << realPart << ", " << imaginaryPart << ")";
}

int main() {
    Complex x(9.5, 7.7);
    Complex y(1.2, 3.1);
    Complex z;

    cout << "x = ";
    x.print();
    cout << "\ny = ";
    y.print();
    cout << endl << endl;

    z = x.add(y);
    cout << "Addition (x + y) = ";
    z.print();
    cout << endl;

    z = x.subtract(y);
    cout << "Subtraction (x - y) = ";
    z.print();
    cout << endl;

    return 0;
}