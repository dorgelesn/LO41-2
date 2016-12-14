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


#include "Retrait.h"

#include <stdio.h>
#include <stdlib.h>

#include "Display.h"

Retrait* retrait_new()
{

    display_debug("[Retrait]: constructor\n");

    Retrait* r = malloc(sizeof(Retrait));

    r->m__base = machine_new();

    return r;

}


void retrait_delete(Retrait* retrait)
{

    display_debug("[Retrait]: destructor\n");

    machine_delete(retrait->m__base);

    free(retrait);

}


int retrait_start(Retrait* retrait)
{

    return machine_start(retrait->m__base, &retrait_thread, retrait);

}


int retrait_join(Retrait* retrait)
{

    display_debug("[Retrait]: ==retrait_thread_join==\n");
    return machine_join(retrait->m__base);

}


int retrait_stop(Retrait* retrait)
{

    display_debug("[Retrait]: ==retrait_thread_stop==\n");
    return machine_stop(retrait->m__base);

}


void retrait_wake(Retrait* retrait)
{

    display_debug("[Retrait]: ==retrait_thread_wake==\n");
    machine_wake(retrait->m__base);
    return;

}


void* retrait_thread(void* args)
{

    display_debug("[Retrait]: ==retrait_start==\n");

    Retrait* retrait = (Retrait*) args;

    while(!machine_get_should_stop(retrait->m__base))
    {

        machine_lock(retrait->m__base);
        {

            machine_sleep(retrait->m__base);

        }
        machine_unlock(retrait->m__base);

    }

    return 0;

}

void retrait_receive_product_conveyor(Retrait* retrait, Product* product)
{

    machine_lock(retrait->m__base);

    if(retrait->m__product)
        machine_wait(retrait->m__base);

    retrait->m__product = product;

    machine_signal(retrait->m__base);

    machine_unlock(retrait->m__base);

}


void retrait_sortir_product(Retrait* retrait)
{

    product_delete(retrait->m__product);
    retrait->m__product = NULL;

}
