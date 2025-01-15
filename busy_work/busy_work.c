#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>


uint64_t get_cur_time_ms()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    return ((uint64_t) tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}


int main(int argc, char *argv[])
{
    uint32_t work_duration = 0;

    if (argc > 1) {
        work_duration = atoi(argv[1]);
    }

    if (work_duration == 0) {
        work_duration = 5;
        printf("Defaulting busy-work duration to %ds\n", work_duration);
    }
    else {
        printf("Using busy-work duration %ds\n", work_duration);
    }


    uint64_t start_ms = get_cur_time_ms();

    while ((get_cur_time_ms() - start_ms)  <  (work_duration * 1000))
    {
        // nothing to do
    }

    printf("Done\n");
    return 0;
}
