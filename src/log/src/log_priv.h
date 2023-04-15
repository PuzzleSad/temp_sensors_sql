#ifndef LOG_PRIV_H_
#define LOG_PRIV_H_

#include "../log.h"
#include <pthread.h>
#include <time.h>

#define printerr_loc(errmsg)\
do{\
        fprintf(stderr, "\033[91m"errmsg"\033[0m");\
        fprintf(stderr, "\033[95m""func: %s\n""\033[0m", __FUNCTION__);\
        fprintf(stderr, "\033[95m""file: %s\n""\033[0m", __FILE__);\
        fprintf(stderr, "\033[95m""line: %d\n""\033[0m", __LINE__);\
}while(0)

struct log_private_t{

        int thread_active;
        // int thread_sleep;
        struct timespec wait_target;

        pthread_t thread;
        pthread_mutex_t mtx;
        pthread_cond_t cond;
};


#endif