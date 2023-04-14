#include "../sql.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>




int database_exists(const char* path){
        if( access( path, F_OK ) == 0 ){
                return EXIT_SUCCESS;
        }else{
                return EXIT_FAILURE;
        }
}
int database_valid_perms(const char* path){
        if( access(path, (R_OK | W_OK)) == 0 ){
                return EXIT_SUCCESS;
        }else{
                return EXIT_FAILURE;
        }
}

int database_create(sqlite3 **db, const char* path){

        int status = 0;
        int sql_status = SQLITE_OK;

        if( path == NULL ){
                puts("Error in: database_create");
                puts("Input arg is NULL");
                return EXIT_FAILURE;
        }

        
        
    

        if( status == EXIT_FAILURE )    //The helper function will complain if the path is too long
                return EXIT_FAILURE;


        sql_status = sqlite3_open_v2(path, db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
        if( sql_status != SQLITE_OK){
                printf("Error in creating sql database\n");
                printf("in: %s\n", __FUNCTION__);
        }

        return EXIT_SUCCESS;

}


int print_tables( sqlite3 *db ){
        const char* tables = "SELECT name FROM sqlite_master WHERE type='table'";
        sqlite3_stmt *statement;
        int sql_status = SQLITE_OK;

        sql_status = sqlite3_prepare_v2( db, tables, -1, &statement, NULL);

        if( sql_status != SQLITE_OK ){
                printf("sql statement composition error\n");
                printerr_loc();
                printf("--------------sqlite3 error msg--------------\n");
                printf("%s\n", sqlite3_errstr(sql_status));
                printf("---------------------------------------------\n");
                return EXIT_FAILURE;
        }

        printf("columns: %i\n", sqlite3_column_count( statement ) );
        printf("Col type: %i\n", sqlite3_column_type( statement, 0 ));

        sql_status = sqlite3_step( statement );
        if( sql_status != SQLITE_OK ){
                printf("--------------sqlite3 error msg--------------\n");
                printf("%s\n", sqlite3_errstr(sql_status));
                printf("---------------------------------------------\n");
        }
        printf("Col type: %i\n", sqlite3_column_type( statement, 0 ));

        printf("str: %s\n", sqlite3_column_text( statement, 0));

        sql_status = sqlite3_step( statement );
        if( sql_status != SQLITE_OK ){
                printf("--------------sqlite3 error msg--------------\n");
                printf("%s\n", sqlite3_errstr(sql_status));
                printf("---------------------------------------------\n");
        }
        printf("Col type: %i\n", sqlite3_column_type( statement, 0 ));

        printf("str: %s\n", sqlite3_column_text( statement, 0));
        






        return EXIT_SUCCESS;
} 











