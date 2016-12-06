#ifndef USINE_H
#define USINE_H

#include "Convoyeur.h"
#include "Superviseur.h"
#include "Type.h"

typedef struct {

    Convoyeur* m__convoyeur;
    Superviseur* m__superviseur;
    Type* m__types[1]; //Producted product types

} Usine;

Usine* new_usine();
void delete_usine(Usine* usine);

void start_usine(Usine* usine);

#endif
