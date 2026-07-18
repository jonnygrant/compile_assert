#ifndef FLOAT_CONTAINER_H
#define FLOAT_CONTAINER_H

#include <stdlib.h>

#include "compile_assert.h"

typedef struct
{
    float * ptr;
} float_container;

inline void float_container_init(float_container * container);
inline void float_container_destroy(float_container * container);

inline void float_container_set(float_container * container, float value);
inline const float float_container_get(const float_container * container);

inline void float_container_ownership(float_container * dst,
                          float_container * src);


inline void float_container_init(float_container * container)
{
    container->ptr = nullptr;
}

inline void float_container_destroy(float_container * container)
{
    free(container->ptr);
    container->ptr = nullptr;
}

inline void float_container_set(float_container * container, float value)
{
    container->ptr = malloc(sizeof(float));

    *container->ptr = value;
}

inline const float float_container_get(const float_container * container)
{
    //compile_assert(container->ptr != nullptr, "error");

    float a = *container->ptr;
    return a;
}


inline void float_container_ownership(float_container * dst,
                          float_container * src)
{
    if (dst == src)
    {
        return;
    }

    free(dst->ptr);

    dst->ptr = src->ptr;
    src->ptr = nullptr;
}

#endif
