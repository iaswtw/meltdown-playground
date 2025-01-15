#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>

static inline void maccess(void *p) {
  asm volatile("movq (%0), %%rax\n" : : "c"(p) : "rax");
}

static void flush(void *p) {
  asm volatile("clflush 0(%0)\n" : : "c"(p) : "rax");
}

static inline uint64_t rdtsc() {
  uint64_t a = 0, d = 0;
  asm volatile("mfence");
  asm volatile("rdtscp" : "=a"(a), "=d"(d));
  a = (d << 32) | a;
  asm volatile("mfence");
  return a;
}

static void detect_flush_reload_threshold(size_t * pReloadTime, size_t * pFlushReloadTime, size_t * pCacheMissThreshold) {
  size_t reload_time = 0, flush_reload_time = 0, i, count = 1000000;
  size_t dummy[16];
  size_t *ptr = dummy + 8;
  uint64_t start = 0, end = 0;

  maccess(ptr);
  for (i = 0; i < count; i++) {
    start = rdtsc();
    maccess(ptr);
    end = rdtsc();
    reload_time += (end - start);
  }
  for (i = 0; i < count; i++) {
    start = rdtsc();
    maccess(ptr);
    end = rdtsc();
    flush(ptr);
    flush_reload_time += (end - start);
  }
  reload_time /= count;
  flush_reload_time /= count;
  size_t cache_miss_threshold = (flush_reload_time + reload_time * 2) / 3;

  if (pReloadTime) {
      *pReloadTime = reload_time;
  }
  if (pFlushReloadTime) {
      *pFlushReloadTime = flush_reload_time;
  }
  if (pCacheMissThreshold) {
      *pCacheMissThreshold = cache_miss_threshold;
  }
}


int main(int argc, char *argv[])
{
    size_t reload_time = 0;
    size_t flush_reload_time = 0;
    size_t cache_miss_threshold = 0;

    detect_flush_reload_threshold(&reload_time, &flush_reload_time, &cache_miss_threshold);


    printf("Flush+Reload cycles    = %zd\n", flush_reload_time);
    printf("Reload only            = %zd\n", reload_time);
    printf("Flush+Reload threshold = %zd\n", cache_miss_threshold);

    return 0;
}
