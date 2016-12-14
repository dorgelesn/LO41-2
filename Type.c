#include "Type.h"

#include <stdio.h>
#include <stdlib.h>

#include "Display.h"

Type* type_new(int tmps, int tmps_max)
{

    display_debug("[Type]: constructor\n");

    Type* t = malloc(sizeof(Type));

    t->m__temps = tmps;
    t->m__temps_max = tmps_max;

    return t;

}


void type_delete(Type* type)
{

    display_debug("[Type]: destructor\n");

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
