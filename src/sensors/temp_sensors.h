#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>
#include "../reading/reading.h"
//s_vtable is not included on purpose
//temp_sensors.c will call the appropriate functions from <sensor>.h when running init

#define DS18B20  1

typedef struct sensors_private_t sensors_private_t;

typedef struct sensor_t{
        uint64_t sensor_type;
        uint64_t sensor_id;
}sensor_t;

typedef struct sensors_t{
        int count;
        sensor_t* sensors;

        sensors_private_t* sens_private;
}sensors_t;

int init_sensors( sensors_t* sensors );

int init_sensors_of_type( sensors_t* sensors, uint32_t type );




#endif