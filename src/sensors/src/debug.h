#ifndef SENSORS_DEBUG_H
#define SENSORS_DEBUG_H

#define printerr_loc(errmsg)\
do{\
        fprintf(stderr, "\033[91m"errmsg"\033[0m");\
        fprintf(stderr, "\033[95m""func: %s\n""\033[0m", __FUNCTION__);\
        fprintf(stderr, "\033[95m""file: %s\n""\033[0m", __FILE__);\
        fprintf(stderr, "\033[95m""line: %d\n""\033[0m", __LINE__);\
}while(0)


#endif