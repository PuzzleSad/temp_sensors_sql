#include "../log.h"
#include "log_fileio.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int test_file( log_t* log ){
        if( access( log->path, F_OK ) != EXIT_SUCCESS ){
                /* File does not exist*/
        }else{
                if( access( log->path, W_OK | R_OK) != EXIT_SUCCESS ){
                        /* either R or W is not allowed */
                }else{
                        /* file exits and is modifiable */
                }
        }
}