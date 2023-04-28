#include "../temp_sensors_sql.h"
#include "stringutils/stringutils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define eval_status(status)\
do{\
        if( status == EXIT_SUCCESS ){\
                return EXIT_SUCCESS;\
        }else{\
                return EXIT_FAILURE;\
        }\
}while(0);

#define LOGFILE_DEFAULT "log.txt"

#ifdef TEMP_SENSORS_SQL_SHORTHAND

int tss_init( tss_t* tsst ){
        return init_temp_sensors_sql( tsst );
}
int tss_startlog( tss_t* tsst, char* logfile ){
        return temp_sensors_sql_startlog( tsst, logfile );
}

#endif


int init_temp_sensors_sql( temp_sensors_sql_t* tsst ){
        memset( tsst, 0, sizeof( temp_sensors_sql_t ) );
        tsst->log = (log_t*)calloc( 1, sizeof(log_t) );



        return EXIT_SUCCESS;
}

int temp_sensors_sql_startlog( temp_sensors_sql_t* tsst, char* logfile ){
        int status = 0;

        status = log_init( tsst->log );
        eval_status(status);

        if( logfile == NULL ){
                status = log_logfile( tsst->log, LOGFILE_DEFAULT );
                eval_status(status);
        }else{
                log_logfile( tsst->log, logfile );
                eval_status(status);
        }

        status = log_start( tsst->log );
        eval_status(status);

        return EXIT_SUCCESS;
}