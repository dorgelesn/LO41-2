/*
 * Gnikwo < gnikwo AT hotmail DOT com >
 *
 * Copyright (c) 2016 Gnikwo
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction,
 * including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */


#ifndef MACHINE_H
#define MACHINE_H

#include <pthread.h>
#include <unistd.h>

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
    pthread_cond_t m__receive;
    pthread_cond_t m__give;
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

void machine_wait_receive(Machine* machine);
void machine_wait_give(Machine* machine);
void machine_signal_receive(Machine* machine);
void machine_broadcast_receive(Machine* machine);
void machine_signal_give(Machine* machine);

void machine_sleep(Machine* machine);
void machine_wake(Machine* machine);

bool machine_get_should_stop(Machine* machine);

int machine_get_temps_courant(Machine* machine);

bool machine_get_defaillance(Machine* machine);
bool machine_is_occupe(Machine* machine);

#endif
