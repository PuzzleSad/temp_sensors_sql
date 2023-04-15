#include "../log.h"
#include "log_thread.h"
#include "log_priv.h"

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static int init_priv_args( log_t* log );

static void* log_thread( void* args ){
        log_t* log = (log_t*)args;
        log_private_t* lp = log->logpriv;


        while( lp->thread_active ){
                #ifndef NDEBUG
                printf("\033[92mlog thread started\033[0m\n");
                #endif
                sleep(1);
        }

        #ifndef NDEBUG
        printf("\033[92mlog thread ending...\033[0m\n");
        #endif

        return NULL;
}

int _log_threadsetup( log_t* log ){
        int status = 0;
        status = init_priv_args( log );

        if( status != EXIT_SUCCESS ){
                printerr_loc("\nargs init error\n");
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}

int _log_initthread( log_t* log ){
        int status = 0;


        status = pthread_create( 
                &log->logpriv->thread,
                NULL,
                log_thread,
                (void*)log
        );

        if( status != EXIT_SUCCESS ){
                printerr_loc("thread init error\n");
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}

int _log_endthread( log_t* log ){
        int status = 0;

        log->logpriv->thread_active = 0;

        status = pthread_join(
                log->logpriv->thread,
                NULL
        );

        if( status != EXIT_SUCCESS ){
                printerr_loc("pthread_join error\n");
                return EXIT_FAILURE;
        }

        
        return EXIT_SUCCESS;
}

int _log_finithread( log_t* log ){
        free( log->logpriv );
        return EXIT_SUCCESS;
}











static int init_priv_args( log_t* log ){
        log_private_t* lp;
        log->logpriv = (log_private_t*)calloc( 1, sizeof( log_private_t) );
        lp = log->logpriv;

        memset( lp, 0, sizeof(log_private_t) );

         

        lp->thread_active = 1;

        if( pthread_mutex_init( &lp->mtx, NULL ) != EXIT_SUCCESS ){
                printerr_loc("error mutex init\n");
                return EXIT_FAILURE;
        }

        if( pthread_cond_init( &lp->cond, NULL ) != EXIT_SUCCESS ){
                printerr_loc("error cond init\n");
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;

}