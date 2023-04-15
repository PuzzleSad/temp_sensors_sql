#include "../log.h"
#include "log_priv.h"
#include "log_thread.h"
#include "log_fileio.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int log_init( log_t* log ){
        assert( log != NULL );
        int status = 0;
        memset( log, 0, sizeof(log_t));

        
        status = _log_threadsetup( log );

        if(status != EXIT_SUCCESS ){
                printerr_loc("\nlog thread setup error\n");
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}

int log_start( log_t* log ){
        assert( log != NULL );
        int status = 0;
        
        status = test_file( log, CREATE_IF_NO_FILE );

        if(status != EXIT_SUCCESS ){
                printerr_loc("\nlogfile error\n");
                return EXIT_FAILURE;
        }


        status = _log_initthread( log );

        if(status != EXIT_SUCCESS ){
                printerr_loc("\nthread start error\n");
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}


int log_stop( log_t* log ){
        assert( log != NULL );
        int status = 0;
        status = _log_endthread( log );

        if( status != EXIT_SUCCESS ){
                printerr_loc("log_stop error\n");
                return EXIT_FAILURE;
        }
        
        return EXIT_SUCCESS;
}
int log_fini( log_t* log ){
        assert( log != NULL );
        _log_finithread( log );
        return EXIT_SUCCESS;
}

int log_logfile( log_t* log, const char* path ){
        assert( log != NULL );

        if( path == NULL ){
                printerr_loc("path null");
                return EXIT_FAILURE;
        }

        int str_len;
        str_len = strlen(path);

        /* TODO probably do some path max length test here*/

        log->path = (char*)calloc( (str_len + 1), sizeof(char) );
        memcpy( log->path, path, str_len );


        return EXIT_SUCCESS;
}