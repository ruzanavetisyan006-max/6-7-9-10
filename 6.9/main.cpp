#include <iostream>

using std::cout;
using std::endl;

class Date {
public:
    Date(int m = 1, int d = 1, int y = 2000);

    void setDate(int m, int d, int y);
    void nextDay();
    void print() const;

private:
    int month;
    int day;
    int year;

    bool leapYear(int y) const;
    int daysInMonth(int m) const;
};

Date::Date(int m, int d, int y) {
    setDate(m, d, y);
}

void Date::setDate(int m, int d, int y) {
    year = (y >= 1 && y <= 9999) ? y : 2000;
    month = (m >= 1 && m <= 12) ? m : 1;
    
    if (d >= 1 && d <= daysInMonth(month)) {
        day = d;
    } else {
        day = 1;
        cout << "Error: Invalid day for the given month! Reset to 1." << endl;
    }
}

bool Date::leapYear(int y) const {
    if (y % 400 == 0) {
        return true;
    } else if (y % 100 == 0) {
        return false;
    } else if (y % 4 == 0) {
        return true;
    }
    return false;
}

int Date::daysInMonth(int m) const {
    const int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (m == 2 && leapYear(year)) {
        return 29;
    }
    return days[m];
}

void Date::nextDay() {
    if (day < daysInMonth(month)) {
        day++;
    } else {
        day = 1;
        if (month < 12) {
            month++;
        } else {
            month = 1;
            year++;
        }
    }
}

void Date::print() const {
    cout << month << '/' << day << '/' << year;
}

int main() {

    
    Date d1(2, 27, 2026);

    for (int i = 0; i < 5; i++) {
        cout << "Current date: ";
        d1.print();
        d1.nextDay();
        cout << " | After nextDay(): ";
        d1.print();
        cout << endl;
    }

    Date d2(12, 30, 2026);

    for (int i = 0; i < 4; i++) {
        cout << "Current date: ";
        d2.print();
        d2.nextDay();
        cout << " | After nextDay(): ";
        d2.print();
        cout << endl;
    }

    return 0;
}