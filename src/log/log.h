#ifndef LOG_H_
#define LOG_H_

#define printerr_loc(errmsg)\
do{\
        printf("\033[91m"errmsg"\033[0m");\
        printf("\033[95m""func: %s\n""\033[0m", __FUNCTION__);\
        printf("\033[95m""file: %s\n""\033[0m", __FILE__);\
        printf("\033[95m""line: %d\n""\033[0m", __LINE__);\
}while(0)

/*
        please note that log spawns a thread.
        it probably doesn't add much but the idea is that the log thread
        can respond if for some reason the thread talking to the SQL module hangs
*/


// #define NDEBUG

//log_private contains variables for thread management
typedef struct log_private_t log_private_t;

typedef struct log_t{
        char* path;
        log_private_t* logpriv;
}log_t;


int log_init( log_t* log );
int log_logfile( log_t* log, const char* path );


int log_start( log_t* log );
int log_stop( log_t* log );
int log_fini( log_t* log );


#endif 