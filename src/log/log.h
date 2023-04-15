#ifndef LOG_H_
#define LOG_H_



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
        int logfile_ok; 
        log_private_t* logpriv;
}log_t;


int log_message( log_t* log, const char* msg );




int log_init( log_t* log );
int log_logfile( log_t* log, const char* path );

int log_start( log_t* log );
int log_stop( log_t* log );
int log_fini( log_t* log );


#endif 