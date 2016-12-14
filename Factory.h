#ifndef USINE_H
#define USINE_H

#include "Supervisor.h"

typedef struct {

    Supervisor* m__supervisor;

} Factory;

Factory* factory_new(char* products, char* types, char* tables);
void factory_delete(Factory* factory);

int factory_start(Factory* factory);
int factory_join(Factory* factory);
int factory_stop(Factory* factory);

#endif
