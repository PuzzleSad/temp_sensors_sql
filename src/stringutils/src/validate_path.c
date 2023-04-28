#include "../stringutils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#define printerr_loc(errmsg)\
do{\
        fprintf(stderr, "\033[91m"errmsg"\033[0m");\
        fprintf(stderr, "\033[95m""func: %s\n""\033[0m", __FUNCTION__);\
        fprintf(stderr, "\033[95m""file: %s\n""\033[0m", __FILE__);\
        fprintf(stderr, "\033[95m""line: %d\n""\033[0m", __LINE__);\
}while(0)

static void access_fine_debug_print( const char* path );
static int path_len_warn( size_t len );

int su_validate_path( const char* path ){
        if( access( path, F_OK) != EXIT_SUCCESS ){
                fprintf(stderr, "Error, file does not exist\nPath: %s\n", path);
                return EXIT_FAILURE;
        }

        if( access( path, R_OK|W_OK) != EXIT_SUCCESS ){
                access_fine_debug_print(path);
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}

int su_validate_path_step( const char* path ){
        size_t path_len;
        const char delim[2] = "/";
        char* token;

        char *strbuf;
        

        if( path != NULL ){
                path_len = strlen(path) + 1;

                if( path_len_warn( path_len ) == EXIT_FAILURE ){
                        return EXIT_FAILURE;
                }

                strbuf = (char*)calloc( path_len, sizeof(char) );
                memcpy( strbuf, path, path_len );
        }else{
                printerr_loc("Warning, validate path given NULL path");
                return EXIT_FAILURE;
        }

        
        int path_offset = 0;
        size_t token_len = 0;
        char path_rebuild[path_len + 1];
        memset(path_rebuild, 0, path_len +1);

        

        token = strtok( strbuf, delim );

        while( token != NULL ){
                path_rebuild[path_offset] = '/';
                path_offset++;

                token_len = strlen(token);
                memcpy( &path_rebuild[path_offset], token, token_len);
                path_offset += token_len;

                if( su_validate_path(path_rebuild) != EXIT_SUCCESS ){
                        return EXIT_FAILURE;
                }

                token = strtok( NULL, delim );
        }
        


        free( strbuf );
        return EXIT_SUCCESS;

}





static void access_fine_debug_print( const char* path ){
        fprintf(stderr, "File access permission issue for:\n%s\n", path);

        if( access( path, R_OK ) != EXIT_SUCCESS ){
                fprintf(stderr, "Read permission denied.\n");
        }
        if( access( path, W_OK ) != EXIT_SUCCESS ){
                fprintf(stderr, "Write permission denied.\n");
        }
}

static int path_len_warn( size_t len ){
        if( len > 5000 ){
                fprintf( stderr, "Warning, path length > 5000\nLength: %"PRIu64"\n", len );
                return EXIT_FAILURE;
        }else{
                return EXIT_SUCCESS;
        }
}
