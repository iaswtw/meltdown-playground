#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <sys/time.h>

static inline uint64_t rdtsc() {
  uint64_t a = 0, d = 0;
  asm volatile("mfence");
  asm volatile("rdtscp" : "=a"(a), "=d"(d));
  a = (d << 32) | a;
  asm volatile("mfence");
  return a;
}

uint64_t get_cur_time_ms()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    return ((uint64_t) tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}


int main(int argc, char *argv[])
{
//#ifdef __x86_64__
//    printf("hello\n");
//#else
//    printf("world\n");
//#endif

    double accum_duration_s = 0.0f;

    if (argc > 1) {
        accum_duration_s = atof(argv[1]);
    }
    if (accum_duration_s == 0.0f) {
        accum_duration_s = 5.0f;
        printf("Defaulting accumulation duration of %lfs\n", accum_duration_s);
    }
    else {
        printf("Using accumulation duration %lfs\n", accum_duration_s);
    }

    setlocale(LC_NUMERIC, "");

    uint64_t s = rdtsc();
    printf("%'ld\n", s);
    uint64_t start_ms = get_cur_time_ms();

    // busy wait 1s
    while ((get_cur_time_ms() - start_ms) < (accum_duration_s * 1000)) {
        // nothing to do
    }

    uint64_t e = rdtsc();
    printf("%'ld\n", e);
    printf("Elapsed: %'ld\n", e - s);

    return 0;
}
