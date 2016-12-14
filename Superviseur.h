#ifndef SUPERVISEUR_H
#define SUPERVISEUR_H

#include "Machine.h"
#include "Alimentation.h"
#include "Convoyeur.h"
#include "Type.h"
#include "Table.h"
#include "Produit.h"

typedef struct
{

    Machine* m__base;

    Convoyeur* m__convoyeur;
    Alimentation* m__alimentation;
    Retrait* m__retrait;

    Type** m__types;
    int m__num_types;

    Table** m__tables;
    int m__num_tables;

    Produit** m__produits;
    int m__num_produits;

} Superviseur;

Superviseur* superviseur_new(char* produits, char* types, char* tables);
void superviseur_delete(Superviseur* superviseur);

int superviseur_start(Superviseur* superviseur);
int superviseur_join(Superviseur* superviseur);
int superviseur_stop(Superviseur* superviseur);
void* superviseur_thread(void* args);

void superviseur_import_produits(Superviseur* superviseur, char* fichier_produits);
void superviseur_import_types(Superviseur* superviseur, char* fichier_types);
void superviseur_import_tables(Superviseur* superviseur, char* fichier_tables);

#endif
