#include <iostream>
#include <iomanip>

class SavingsAccount {
public:
    SavingsAccount(double balance);

    void calculateMonthlyInterest();

    double getSavingsBalance() const;

    static void modifyInterestRate(double newRate);

private:
    double savingsBalance;
    static double annualInterestRate;
};

double SavingsAccount::annualInterestRate = 0.0;

SavingsAccount::SavingsAccount(double balance) {
    savingsBalance = (balance >= 0.0 ? balance : 0.0);
}

void SavingsAccount::calculateMonthlyInterest() {
    double monthlyInterest = (savingsBalance * annualInterestRate) / 12.0;
    savingsBalance += monthlyInterest;
}

double SavingsAccount::getSavingsBalance() const {
    return savingsBalance;
}

void SavingsAccount::modifyInterestRate(double newRate) {
    annualInterestRate = (newRate >= 0.0 ? newRate : 0.0);
}

int main() {
    SavingsAccount saver1(2000.00);
    SavingsAccount saver2(3000.00);

    SavingsAccount::modifyInterestRate(0.03);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Initial Balances:\n";
    std::cout << "Saver 1: $" << saver1.getSavingsBalance() << "\n";
    std::cout << "Saver 2: $" << saver2.getSavingsBalance() << "\n\n";

    saver1.calculateMonthlyInterest();
    saver2.calculateMonthlyInterest();

    std::cout << "Balances after 1 month at 3% interest:\n";
    std::cout << "Saver 1: $" << saver1.getSavingsBalance() << "\n";
    std::cout << "Saver 2: $" << saver2.getSavingsBalance() << "\n\n";


    SavingsAccount::modifyInterestRate(0.04);

    saver1.calculateMonthlyInterest();
    saver2.calculateMonthlyInterest();

    std::cout << "Balances after 1 more month at 4% interest:\n";
    std::cout << "Saver 1: $" << saver1.getSavingsBalance() << "\n";
    std::cout << "Saver 2: $" << saver2.getSavingsBalance() << "\n";

    return 0;
}