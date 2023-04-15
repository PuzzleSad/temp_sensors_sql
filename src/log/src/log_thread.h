#ifndef LOG_THREAD_H
#define LOG_THREAD_H



#include "../log.h"

//Underscores is an experimental coding style

//threadsetup initializes thread specific variables i.e. log_private
//initthread STARTS the thread, i.e. have the path of the logfile filled in before then
int _log_threadsetup( log_t* log );
int _log_initthread( log_t* log ); 
int _log_endthread( log_t* log );
int _log_finithread( log_t* log );


#endif