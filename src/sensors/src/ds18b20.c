#include "../ds18b20.h"
#include "debug.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

static int ds18b20_path( char* buff, const char* prefix, char* dir, int bufflen);

int find_ds18b20_sensors(ds18b20_t** d){
        const char* prefix_path = "/sys/bus/w1/devices";

        struct dirent *dir_p;
        DIR *dir;

        

        d = NULL;

        (void)d;        /* TODO this */

        if( (dir = opendir(prefix_path)) == NULL ){
                fprintf(stderr, "dir: %s\n", prefix_path);
                printerr_loc("dir not found\n");
                return EXIT_FAILURE;
        }

        while( (dir_p = readdir(dir)) != NULL ){
                /* regex name of sensor dir */
                // printf("\033[33mFile: %s\033[0m\n", dir_p->d_name);

                if( strstr( dir_p->d_name, "28-") != NULL ){
                        /* Found path to a ds18b20 dir */
                        #define BUFF_LEN 100
                        char buff[BUFF_LEN];

                        ds18b20_path( 
                                buff, 
                                prefix_path,
                                dir_p->d_name, 
                                BUFF_LEN 
                                );


                        #undef BUFFLEN

                

                }
        }



        /* TODO implementation */
        
        return 0;
}


//expected:
//      prefix: /sys/bus/w1/devices
//      dir:     28-01801082158       (example name)
//      output: /sys/bus/w1/devices/28-01801082158/<something>
static int ds18b20_path( char* buff, const char* prefix, char* dir, int bufflen){
        memset( buff, 0, bufflen );

        int str_len = 0;
        str_len += strlen( prefix );
        str_len += strlen( dir );
        str_len += 5;   //thumbsuck number to account for possible additional characters
        if( str_len >= bufflen ){
                printerr_loc("string too large for buffer\n");
                return EXIT_FAILURE;
        }

        /* TODO finish this */
        sprintf(buff, "%s/%s/todo", prefix, dir);

        return EXIT_SUCCESS;
}

