#include <iostream>
#include <iomanip>
#include <cmath>

using std::cout;
using std::endl;
using std::setfill;
using std::setw;

class DateAndTime {
public:
    DateAndTime(int m = 1, int d = 1, int y = 2000, int h = 0, int min = 0, int s = 0);

    void setDateTime(int m, int d, int y, int h, int min, int s);
    void tick();

    void printUniversal() const;
    void printStandard() const;

private:
    int month;
    int day;
    int year;

    int hour;
    int minute;
    int second;

    bool leapYear(int y) const;
    int daysInMonth(int m) const;
    void nextDay();
};

DateAndTime::DateAndTime(int m, int d, int y, int h, int min, int s) {
    setDateTime(m, d, y, h, min, s);
}

void DateAndTime::setDateTime(int m, int d, int y, int h, int min, int s) {
    year = (y >= 1 && y <= 9999) ? y : 2000;
    month = (m >= 1 && m <= 12) ? m : 1;
    day = (d >= 1 && d <= daysInMonth(month)) ? d : 1;

    hour = (h >= 0 && h < 24) ? h : 0;
    minute = (min >= 0 && min < 60) ? min : 0;
    second = (s >= 0 && s < 60) ? s : 0;
}

bool DateAndTime::leapYear(int y) const {
    if (y % 400 == 0) {
        return true;
    } else if (y % 100 == 0) {
        return false;
    } else if (y % 4 == 0) {
        return true;
    }
    return false;
}

int DateAndTime::daysInMonth(int m) const {
    const int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && leapYear(year)) {
        return 29;
    }
    return days[m];
}

void DateAndTime::nextDay() {
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

void DateAndTime::tick() {
    second++;

    if (second >= 60) {
        second = 0;
        minute++;

        if (minute >= 60) {
            minute = 0;
            hour++;

            if (hour >= 24) {
                hour = 0;
                nextDay();
            }
        }
    }
}

void DateAndTime::printUniversal() const {
    cout << setfill('0') 
         << setw(2) << month << '/' 
         << setw(2) << day << '/' 
         << year << " "
         << setw(2) << hour << ":"
         << setw(2) << minute << ":"
         << setw(2) << second;
}

void DateAndTime::printStandard() const {
    cout << month << '/' << day << '/' << year << " "
         << ((hour == 0 || hour == 12) ? 12 : hour % 12) << ":"
         << setfill('0') << setw(2) << minute << ":"
         << setw(2) << second
         << (hour < 12 ? " AM" : " PM");
}

int main() {

    DateAndTime dt(12, 31, 2026, 23, 59, 58);


    for (int i = 0; i < 5; i++) {
        cout << "Standard: ";
        dt.printStandard();
        cout << " | Universal: ";
        dt.printUniversal();
        cout << endl;

        dt.tick();
    }

    return 0;
}