#include "Retrait.h"

#include <stdio.h>
#include <stdlib.h>

#include "Affichage.h"

Retrait* retrait_new()
{

    afficher_debug("[Retrait]: constructor\n");

    Retrait* r = malloc(sizeof(Retrait));

    r->m__base = machine_new();

    return r;

}


void retrait_delete(Retrait* retrait)
{

    afficher_debug("[Retrait]: destructor\n");

    machine_delete(retrait->m__base);

    free(retrait);

}


int retrait_start(Retrait* retrait)
{

    return machine_start(retrait->m__base, &retrait_thread, retrait);

}


int retrait_join(Retrait* retrait)
{

    afficher_debug("[Retrait]: ==retrait_thread_join==\n");
    return machine_join(retrait->m__base);

}


int retrait_stop(Retrait* retrait)
{

    afficher_debug("[Retrait]: ==retrait_thread_stop==\n");
    return machine_stop(retrait->m__base);

}


void retrait_wake(Retrait* retrait)
{

    afficher_debug("[Retrait]: ==retrait_thread_wake==\n");
    machine_wake(retrait->m__base);
    return;

}


void* retrait_thread(void* args)
{

    afficher_debug("[Retrait]: ==retrait_start==\n");

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

void retrait_recevoir_produit_convoyeur(Retrait* retrait, Produit* produit)
{

    machine_lock(retrait->m__base);

    if(retrait->m__produit)
        machine_wait(retrait->m__base);

    retrait->m__produit = produit;

    machine_signal(retrait->m__base);

    machine_unlock(retrait->m__base);

}


void retrait_sortir_produit(Retrait* retrait)
{

    produit_delete(retrait->m__produit);
    retrait->m__produit = NULL;

}
