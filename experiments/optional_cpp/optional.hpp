#include "compile_assert.h"

template <typename T>
class Optional
{
private:
    T* m_ptr;

public:
    constexpr Optional() noexcept
        : m_ptr(nullptr)
    {
    }

    constexpr Optional(T* ptr) noexcept
        : m_ptr(ptr)
    {
    }

    [[nodiscard]]
    constexpr explicit operator bool() const noexcept
    {
        return m_ptr != nullptr;
    }

    constexpr T& operator*() const
    {
        // Prevents dereferencing nullptr
        compile_assert(m_ptr != nullptr, "Error cannot return);
        return *m_ptr;
    }

    constexpr T* operator->() const
    {
        compile_assert(m_ptr != nullptr);
        return m_ptr;
    }
};
