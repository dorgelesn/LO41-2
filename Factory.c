#include "Factory.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "Display.h"

Factory* factory_new(char* products, char* types, char* tables)
{

    display_debug("[Factory]: constructor\n");

    Factory* u = malloc(sizeof(Factory));

    u->m__supervisor = supervisor_new(products, types, tables);

    return u;

}


void factory_delete(Factory* factory)
{

    display_debug("[Factory]: destructor\n");

    supervisor_delete(factory->m__supervisor);

    free(factory);

}

int factory_start(Factory* factory)
{

    display_debug("[Factory] : ==factory_start==\n");

    return supervisor_start(factory->m__supervisor);

}


int factory_join(Factory* factory)
{

    display_debug("[Factory]: ==factory_join==\n");
    return supervisor_join(factory->m__supervisor);

}


int factory_stop(Factory* factory)
{

    display_debug("[Factory]: ==factory_stop==\n");
    return supervisor_stop(factory->m__supervisor);

}

