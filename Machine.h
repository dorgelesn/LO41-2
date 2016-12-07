#ifndef MACHINE_H
#define MACHINE_H

#include <pthread.h>

typedef int bool;
#define true 1
#define false 0

typedef struct
{

    pthread_t m__thread;
    int m__temps_courant;
    bool m__defaillance;

} Machine;

Machine* machine_new(void* ( *thread_fonction)(void*));
void machine_delete(Machine* machine);

void machine_start(Machine* machine);

int machine_get_temps_courant(Machine* machine);
void machine_tick(Machine* machine);

bool machine_get_defaillance(Machine* machine);
bool machine_is_occupe(Machine* machine);

#endif
