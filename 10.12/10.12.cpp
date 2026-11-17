#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    int getDay() const {
        return day;
    }

    int getMonth() const {
        return month;
    }

    int getYear() const {
        return year;
    }
};

class Employee {
private:
    string firstName;
    string lastName;
    string socialSecurityNumber;
    Date birthDate;

public:
    Employee(const string& first, const string& last, const string& ssn, const Date& bDate)
        : firstName(first), lastName(last), socialSecurityNumber(ssn), birthDate(bDate) {}

    void setFirstName(const string& first) {
        firstName = first;
    }

    string getFirstName() const {
        return firstName;
    }

    void setLastName(const string& last) {
        lastName = last;
    }

    string getLastName() const {
        return lastName;
    }

    void setSocialSecurityNumber(const string& ssn) {
        socialSecurityNumber = ssn;
    }

    string getSocialSecurityNumber() const {
        return socialSecurityNumber;
    }

    Date getBirthDate() const {
        return birthDate;
    }

    virtual double earnings() const = 0;

    virtual void print() const {
        cout << getFirstName() << " " << getLastName()
             << "\nsocial security number: " << getSocialSecurityNumber()
             << "\nbirth date: " << birthDate.getDay() << "/" << birthDate.getMonth() << "/" << birthDate.getYear();
    }

    virtual ~Employee() = default;
};

class SalariedEmployee : public Employee {
private:
    double weeklySalary;

public:
    SalariedEmployee(const string& first, const string& last, const string& ssn, const Date& bDate, double salary)
        : Employee(first, last, ssn, bDate) {
        setWeeklySalary(salary);
    }

    void setWeeklySalary(double salary) {
        weeklySalary = (salary < 0.0) ? 0.0 : salary;
    }

    double getWeeklySalary() const {
        return weeklySalary;
    }

    virtual double earnings() const override {
        return getWeeklySalary();
    }

    virtual void print() const override {
        cout << "salaried employee: ";
        Employee::print();
        cout << "\nweekly salary: " << getWeeklySalary();
    }
};

class HourlyEmployee : public Employee {
private:
    double wage;
    double hours;

public:
    HourlyEmployee(const string& first, const string& last, const string& ssn, const Date& bDate, double hourlyWage, double hoursWorked)
        : Employee(first, last, ssn, bDate) {
        setWage(hourlyWage);
        setHours(hoursWorked);
    }

    void setWage(double hourlyWage) {
        wage = (hourlyWage < 0.0) ? 0.0 : hourlyWage;
    }

    double getWage() const {
        return wage;
    }

    void setHours(double hoursWorked) {
        hours = ((hoursWorked >= 0.0 && hoursWorked <= 168.0) ? hoursWorked : 0.0);
    }

    double getHours() const {
        return hours;
    }

    virtual double earnings() const override {
        if (getHours() <= 40.0) {
            return getWage() * getHours();
        }
        else {
            return 40 * getWage() + (getHours() - 40) * getWage() * 1.5;
        }
    }

    virtual void print() const override {
        cout << "hourly employee: ";
        Employee::print();
        cout << "\nhourly wage: " << getWage() << "; hours worked: " << getHours();
    }
};

int main() {
    vector<Employee*> employees;

    employees.push_back(new SalariedEmployee("John", "Smith", "111-11-1111", Date(15, 5, 1985), 800.0));
    employees.push_back(new HourlyEmployee("Karen", "Price", "222-22-2222", Date(20, 5, 1990), 16.75, 40.0));
    employees.push_back(new SalariedEmployee("Sue", "Jones", "333-33-3333", Date(10, 11, 1988), 1200.0));

    int currentMonth = 5;

    cout << fixed << setprecision(2);
    cout << "Employee payroll processing for month: " << currentMonth << "\n\n";

    for (const auto* employeePtr : employees) {
        employeePtr->print();
        
        double payment = employeePtr->earnings();
        
        if (employeePtr->getBirthDate().getMonth() == currentMonth) {
            payment += 100.0;
            cout << "\nBirthday Bonus: $100.00 added";
        }

        cout << "\nearned: $" << payment << "\n\n";
    }

    for (auto* employeePtr : employees) {
        delete employeePtr;
    }

    return 0;
}