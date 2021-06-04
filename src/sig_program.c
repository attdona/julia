#include "julia.h"

static uint8_t signal_num;

static void sigprog_handler(int sig)
{
    signal_num = sig;
}

JL_DLLEXPORT uint8_t jl_get_signal(void)
{
    return signal_num;
}

JL_DLLEXPORT void jl_register_sigprog(void)
{
    struct sigaction actint;
    memset(&actint, 0, sizeof(struct sigaction));
    sigemptyset(&actint.sa_mask);
    actint.sa_handler = sigprog_handler;
    actint.sa_flags = 0;
    if (sigaction(SIGINT, &actint, NULL) < 0) {
        jl_errorf("fatal error: sigaction: %s", strerror(errno));
    }
}