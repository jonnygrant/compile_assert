//g++ -I.. -D__ENABLE_COMPILE_ASSERT__ -std=c++23 -Wall -O2 -o ownership ownership.cpp

#include "compile_assert.h"

// Demonstrate assigning ownership of an object, upon which it can no longer be used by
// the original object


class float_container
{
public:
    float_container()
        : m_valid(false), m_value(nullptr)
    {
    }

    ~float_container()
    {
        if(m_valid)
        {
            delete m_value;
        }
    }

    float_container(const float_container&) = delete;
    float_container& operator=(const float_container&) = delete;

    float_container(float_container&& other) noexcept
        : m_value(other.m_value)
    {
        other.m_value = nullptr;
        other.m_valid = false;
    }

    // Steal on assignment.
    float_container& operator=(float_container& other)
    {
        if (this != &other)
        {
            delete m_value;

            m_value = other.m_value;
            m_valid = true;
            other.m_value = nullptr;
            other.m_valid = false;
        }

        return *this;
    }

    // Allocate a new float.
    void set(float value)
    {
        if (!m_value)
            m_value = new float;

        *m_value = value;
        m_valid = true;
    }

    const float* operator->() const
    {
        compile_assert(m_valid, "error get m_valid");
        return m_value;
    }

    const float* get() const
    {
        compile_assert(m_valid, "error get m_valid");
        return m_value;
    }

private:
    bool m_valid;
    float* m_value;
};


int main()
{
    float_container value;

    // Allocate internally.
    value.set(3.14f);
    __builtin_printf("%6.2f\n", *value.get());

    // Take ownership of an existing allocation.
    float_container value2;
    value2 = value;

    // fail to compile
    // comment out, and see warning disapears
    __builtin_printf("%6.2f\n", *value.get());
}
