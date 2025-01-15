#include <stdio.h>
#include <cpuid.h>

static int check_tsx()
{
    if (__get_cpuid_max(0, NULL) >= 7) {
        unsigned a, b, c, d;
        __cpuid_count(7, 0, a, b, c, d);
        return (b & (1 << 11)) ? 1 : 0;
    }
    else {
        return 0;
    }
}


int main(int argc, char *argv[])
{
    int has_tsx = check_tsx();
    if (has_tsx) {
        printf("Processor has TSX extensions\n");
    } else {
        printf("No TSX extensions :-(\n");
    }

    return 0;
}
