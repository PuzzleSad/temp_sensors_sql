#ifndef LOG_PRIV_H_
#define LOG_PRIV_H_

#include "../log.h"
#include <pthread.h>

struct log_private_t{

        int thread_active;

        pthread_t thread;
        pthread_mutex_t mtx;
        pthread_cond_t cond;
};


#endif