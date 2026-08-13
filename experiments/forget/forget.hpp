#include "compile_assert.h"
#include "compile_assert.h"

template <typename T>
class Forget
{
private:
    T m_value;
    mutable bool m_value_owned;

public:
    constexpr Forget() noexcept
        : m_value{},
          m_value_owned(false)
    {
    }

    constexpr Forget(T value) noexcept
        : m_value(value),
          m_value_owned(true)
    {
    }

    constexpr operator T() const
    {
        compile_assert(m_value_owned,
                    "Forget: cannot access a forgotten value");
        return m_value;
    }

    constexpr Forget(const Forget& other) noexcept
        : m_value(other.m_value),
          m_value_owned(true)
    {
        compile_assert(other.m_value_owned,
                       "Forget: cannot copy from a forgotten value");

        other.m_value_owned = false;
    }

    [[nodiscard]]
    constexpr explicit operator bool() const noexcept
    {
        return m_value_owned;
    }
};
