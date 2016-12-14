#include "Machine.h"

#include <stdio.h>
#include <stdlib.h>

#include "Affichage.h"

Machine* machine_new()
{

    afficher_debug("[Machine] : constructor\n");

    Machine* m = malloc(sizeof(Machine));

    m->m__temps_courant = 0;
    m->m__defaillance = false;

    pthread_attr_init(&(m->m__attr));
    pthread_attr_setdetachstate(&(m->m__attr), PTHREAD_CREATE_JOINABLE);

    pthread_mutex_init(&(m->m__mutex), NULL);
    pthread_cond_init(&(m->m__cond), NULL);
    pthread_cond_init(&(m->m__dormir), NULL);

    m->m__should_stop = false;

    return m;

}


void machine_delete(Machine* machine)
{

    afficher_debug("[Machine]: destructor\n");

    pthread_attr_destroy(&(machine->m__attr));

    free(machine);

}


int machine_start(Machine* machine, void* ( *thread_fonction)(void*), void* args)
{

    return pthread_create(&(machine->m__thread), &(machine->m__attr), thread_fonction, args);

}


int machine_join(Machine* machine)
{

    afficher_debug("[Machine]: join\n");
    return pthread_join(machine->m__thread, NULL);

}


int machine_stop(Machine* machine)
{

    afficher_debug("[Machine]: stop\n");
    machine->m__should_stop = true;
    machine_wake(machine);
    return 0;

}


void machine_lock(Machine* machine)
{

    pthread_mutex_lock(&(machine->m__mutex));

}


void machine_unlock(Machine* machine)
{

    pthread_mutex_unlock(&(machine->m__mutex));

}


void machine_wait(Machine* machine)
{

    pthread_cond_wait(&(machine->m__cond), &(machine->m__mutex));

}


void machine_signal(Machine* machine)
{

    pthread_cond_signal(&(machine->m__cond));

}


void machine_sleep(Machine* machine)
{

    pthread_cond_wait(&(machine->m__dormir), &(machine->m__mutex));

}


void machine_wake(Machine* machine)
{

    pthread_cond_signal(&(machine->m__dormir));

}



bool machine_get_should_stop(Machine* machine)
{

    return machine->m__should_stop;

}


int machine_get_temps_courant(Machine* machine)
{

    return 0;

}


bool machine_get_defaillance(Machine* machine)
{

    return false;

}


bool machine_is_occupe(Machine* machine)
{

    return false;

}
