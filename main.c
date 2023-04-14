#include <stdio.h>
#include <sqlite3.h>
#include "src/sql/sql.h"


int main(){
        printf("\n\n");
        sqlite3 *db;

        database_open( &db, "test.db");
        print_tables(db);



        sqlite3_close(db);
}