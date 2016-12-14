#include "Alimentation.h"

#include <stdio.h>
#include <stdlib.h>

#include "Affichage.h"

Alimentation* alimentation_new(Convoyeur* convoyeur, Produit** produits, int num_produits)
{

    afficher_debug("[Alimentation] : constructor\n");

    Alimentation* a = malloc(sizeof(Alimentation));
    a->m__base = machine_new();

    a->m__convoyeur = convoyeur;
    a->m__produits = produits;
    a->m__num_produits = num_produits;

    return a;

}


void alimentation_delete(Alimentation* alimentation)
{

    afficher_debug("[Alimentation]: destructor\n");

    machine_delete(alimentation->m__base);

    free(alimentation);

}


int alimentation_start(Alimentation* alimentation)
{

    return machine_start(alimentation->m__base, &alimentation_thread, alimentation);

}


int alimentation_join(Alimentation* alimentation)
{

    afficher_debug("[Alimentation]: ==alimentation_thread_join==\n");
    return machine_join(alimentation->m__base);

}


int alimentation_stop(Alimentation* alimentation)
{

    afficher_debug("[Alimentation]: ==alimentation_thread_stop==\n");
    return machine_stop(alimentation->m__base);

}


void alimentation_wake(Alimentation* alimentation){

    machine_wake(alimentation->m__base);
    return;

}


void* alimentation_thread(void* argv)
{

    afficher_debug("[Alimentation] : ==alimentation_thread==\n");

    Alimentation* alim = (Alimentation*) argv;

    int i = 0;
    for(; i < alim->m__num_produits; i++)
    {

        if(convoyeur_get_produit(alim->m__convoyeur))
            machine_wait(alim->m__base);
        convoyeur_recevoir_produit_alimentation(alim->m__convoyeur, alim->m__produits[i]);

    }

    while(!machine_get_should_stop(alim->m__base))
    {

        machine_lock(alim->m__base);
        {

            //Dormir
            machine_sleep(alim->m__base);

        }
        machine_unlock(alim->m__base);

    }

    return 0;

}
