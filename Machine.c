#include "Machine.h"

#include <stdio.h>
#include <stdlib.h>

#include "Affichage.h"

Machine* machine_new(void* ( *thread_fonction)(void*))
{

    afficher_debug("[Machine] : constructor\n");

    Machine* m = malloc(sizeof(Machine));

    int erreur = pthread_create(&(m->m__thread), NULL, thread_fonction, NULL);
    m->m__temps_courant = 0;
    m->m__defaillance = false;

    return m;

}


void machine_delete(Machine* machine)
{

    afficher_debug("[Machine]: destructor\n");

    pthread_join(machine->m__thread, NULL);

    free(machine);

}


void machine_start(Machine* machine)
{

    afficher_debug("[Machine] : machine_start\n");

    exit(0);

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
