#ifndef TEMP_SENSORS_SQL
#define TEMP_SENSORS_SQL

#include "src/log/log.h"
// #include "src/reading/reading.h"
#include "src/sensors/temp_sensors.h"
#include "src/sql/sql.h"

#include <stdint.h>

#ifndef TEMP_SENSORS_SQL_SHORTHAND
// #define TEMP_SENSORS_SQL_SHORTHAND //comment in and out, otherwise, do the define before including this file
#endif

/*
        Consider this a sort of unified struct for everything.
*/

typedef struct temp_sensors_sql_t{
        log_t* log;

}temp_sensors_sql_t;


int init_temp_sensors_sql( temp_sensors_sql_t* tsst );
int temp_sensors_sql_startlog( temp_sensors_sql_t* tsst, char* logfile );       //set logfile NULL for default


//Small QOL if the user wishes to type less
#ifdef TEMP_SENSORS_SQL_SHORTHAND

typedef temp_sensors_sql_t tss_t;

int tss_init( tss_t* tsst );
int tss_startlog( tss_t* tsst, char* logfile );       //set logfile NULL for default

#endif




#endif