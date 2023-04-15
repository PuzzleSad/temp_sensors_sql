#include "../sql.h"

#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int database_open(sqlite3 **db,const char* path){

        /*
                if no db
                        ask to make one or quit
                else
                        check if we can edit, complain if we cant
        */

        if( database_exists(path) != EXIT_SUCCESS ){
                printf("Database [%s] doesn't exist\n", path );
                printf("Please type \"YES\" if you want a NEW database to be created locally with the name:\n%s\n", path);

                char scan_str[100];
                scanf("%99s", scan_str);

                if( strcmp( scan_str, "YES" ) == 0 ){
                        printf("Creading db...\n");
                        database_create(db, path);
                }else{
                        printf("Exiting. No database found or created\n");
                }

        }else{//on success
                if( database_valid_perms(path) != EXIT_SUCCESS ){
                        printf("Error, database [%s] does not appear to have valid read/write permissions.", path);
                        return EXIT_FAILURE;
                }

                printf("Database found: %s\n", path);
                int sql_status = SQLITE_OK;
                sql_status = sqlite3_open_v2( path, db, SQLITE_OPEN_READWRITE, NULL);    
                if(sql_status != SQLITE_OK ){
                        printf("sql open error\n");
                        printerr_loc();
                        printf("--------------sqlite3 error msg--------------\n");
                        printf("%s\n", sqlite3_errstr(sql_status));
                        printf("---------------------------------------------\n");
                        return EXIT_FAILURE;
                }else{
                        return EXIT_SUCCESS;
                }
        }


        
        return EXIT_SUCCESS;
}