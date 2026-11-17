#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setfill;
using std::setw;

class Time {
public:
    Time(int hour = 0, int minute = 0, int second = 0);

    bool setTime(int hour, int minute, int second);
    bool setHour(int hour);
    bool setMinute(int minute);
    bool setSecond(int second);

    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    void printUniversal() const;
    void printStandard() const;

private:
    int hour;
    int minute;
    int second;
};

Time::Time(int h, int m, int s) {
    setTime(h, m, s);
}

bool Time::setTime(int h, int m, int s) {
    bool hValid = setHour(h);
    bool mValid = setMinute(m);
    bool sValid = setSecond(s);

    return (hValid && mValid && sValid);
}

bool Time::setHour(int h) {
    if (h >= 0 && h < 24) {
        hour = h;
        return true;
    }
    hour = 0;
    return false;
}

bool Time::setMinute(int m) {
    if (m >= 0 && m < 60) {
        minute = m;
        return true;
    }
    minute = 0;
    return false;
}

bool Time::setSecond(int s) {
    if (s >= 0 && s < 60) {
        second = s;
        return true;
    }
    second = 0;
    return false;
}

int Time::getHour() const { return hour; }
int Time::getMinute() const { return minute; }
int Time::getSecond() const { return second; }

void Time::printUniversal() const {
    cout << setfill('0') << setw(2) << hour << ":"
         << setw(2) << minute << ":"
         << setw(2) << second;
}

void Time::printStandard() const {
    cout << ((hour == 0 || hour == 12) ? 12 : hour % 12) << ":"
         << setfill('0') << setw(2) << minute << ":"
         << setw(2) << second
         << (hour < 12 ? " AM" : " PM");
}

int main() {
    Time t;

    cout << "Initial time: ";
    t.printUniversal();
    cout << endl << endl;

    cout << "Attempting to set valid time (13, 27, 45):" << endl;
    if (t.setTime(13, 27, 45)) {
        cout << "Success! Time set to: ";
        t.printUniversal();
        cout << endl;
    } else {
        cout << "Error setting time!" << endl;
    }
    cout << endl;

    cout << "Attempting to set invalid hour (25, 30, 30):" << endl;
    if (t.setTime(25, 30, 30)) {
        cout << "Success!" << endl;
    } else {
        cout << "Error: Invalid hour detected! Set failed." << endl;
    }
    cout << endl;

    cout << "Attempting to set invalid minute via setMinute(75):" << endl;
    if (t.setMinute(75)) {
        cout << "Success!" << endl;
    } else {
        cout << "Error: Invalid minute detected (75)! Set failed." << endl;
    }
    cout << endl;

    cout << "Attempting to set invalid second via setSecond(-5):" << endl;
    if (t.setSecond(-5)) {
        cout << "Success!" << endl;
    } else {
        cout << "Error: Invalid second detected (-5)! Set failed." << endl;
    }

    return 0;
}