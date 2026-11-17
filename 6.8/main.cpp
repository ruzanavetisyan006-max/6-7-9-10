#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setfill;
using std::setw;

class Time {
public:
    Time(int hour = 0, int minute = 0, int second = 0);

    void setTime(int hour, int minute, int second);
    void tick();
    void printStandard() const;

private:
    int hour;
    int minute;
    int second;
};

Time::Time(int h, int m, int s) {
    setTime(h, m, s);
}

void Time::setTime(int h, int m, int s) {
    hour = (h >= 0 && h < 24) ? h : 0;
    minute = (m >= 0 && m < 60) ? m : 0;
    second = (s >= 0 && s < 60) ? s : 0;
}

void Time::tick() {
    second++;

    if (second >= 60) {
        second = 0;
        minute++;

        if (minute >= 60) {
            minute = 0;
            hour++;

            if (hour >= 24) {
                hour = 0;
            }
        }
    }
}

void Time::printStandard() const {
    cout << ((hour == 0 || hour == 12) ? 12 : hour % 12) << ":"
         << setfill('0') << setw(2) << minute << ":"
         << setw(2) << second
         << (hour < 12 ? " AM" : " PM");
}

int main() {
  
    Time t(23, 59, 58); 

    cout << "Testing tick() function through critical time transitions:" << endl;

    for (int i = 0; i < 5; i++) {
        cout << "Before tick: ";
        t.printStandard();
        
        t.tick();
        
        cout << " | After tick:  ";
        t.printStandard();
        cout << endl;
    }

    return 0;
}