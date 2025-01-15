#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    uint32_t * address = (uint32_t*) 0xFFFF800000;

    printf("Accessing memory location at address %p\n", address);

    uint32_t value = *address;          // this will cause segfault

    printf("value = %u\n", value);      // this will never be printed

    return 0;
}
