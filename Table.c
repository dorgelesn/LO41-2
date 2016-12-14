#include "Table.h"

#include <stdio.h>
#include <stdlib.h>

#include "Affichage.h"

#include "Convoyeur.h"

Table* table_new(Type** types)
{

    afficher_debug("[Table]: constructor\n");

    Table* t = malloc(sizeof(Table));

    t->m__base = machine_new();

    t->m__produit = NULL;
    t->m__types = types;

    return t;

}


void table_delete(Table* table)
{

    afficher_debug("[Table]: desctructor\n");

    machine_delete(table->m__base);
    free(table);

}


int table_start(Table* table)
{

    return machine_start(table->m__base, &table_thread, table);

}


int table_join(Table* table)
{

    afficher_debug("[Table]: ==table_thread_join==\n");
    return machine_join(table->m__base);

}


int table_stop(Table* table)
{

    afficher_debug("[Table]: ==table_thread_stop==\n");
    return machine_stop(table->m__base);

}


void table_wake(Table* table)
{

    afficher_debug("[Table]: ==table_thread_wake==\n");
    machine_wake(table->m__base);
    return;

}


void* table_thread(void* args)
{

    afficher_debug("[Table]: ==table_thread==\n");

    Table* table = (Table*) args;

    while(!machine_get_should_stop(table->m__base))
    {

        machine_lock(table->m__base);
        {

            //Dormir
            machine_sleep(table->m__base);

        }
        machine_unlock(table->m__base);

    }

    return 0;

}


void table_recevoir_produit_convoyeur(Table* table, void* convoyeur, Produit* produit)
{

    machine_lock(table->m__base);

    if(table->m__produit)
        machine_wait(table->m__base);

    table->m__produit = produit;

    machine_signal(table->m__base);

    machine_unlock(table->m__base);

}


void table_donner_produit_convoyeur(Table* table, void* convoyeur)
{

    convoyeur_recevoir_produit_table((Convoyeur*)convoyeur, table, table->m__produit);
    table->m__produit = NULL;

}


Produit* table_get_produit(Table* table)
{

    return table->m__produit;

}

