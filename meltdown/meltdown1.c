#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>

static jmp_buf buf;     // save execution context at the point where setjmp() is called

static void unblock_signal(int signum)
{
    sigset_t sigs;

    sigemptyset(&sigs);                         // clear all signals in `sigs`
    sigaddset(&sigs, signum);                   // set `signum` in `sigs`
    sigprocmask(SIG_UNBLOCK, &sigs, NULL);      // unblock/clear given signal
}

static void segfault_handler(int signum)
{
    (void) signum;
    // signal mask is set when the signal is raised.
    // Without unblocking the signal (resetting the mask), further signals will terminate the app
    unblock_signal(SIGSEGV);

    // continue execution at the saved execution context location.
    // setjmp() will return with the given value (1).
    longjmp(buf, 1);
}

int main(int argc, char **argv)
{
    if (signal(SIGSEGV, segfault_handler) == SIG_ERR) {
        printf("Error setting up SEGV handler\n");
        exit(1);
    }

    // pointer to region we don't have access to
    uint32_t * address = (uint32_t *) 0xFFFF8800000;

    // ----------- First attempt ------------
    uint32_t value = 100;
    if (setjmp(buf) == 0) {
        value = *address;

//        asm volatile("1:\n"                                                          \
//                     "movzx (%%ecx), %%eax\n"                                         \
//                     "shl $12, %%eax\n"                                              \
//                     "jz 1b\n"                                                       \
//                     "mov (%%ebx,%%eax,1), %%ebx\n"                                  \
//                     :                                                               \
//                     : "c"(phys), "b"(mem)                                           \
//                     : "eax");

    }
    printf("Value (1st attempt) = %u\n", value);

    // ----------- Second attempt ------------
    if (setjmp(buf) == 0) {
        value = *address;
    }
    printf("Value (2nd attempt) = %u\n", value);


    // Restore default handling of signal
    signal(SIGSEGV, SIG_DFL);
}
