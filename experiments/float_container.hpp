#ifndef FLOAT_CONTAINER_HPP
#define FLOAT_CONTAINER_HPP

#include "compile_assert.h"

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

    float_container(float_container& other)
        : m_valid(false), m_value(nullptr)
    {
        if (this != &other)
        {
            m_value = other.m_value;
            m_valid = true;
            other.m_value = nullptr;
            other.m_valid = false;
        }
    }

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

#endif
