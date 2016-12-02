#include "Machine.h"

#include <stdio.h>
#include <stdlib.h>

Machine* new_machine(void* thread_fonction)
{

    Machine* m = malloc(sizeof(Machine));

    int erreur = pthread_create(m->m__thread, NULL, thread_fonction, NULL);
    m->m__temps_courant = 0;
    m->m__defaillance = false;

    return m;

}


void delete_machine(Machine* machine)
{

    free(machine);

}


void machine_start(Machine* machine)
{

    printf("[Machine] : machine_start\n");

}


int machine_get_temps_courant(Machine* machine)
{

    return 0;

}


void machine_tick(Machine* machine)
{



}


bool machine_get_defaillance(Machine* machine)
{

    return false;

}


bool machine_is_occupe(Machine* machine)
{

    return false;

}
