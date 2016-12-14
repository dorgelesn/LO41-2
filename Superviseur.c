#include "Superviseur.h"

#include <stdio.h>
#include <stdlib.h>

#include "Affichage.h"

Superviseur* superviseur_new(char* produits, char* types, char* tables)
{

    afficher_debug("[Superviseur]: constructor\n");

    Superviseur* s = malloc(sizeof(Superviseur));


    s->m__base = machine_new();

    superviseur_import_types(s, types);
    superviseur_import_produits(s, produits);
    superviseur_import_tables(s, tables);

    Retrait* retrait = retrait_new();
    Convoyeur* convoyeur = convoyeur_new(retrait, s->m__tables, s->m__num_tables);
    Alimentation* alim = alimentation_new(convoyeur, s->m__produits);

    s->m__alimentation = alim;
    s->m__convoyeur = convoyeur;
    s->m__retrait = retrait;

    return s;

}


void superviseur_delete(Superviseur* superviseur)
{

    afficher_debug("[Superviseur]: destructor\n");

    alimentation_delete(superviseur->m__alimentation);
    convoyeur_delete(superviseur->m__convoyeur);
    retrait_delete(superviseur->m__retrait);

    for(int i = 0; i < superviseur->m__num_produits; i++)
        produit_delete(superviseur->m__produits[i]);
    free(superviseur->m__produits);

    for(int i = 0; i < superviseur->m__num_types; i++)
        type_delete(superviseur->m__types[i]);
    free(superviseur->m__types);

    for(int i = 0; i < superviseur->m__num_tables; i++)
        table_delete(superviseur->m__tables[i]);
    free(superviseur->m__tables);

    machine_delete(superviseur->m__base);

    free(superviseur);

}


int superviseur_start(Superviseur* superviseur)
{

    if(convoyeur_start(superviseur->m__convoyeur))
        return 1;

    if(alimentation_start(superviseur->m__alimentation))
        return 1;

    if(retrait_start(superviseur->m__retrait))
        return 1;

    for(int i = 0; i < superviseur->m__num_tables; i++)
    {

        if(table_start(superviseur->m__tables[i]))
            return 1;

    }

    return machine_start(superviseur->m__base, &superviseur_thread, superviseur);

}


int superviseur_join(Superviseur* superviseur)
{

    afficher_debug("[Superviseur]: ==superviseur_thread_join==\n");

    if(convoyeur_join(superviseur->m__convoyeur))
        return 1;

    if(alimentation_join(superviseur->m__alimentation))
        return 1;

    if(retrait_join(superviseur->m__retrait))
        return 1;

    for(int i = 0; i < superviseur->m__num_tables; i++)
    {

        if(table_join(superviseur->m__tables[i]))
            return 1;

    }

    return machine_join(superviseur->m__base);

}


int superviseur_stop(Superviseur* superviseur)
{

    afficher_debug("[Superviseur]: ==superviseur_thread_stop==\n");

    if(convoyeur_stop(superviseur->m__convoyeur))
        return 1;

    if(alimentation_stop(superviseur->m__alimentation))
        return 1;

    if(retrait_stop(superviseur->m__retrait))
        return 1;

    for(int i = 0; i < superviseur->m__num_tables; i++)
    {

        if(table_stop(superviseur->m__tables[i]))
            return 1;

    }

    return machine_stop(superviseur->m__base);

}


void* superviseur_thread(void* args)
{

    afficher_debug("[Superviseur]: ==superviseur_start==\n");

    Superviseur* superviseur = (Superviseur*) args;

    while(!machine_get_should_stop(superviseur->m__base))
    {

        for(int i = 0; i < superviseur->m__num_types; i++)
        {

            afficher("Type : %p", 5+i, superviseur->m__types[i]);

        }
        for(int i = 0; i < superviseur->m__num_tables; i++)
        {

            afficher("Table : %p", 8+i, superviseur->m__tables[i]);

        }
        for(int i = 0; i < superviseur->m__num_produits; i++)
        {

            afficher("Produit : %p", 12+i, superviseur->m__produits[i]);

        }
        sleep(1);

    }

    return 0;

}


void superviseur_import_produits(Superviseur* superviseur, char* fichier_produits)
{

    superviseur->m__num_produits = 3;
    superviseur->m__produits = (Produit**) malloc(sizeof(Produit*) * superviseur->m__num_produits);

    superviseur->m__produits[0] = produit_new(superviseur->m__types[0]);
    superviseur->m__produits[1] = produit_new(superviseur->m__types[0]);
    superviseur->m__produits[2] = produit_new(superviseur->m__types[0]);

}


void superviseur_import_types(Superviseur* superviseur, char* fichier_types)
{

    superviseur->m__num_types = 1;
    superviseur->m__types = (Type**) malloc(sizeof(Type*) * superviseur->m__num_types);

    superviseur->m__types[0] = type_new(10, 30);

}


void superviseur_import_tables(Superviseur* superviseur, char* fichier_tables)
{

    superviseur->m__num_tables = 3;

    superviseur->m__tables = (Table**) malloc(sizeof(Table*) * superviseur->m__num_tables);

    superviseur->m__tables[0] = table_new(superviseur->m__types);
    superviseur->m__tables[1] = table_new(superviseur->m__types);
    superviseur->m__tables[2] = table_new(superviseur->m__types);

}
