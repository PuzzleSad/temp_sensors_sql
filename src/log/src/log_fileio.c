#include "../log.h"
#include "log_fileio.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>


static int create_logf( log_t* log );


int test_file( log_t* log, int create_if_nofile ){
        if( log->path == NULL ){
                /* file path ptr null */
                fprintf( stderr, "\033[91mError, input path is null\033[0m\n");
                printerr_loc("file path null\n");
                return EXIT_FAILURE;
        }

        if( access( log->path, F_OK ) != EXIT_SUCCESS ){
                /* No log file, create log file if flag set */

                if( create_if_nofile == 1 ){
                        #ifndef NDEBUG
                        fprintf(stderr, "\033[92mLogfile creation\033[0m\nLogFile: %s\n", log->path);
                        #endif

                        create_logf( log );
                        log->logfile_ok = 1;
                        return EXIT_SUCCESS;
                }else{
                        #ifndef NDEBUG
                        fprintf(stderr, "\033[92mLogfile doesnt exist\033[0m\nLogFile: %s\n", log->path);
                        #endif

                        log->logfile_ok = 0;
                        return EXIT_FAILURE;
                }


                

        }else{
                /* File exists, test if can modify */
                if( access( log->path, W_OK) != EXIT_SUCCESS ){
                        /* file exits, no write perms */
                        fprintf(stderr, "ERROR file does not have appropriate W access\n");
                        printerr_loc("error file perms\n");
                        log->logfile_ok = 0;
                        return EXIT_FAILURE;
                }else{
                        /* file exits, has write perms */
                        log->logfile_ok = 1;
                        return EXIT_SUCCESS;
                }
        }
}

int write_log( log_t* log, char* msg ){
        assert( log->path != NULL);

        if( log->logfile_ok == 0 ){
                printerr_loc("Logfile_ok error\n");
                return EXIT_FAILURE;
        }
        int status = 0;

        FILE *fp;
        fp = fopen( log->path, "a");

        #ifdef PARANOID_FILETESTING
        status = test_file( log, 0 );
        if( status != EXIT_SUCCESS ){
                fprintf(stderr, "Error, write_log repots file test failure\n");
                printerr_loc("test_file report fail\n");
                return EXIT_FAILURE;
        }

        if( fp == NULL ){
                printerr_loc("file open failure\n");
                return EXIT_FAILURE;
        }
        #endif

        fprintf( fp, "%s", msg);

        fclose( fp );

        return EXIT_SUCCESS;
}









static int create_logf( log_t* log ){

        FILE *fp;
        fp = fopen( log->path, "w+");

        if( fp == NULL ){
                fprintf( stderr, "\033[91mERROR, Failed to create file\033[0m:\n%s\n", log->path);
                printerr_loc("file creation error\n");
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}