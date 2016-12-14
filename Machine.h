#ifndef MACHINE_H
#define MACHINE_H

#include <pthread.h>

typedef int bool;
#define true 1
#define false 0

typedef struct
{

    pthread_attr_t m__attr;
    pthread_t m__thread;
    int m__temps_courant;
    bool m__defaillance;

    pthread_mutex_t m__mutex;
    pthread_cond_t m__cond;
    pthread_cond_t m__dormir;

    bool m__should_stop;

} Machine;

Machine* machine_new();
void machine_delete(Machine* machine);

int machine_start(Machine* machine, void* ( *thread_fonction)(void*), void* args);
int machine_join(Machine* machine);
int machine_stop(Machine* machine);

void machine_lock(Machine* machine);
void machine_unlock(Machine* machine);

void machine_wait(Machine* machine);
void machine_signal(Machine* machine);

void machine_sleep(Machine* machine);
void machine_wake(Machine* machine);

bool machine_get_should_stop(Machine* machine);

int machine_get_temps_courant(Machine* machine);

bool machine_get_defaillance(Machine* machine);
bool machine_is_occupe(Machine* machine);

#endif
