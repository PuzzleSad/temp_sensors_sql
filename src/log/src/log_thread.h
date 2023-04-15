#ifndef LOG_THREAD_H
#define LOG_THREAD_H

#define printerr_loc(errmsg)\
do{\
        printf("\033[91m"errmsg"\033[0m");\
        printf("\033[95m""func: %s\n""\033[0m", __FUNCTION__);\
        printf("\033[95m""file: %s\n""\033[0m", __FILE__);\
        printf("\033[95m""line: %d\n""\033[0m", __LINE__);\
}while(0)

#include "../log.h"

//Underscores is an experimental coding style

//threadsetup initializes thread specific variables i.e. log_private
//initthread STARTS the thread, i.e. have the path of the logfile filled in before then
int _log_threadsetup( log_t* log );
int _log_initthread( log_t* log ); 
int _log_endthread( log_t* log );
int _log_finithread( log_t* log );


#endif