#include "Convoyeur.h"

#include <stdio.h>
#include <stdlib.h>

#include "Affichage.h"

Convoyeur* convoyeur_new(Retrait* retrait, Table** tables, int num_tables)
{

    afficher_debug("[Convoyeur]: constructor\n");

    Convoyeur* c = malloc(sizeof(Convoyeur));

    c->m__base = machine_new();

    c->m__retrait = retrait;
    c->m__tables = tables;

    c->m__produit = NULL;
    c->m__position = 0;

    return c;

}


void convoyeur_delete(Convoyeur* convoyeur)
{

    afficher_debug("[Convoyeur]: destructor\n");

    machine_delete(convoyeur->m__base);

    free(convoyeur);

}


int convoyeur_start(Convoyeur* convoyeur)
{

    return machine_start(convoyeur->m__base, &convoyeur_thread, convoyeur);

}


int convoyeur_join(Convoyeur* convoyeur)
{

    afficher_debug("[Convoyeur]: ==convoyeur_thread_join==\n");
    return machine_join(convoyeur->m__base);

}


int convoyeur_stop(Convoyeur* convoyeur)
{

    afficher_debug("[Convoyeur]: ==convoyeur_thread_stop==\n");
    return machine_stop(convoyeur->m__base);

}


void convoyeur_wake(Convoyeur* alimentation){

    machine_wake(alimentation->m__base);
    return;

}


void* convoyeur_thread(void* args)
{

    afficher_debug("[Convoyeur]: ==convoyeur_thread==\n");

    Convoyeur* convoyeur = (Convoyeur*) args;

    while(!machine_get_should_stop(convoyeur->m__base))
    {

        machine_lock(convoyeur->m__base);
        {

            //if(convoyeur->m__produit)
              //  retrait_recevoir_produit_convoyeur(convoyeur->m__retrait, convoyeur->m__produit);

            //Dormir
            machine_sleep(convoyeur->m__base);

        }
        machine_unlock(convoyeur->m__base);

    }

    pthread_exit(NULL);

    return 0;

}


void convoyeur_recevoir_produit_alimentation(Convoyeur* convoyeur, Produit* produit)
{

    afficher_debug("[Convoyeur]: convoyeur_recevoir_produit_alimentation\n");

    machine_lock(convoyeur->m__base);
    {

        convoyeur->m__position = 0;
        convoyeur->m__produit = produit;

        machine_signal(convoyeur->m__base);
        machine_wake(convoyeur->m__base);

    }
    machine_unlock(convoyeur->m__base);

}


void convoyeur_recevoir_produit_table(Convoyeur* convoyeur, Table* table, Produit* produit)
{

    machine_lock(convoyeur->m__base);
    {

        if(convoyeur->m__produit)
            machine_wait(convoyeur->m__base);

        int i = 0;
        bool found_table = false;
        while(!found_table)
        {

            if(convoyeur->m__tables[i] == table)
            {

                found_table = true;

            }else
            {

                i++;

            }

        }

        convoyeur->m__position = i + 1; //Décalé de 1 a cause du robot d'alimentation du convoyeur
        convoyeur->m__produit = produit;

        machine_signal(convoyeur->m__base);
        machine_wake(convoyeur->m__base);

    }
    machine_unlock(convoyeur->m__base);

}


void convoyeur_donner_produit_table(Convoyeur* convoyeur, Table* table)
{

    table_recevoir_produit_convoyeur(table, convoyeur, convoyeur->m__produit);
    convoyeur->m__produit = NULL;

}


void convoyeur_donner_produit_retrait(Convoyeur* convoyeur)
{

    retrait_recevoir_produit_convoyeur(convoyeur->m__retrait, convoyeur->m__produit);
    convoyeur->m__produit = NULL;

}

int convoyeur_position_max(Convoyeur* convoyeur)
{

    return convoyeur->m__num_tables + 2;

}


Produit* convoyeur_get_produit(Convoyeur* convoyeur)
{

    return convoyeur->m__produit;

}
