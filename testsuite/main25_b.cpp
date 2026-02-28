// g++ -I.. -D__ENABLE_COMPILE_ASSERT__ -Wall -O3 -o main25_a_2.bin main25_a_2.cpp

// Compile with a C++26-capable compiler that supports Contracts.

#include <iostream>
#include <stdexcept>
#include <string>

#include "compile_assert.h"

#define pre(expr) compile_assert(expr, "")
#define contract_assert(expr) compile_assert(expr, "")
#define post(expr) compile_assert(expr, "")


static int divide(int a, int b)
{
    pre(b != 0); // Precondition (C++26 contract)

    contract_assert(a >= 0);    // contract assertion

    const int result = a/b;
    post(result*b == a); // Postcondition on return code

    return result;
}


class BankAccount {
public:
    explicit BankAccount(double initial_balance)
        : balance_(initial_balance)
    {
        contract_assert(initial_balance >= 0.0);
    }

    void deposit(double amount)
    {
        pre(amount > 0.0);

        balance_ += amount;
    }

    void withdraw(double amount)
    {
        pre(amount > 0.0);
        pre(amount <= balance_);

        contract_assert(balance_ >= 0.0);

        balance_ -= amount;
    }

    double balance() const
    {
        post(balance_ >= 0.0);
        return balance_;
    }

private:
    double balance_;
};


int main()
{
    try {
        std::cout << "10 / 2 = " << divide(10, 2) << "\n";

        BankAccount account(100.0);
        account.deposit(50.0);
        account.withdraw(25.0);

        std::cout << "Balance: " << account.balance() << "\n";

        // Uncommenting either of these should trigger a contract violation:
        // divide(10, 0);
        // account.withdraw(1000.0);

    } catch (...) {
        std::cerr << "Contract violation detected.\n";
    }

    return 0;
}
