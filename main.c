#include <stdio.h>
#include <sqlite3.h>
#include "src/sql/sql.h"
#include "src/log/log.h"

#include "src/sensors/ds18b20.h"

#include <unistd.h>


int main(){
        printf("\n\n");
        sqlite3 *db;

        log_t log;
        log_init( &log );
        log_logfile( &log, "log.txt" );
        log_start( &log );


        database_open( &db, "test.db");
        print_tables(db);

        sleep(0);
        
        ds18b20_t* d;
        int ds_count;
        ds_count = find_ds18b20_sensors(&d);




        sqlite3_close(db);
        log_stop( &log );
        log_fini( &log );
}