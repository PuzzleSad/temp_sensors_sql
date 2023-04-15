#ifndef DS18B20_H
#define DS18B20_H

#include <stdint.h>
#include "temp_sensors.h"
#include "s_vtable.h"

typedef struct ds18b20_t{
        uint64_t dev_id;
        char* path;
}ds18b20_t;

/* reminder, ** implies function edits stack ptr val */
int find_ds18b20_sensors(ds18b20_t** d);        //retval: how many sensors found




#endif