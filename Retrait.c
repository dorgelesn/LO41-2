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
