#ifndef SQL_H_
#define SQL_H_

#include <stdint.h>
#include <sqlite3.h>

#define printerr_loc()\
do{\
        printf("func: %s\n", __FUNCTION__);\
        printf("file: %s\n", __FILE__);\
}while(0)

/*
        please note that the functions listed are implemented in multiple c-files
        see: source
*/

int database_open(sqlite3 **db,const char* path);  //ret EXIT_SUCCESS/FAILURE

int print_tables( sqlite3 *db );


//these are internal but feel free to use them
int database_create(sqlite3 **db, const char* path);
int database_exists(const char* path);
int database_valid_perms(const char* path);


#endif