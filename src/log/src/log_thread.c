#include "../log.h"
#include "log_thread.h"
#include "log_priv.h"
#include "log_fileio.h"

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

const char* log_init_preamble_str = "log start: ";


static int init_priv_args( log_t* log );
static int write_init_log( log_t* log, const char* init_preamble);
static int write_fini_log( log_t* log );

static int setup_timed_wait( log_t* log, int wait_time_sec );

static void* log_thread( void* args ){
        log_t* log = (log_t*)args;
        log_private_t* lp = log->logpriv;

        write_init_log( log , log_init_preamble_str);

        while( lp->thread_active ){
                pthread_mutex_lock( &lp->mtx);

                // if( lp->thread_sleep ){
                        setup_timed_wait( log, 0 );
                        pthread_cond_timedwait( &lp->cond, &lp->mtx, &lp->wait_target );
                // }
                



                pthread_mutex_unlock( &lp->mtx );
                sleep(1);
        }

        #ifndef NDEBUG
        printf("\033[92mlog thread ending...\033[0m\n");
        #endif

        write_fini_log( log );

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

static int write_init_log( log_t* log, const char* init_preamble){
        #define MSG_MAX_LEN 1000

        time_t now;
        time( &now );
        char* date_str = ctime( &now );
        
        int msg_len = 0;
        msg_len += strlen( date_str );
        msg_len += strlen( init_preamble );
        msg_len += 5;   //thumbsuck number, account for additional spaces and whatnot

        if( msg_len > MSG_MAX_LEN ){
                printerr_loc("Error, malformed message, larger than MSG_MAX_LEN");
                return EXIT_FAILURE;
        }


        char msg_str[MSG_MAX_LEN];
        memset( msg_str, 0, MSG_MAX_LEN);

        sprintf(msg_str, "%s%s", init_preamble, date_str);

        

        // printf("write_init msg:\n%s\n", msg_str);
        write_log( log, "---------------------------\n");
        write_log( log, msg_str);

        return EXIT_SUCCESS;

        #undef MSG_MAX_LEN
}

static int write_fini_log( log_t* log ){
        #define MSG_MAX_LEN 1000

        time_t now;
        time( &now );
        char* date_str = ctime( &now );
        
        int msg_len = 0;
        msg_len += strlen( date_str );
        msg_len += 5;   //thumbsuck number, account for additional spaces and whatnot

        if( msg_len > MSG_MAX_LEN ){
                printerr_loc("Error, malformed message, larger than MSG_MAX_LEN");
                return EXIT_FAILURE;
        }


        char msg_str[MSG_MAX_LEN];
        memset( msg_str, 0, MSG_MAX_LEN);

        sprintf(msg_str, "log end:   %s", date_str);
        

        

        // printf("write_init msg:\n%s\n", msg_str);
        write_log( log, msg_str);
        write_log( log, "---------------------------\n");

        return EXIT_SUCCESS;

        #undef MSG_MAX_LEN
}




static int setup_timed_wait( log_t* log, int wait_time_sec ){
        time( &log->logpriv->wait_target.tv_sec );
        log->logpriv->wait_target.tv_nsec = 0;

        log->logpriv->wait_target.tv_sec += wait_time_sec;

        return EXIT_SUCCESS;
}


static int init_priv_args( log_t* log ){
        log_private_t* lp;
        log->logpriv = (log_private_t*)calloc( 1, sizeof( log_private_t) );
        lp = log->logpriv;

        memset( lp, 0, sizeof(log_private_t) );

         

        lp->thread_active = 1;
        // lp->thread_sleep = 0;

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