#ifndef TEMP_SENSORS_SQL
#define TEMP_SENSORS_SQL

#include "src/log/log.h"
// #include "src/reading/reading.h"
#include "src/sensors/temp_sensors.h"
#include "src/sql/sql.h"

#include <stdint.h>

/*
        Consider this a sort of unified struct for everything.
*/

typedef struct temp_sensors_sql_t{
        log_t* log;

}temp_sensors_sql_t;

#endif