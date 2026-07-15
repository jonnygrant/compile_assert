#ifndef FLOAT_CONTAINER_HPP
#define FLOAT_CONTAINER_HPP

#include "compile_assert.h"

class float_container
{
public:
    float_container()
        : m_value_ptr(nullptr)
    {
    }

    ~float_container()
    {
        delete m_value_ptr;
    }

    float_container(float_container& other)
        : m_value_ptr(nullptr)
    {
        if (this != &other)
        {
            __builtin_printf("(float_container& other) taking ownership of m_value_ptr\n");

            m_value_ptr = other.m_value_ptr;
            other.m_value_ptr = nullptr;
        }
    }

    float_container(const float_container&) = delete;
    float_container& operator=(const float_container&) = delete;

    float_container(float_container&& other) noexcept
        :  m_value_ptr(other.m_value_ptr)
    {
        __builtin_printf("float_container(float_container&& other) taking ownership of m_value_ptr\n");
        other.m_value_ptr = nullptr;
    }

    // Take ownership
    float_container& operator=(float_container&& other)
    {
        if (this != &other)
        {
            delete m_value_ptr;

            m_value_ptr = other.m_value_ptr;
            other.m_value_ptr = nullptr;
        }

        return *this;
    }

    // Allocate a new float.
    void set(float value)
    {
        if (!m_value_ptr)
        {
            m_value_ptr = new float;
        }

        *m_value_ptr = value;
    }

    const float* get() const
    {
        compile_assert(m_value_ptr, "error const float* get() const get m_value_ptr nullptr");
        return m_value_ptr;
    }

private:
    float* m_value_ptr;
};

#endif
