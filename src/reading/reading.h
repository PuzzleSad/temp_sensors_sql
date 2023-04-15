#ifndef READING_H_
#define READING_H_

#include <stdint.h>

typedef struct reading_t{
        uint64_t sensor_ID;
        int64_t time;
        double temp;
}reading_t;

typedef struct readings_t{
        int count;
        reading_t* readings;
}readings_t;


#endif