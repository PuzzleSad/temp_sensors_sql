#ifndef LOG_FILEIO_H
#define LOG_FILEIO_H

#include "../log.h"
#include "log_priv.h"

#define CREATE_IF_NO_FILE 1

//each and every file write will be preceded by a check to see if the file exists with the correct perms
#define PARANOID_FILETESTING

int test_file( log_t* log, int create_if_nofile );

int write_log( log_t* log, char* msg );



#endif