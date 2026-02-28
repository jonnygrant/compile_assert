// g++ -I.. -D__ENABLE_COMPILE_ASSERT__ -Wall -O3 -o main25_a_2.bin main25_a_2.cpp

// Example of compile-time C++26 Contracts.
// Nothing checked at runtime.

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


class bank_account {
public:
    explicit bank_account(double initial_balance)
        : m_balance(initial_balance)
    {
        contract_assert(initial_balance >= 0.0);
    }

    void deposit(double amount)
    {
        pre(amount > 0.0);

        m_balance += amount;
    }

    void withdraw(double amount)
    {
        pre(amount > 0.0);
        pre(amount <= m_balance);

        contract_assert(m_balance >= 0.0);

        m_balance -= amount;
    }

    double balance() const
    {
        post(m_balance >= 0.0);
        return m_balance;
    }

private:
    double m_balance;
};


int main()
{
    std::cout << "10 / 2 = " << divide(10, 2) << "\n";

    bank_account acc(100.0);
    acc.deposit(50.0);
    acc.withdraw(25.0);

    std::cout << "Balance: " << acc.balance() << "\n";

    // Uncommenting either of these should trigger a contract violation:
    divide(10, 0);
    acc.withdraw(1000.0);

    return 0;
}
