// gcc -O2 -Wall -o main6 main6.c

// demonstrate compile_assert checking an image file is valid
// the header is 18 bytes, and 4 pixels are another 16 bytes

#include "compile_assert.h"
#include <stdio.h>

#include <stdint.h>


// Note: buffer must be const
// 18+16 bytes
const uint8_t tga_file[] = {
    0x00,       // ID length
    0x00,       // Color map type
    0x02,       // Image type (truecolor)
    0x00, 0x00, // Color map specification (offset)
    0x00, 0x00, // Color map specification (length)
    0x00,       // Color map depth
    0x00, 0x00, // X-origin
    0x00, 0x00, // Y-origin
    0x02, 0x00, // Image width (2 pixels)
    0x02, 0x00, // Image height (2 pixels)
    0x20,       // Pixel depth (32 bits per pixel: 8 bits for B, 8 bits for G, 8 bits for R, 8 bits for A)
    0x00,        // Image descriptor
    0x00, 0xFF, 0xFF, 0x00, // 32bit pixel
    0x00, 0xFF, 0xFF, 0x00, // 32bit pixel
    0x00, 0xFF, 0xFF, 0x00, // 32bit pixel
    0x00, 0xFF, 0xFF, 0x00, // 32bit pixel
    0x11 // this is a bug, not meant to be here, just for the compile_assert
};

int main()
{
    compile_assert(tga_file[2] == 0x01, "Must be truecolor"); // will fire, as must be 0x02
    compile_assert(sizeof(tga_file) == (16+18), "must be the right size"); // will fire as must remove extra byte

    printf("%d\n", tga_file[0]);

    return 0;
}
