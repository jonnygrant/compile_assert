// g++ -I.. -D__ENABLE_COMPILE_ASSERT__ -std=c++23 -O2 -Wall -o contracts_percentage contracts_percentage.cpp

#include <iostream>
#include <format>

#include "compile_assert.h"

#define pre compile_assert
#define contract_assert compile_assert
#define post compile_assert


/* Demonstrate C++ style Contracts using compile_assert */
class Number
{
public:
    explicit Number(double value)
    {
        pre(value >= 0.0, "pre: initial value must be non-negative");

        m_value = value;
    }

    void increase_by(double percentage)
    {
        pre_percentage(percentage);

        m_value *= (1.0 + percentage / 100.0);

        post_value();
    }

    void decrease_by(double percentage)
    {
        pre_percentage(percentage);

        m_value *= (1.0 - percentage / 100.0);

        post_value();
    }

    double value() const { return m_value; }

private:
    double m_value;

    void pre_percentage(double percentage) const
    {
        compile_assert(percentage >= 0.0,
                       "percentage must be >= 0");

        compile_assert(percentage <= 100.0,
                       "percentage must be <= 100");
    }

    void post_value() const
    {
        compile_assert(m_value >= 0.0,
                       "value must remain non-negative");
    }
};

int main()
{
    Number n(50.0);

    double increase = 100.0;

    n.increase_by(increase);
    std::cout << std::format("Increase was: {}, new value: {}\n", increase, n.value());

    n.decrease_by(20.0);
    std::cout << std::format("Decrease was: {}, new value: {}\n", increase, n.value());

    n.decrease_by(80.0);
    std::cout << std::format("Decrease was: {}, new value: {:.2f}\n", increase, n.value());

    return 0;
}
