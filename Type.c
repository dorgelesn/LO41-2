#include "Type.h"

#include <stdio.h>
#include <stdlib.h>

Type* new_type(int tmps, int tmps_max)
{

    printf("[Type]: constructor\n");

    Type* t = malloc(sizeof(Type));

    t->m__temps = tmps;
    t->m__temps_max = tmps_max;
    printf("[Type] constructor(): %p\n", t);

    return t;

}


void delete_type(Type* type)
{

    printf("[Type]: destructor\n");
    printf("[Type] destructor(): %p\n", &type);

    free(type);

}


int type_get_temps(Type* type)
{

    return 0;

}


int type_get_temps_max(Type* type)
{

    return 0;

}
