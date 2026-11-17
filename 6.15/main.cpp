#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::cin;

class HugeInteger {
public:
    HugeInteger();
    HugeInteger(long long value);
    HugeInteger(const string &val);

    void input(const string &val);
    void output() const;

    HugeInteger add(const HugeInteger &right) const;
    HugeInteger subtract(const HugeInteger &right) const;

    bool isEqualTo(const HugeInteger &right) const;
    bool isNotEqualTo(const HugeInteger &right) const;
    bool isGreaterThan(const HugeInteger &right) const;
    bool isLessThan(const HugeInteger &right) const;
    bool isGreaterThanOrEqualTo(const HugeInteger &right) const;
    bool isLessThanOrEqualTo(const HugeInteger &right) const;
    bool isZero() const;

private:
    int digits[40];
};

HugeInteger::HugeInteger() {
    for (int i = 0; i < 40; i++) {
        digits[i] = 0;
    }
}

HugeInteger::HugeInteger(long long value) {
    for (int i = 0; i < 40; i++) {
        digits[i] = 0;
    }

    int index = 39;
    while (value > 0 && index >= 0) {
        digits[index] = value % 10;
        value /= 10;
        index--;
    }
}

HugeInteger::HugeInteger(const string &val) {
    input(val);
}

void HugeInteger::input(const string &val) {
    for (int i = 0; i < 40; i++) {
        digits[i] = 0;
    }

    int length = val.length();
    int startIndex = (length < 40) ? (40 - length) : 0;
    int stringIndex = (length < 40) ? 0 : (length - 40);

    for (int i = startIndex; i < 40 && stringIndex < length; i++, stringIndex++) {
        if (val[stringIndex] >= '0' && val[stringIndex] <= '9') {
            digits[i] = val[stringIndex] - '0';
        }
    }
}

void HugeInteger::output() const {
    int i = 0;
    while (i < 40 && digits[i] == 0) {
        i++;
    }

    if (i == 40) {
        cout << 0;
    } else {
        for (; i < 40; i++) {
            cout << digits[i];
        }
    }
}

HugeInteger HugeInteger::add(const HugeInteger &right) const {
    HugeInteger temp;
    int carry = 0;

    for (int i = 39; i >= 0; i--) {
        int sum = digits[i] + right.digits[i] + carry;
        temp.digits[i] = sum % 10;
        carry = sum / 10;
    }

    return temp;
}

HugeInteger HugeInteger::subtract(const HugeInteger &right) const {
    if (this->isLessThan(right)) {
        cout << "Error: Subtraction resulted in negative number." << endl;
        return HugeInteger(0);
    }

    HugeInteger temp;
    int borrow = 0;

    for (int i = 39; i >= 0; i--) {
        int diff = digits[i] - right.digits[i] - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        temp.digits[i] = diff;
    }

    return temp;
}

bool HugeInteger::isEqualTo(const HugeInteger &right) const {
    for (int i = 0; i < 40; i++) {
        if (digits[i] != right.digits[i]) {
            return false;
        }
    }
    return true;
}

bool HugeInteger::isNotEqualTo(const HugeInteger &right) const {
    return !isEqualTo(right);
}

bool HugeInteger::isGreaterThan(const HugeInteger &right) const {
    for (int i = 0; i < 40; i++) {
        if (digits[i] > right.digits[i]) return true;
        if (digits[i] < right.digits[i]) return false;
    }
    return false;
}

bool HugeInteger::isLessThan(const HugeInteger &right) const {
    return right.isGreaterThan(*this);
}

bool HugeInteger::isGreaterThanOrEqualTo(const HugeInteger &right) const {
    return (isGreaterThan(right) || isEqualTo(right));
}

bool HugeInteger::isLessThanOrEqualTo(const HugeInteger &right) const {
    return (isLessThan(right) || isEqualTo(right));
}

bool HugeInteger::isZero() const {
    for (int i = 0; i < 40; i++) {
        if (digits[i] != 0) return false;
    }
    return true;
}

int main() {
    HugeInteger n1;
    HugeInteger n2("9999999999999999999999999999999999999999");
    HugeInteger n3(123456789);

    cout << "n1 = ";
    n1.output();
    cout << endl;

    cout << "n2 = ";
    n2.output();
    cout << endl;

    cout << "n3 = ";
    n3.output();
    cout << endl << endl;

    n1.input("8888888888888888888888888888888888888888");
    cout << "New n1 = ";
    n1.output();
    cout << endl;

    HugeInteger sum = n1.add(n3);
    cout << "n1 + n3 = ";
    sum.output();
    cout << endl;

    cout << "Is n1 greater than n3? " << (n1.isGreaterThan(n3) ? "Yes" : "No") << endl;
    cout << "Is n3 less than n1? " << (n3.isLessThan(n1) ? "Yes" : "No") << endl;
    cout << "Is n1 zero? " << (n1.isZero() ? "Yes" : "No") << endl;

    return 0;
}