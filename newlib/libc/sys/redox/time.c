#include "common.h"

int _clock_gettime(clockid_t clk_id, struct timespec * tp){
    return syscall2(SYS_CLOCK_GETTIME, (uint64_t)clk_id, (uint64_t)tp);
}

int _gettimeofday(struct timeval *__restrict tv, void *__restrict tz){
    if(tv){
        struct timespec tp;
        if(_clock_gettime(CLOCK_REALTIME, &tp) == 0){
            tv->tv_sec = tp.tv_sec;
            tv->tv_usec = tp.tv_nsec / 1000;
        } else {
            return -1;
        }
    } else {
        errno = EFAULT;
        return -1;
    }
}

int _nanosleep(const struct timespec * req, struct timespec * rem){
    return syscall2(SYS_NANOSLEEP, (uint64_t)req, (uint64_t)rem);
}
