#include "../temp_sensors.h"
#include "../s_vtable.h"


#include <stdlib.h>
#include <string.h>

struct sensors_private_t{
        int count;
        s_vtable_t* function_tables;
};

int init_sensors( sensors_t* sensors ){
        memset( sensors, 0, sizeof(sensors_t) );
        sensors->sens_private = (sensors_private_t*)calloc( 1, sizeof( sensors_private_t ));

        return EXIT_SUCCESS;
}

int init_sensors_of_type( sensors_t* sensors, uint32_t type ){
        /* TODO this */
        (void)type;
        (void)sensors;
        return 0;
}