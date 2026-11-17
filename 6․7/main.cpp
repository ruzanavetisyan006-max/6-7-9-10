#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

class Rational {
public:
    Rational(int numerator = 0, int denominator = 1);

    Rational add(const Rational &right) const;
    Rational subtract(const Rational &right) const;
    Rational multiply(const Rational &right) const;
    Rational divide(const Rational &right) const;

    void printRational() const;
    void printRationalAsFloat() const;

private:
    int num;
    int den;

    void reduce();
    int gcd(int a, int b) const;
};

Rational::Rational(int numerator, int denominator) {
    num = numerator;
    den = (denominator != 0) ? denominator : 1;
    reduce();
}

Rational Rational::add(const Rational &right) const {
    int newNum = (num * right.den) + (right.num * den);
    int newDen = den * right.den;
    return Rational(newNum, newDen);
}

Rational Rational::subtract(const Rational &right) const {
    int newNum = (num * right.den) - (right.num * den);
    int newDen = den * right.den;
    return Rational(newNum, newDen);
}

Rational Rational::multiply(const Rational &right) const {
    int newNum = num * right.num;
    int newDen = den * right.den;
    return Rational(newNum, newDen);
}

Rational Rational::divide(const Rational &right) const {
    if (right.num == 0) {
        cout << "Error: Division by zero!" << endl;
        return Rational(0, 1);
    }
    int newNum = num * right.den;
    int newDen = den * right.num;
    return Rational(newNum, newDen);
}

void Rational::printRational() const {
    if (den == 0) {
        cout << "Undefined";
    } else if (num == 0) {
        cout << 0;
    } else {
        cout << num << "/" << den;
    }
}

void Rational::printRationalAsFloat() const {
    double value = static_cast<double>(num) / den;
    cout << value;
}

int Rational::gcd(int a, int b) const {
    int c = std::abs(a);
    int d = std::abs(b);
    while (d != 0) {
        int temp = d;
        d = c % d;
        c = temp;
    }
    return (c != 0) ? c : 1;
}

void Rational::reduce() {
    if (num == 0) {
        den = 1;
        return;
    }
    int common = gcd(num, den);
    num /= common;
    den /= common;

    if (den < 0) {
        num = -num;
        den = -den;
    }
}

int main() {
    Rational x(2, 4);
    Rational y(3, 8);
    Rational z;

    cout << "x = ";
    x.printRational();
    cout << " (Float: ";
    x.printRationalAsFloat();
    cout << ")" << endl;

    cout << "y = ";
    y.printRational();
    cout << " (Float: ";
    y.printRationalAsFloat();
    cout << ")" << endl << endl;

    z = x.add(y);
    cout << "Addition (x + y) = ";
    z.printRational();
    cout << endl;

    z = x.subtract(y);
    cout << "Subtraction (x - y) = ";
    z.printRational();
    cout << endl;

    z = x.multiply(y);
    cout << "Multiplication (x * y) = ";
    z.printRational();
    cout << endl;

    z = x.divide(y);
    cout << "Division (x / y) = ";
    z.printRational();
    cout << endl;

    return 0;
}