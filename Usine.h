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

Usine* usine_new();
void usine_delete(Usine* usine);

void* usine_start(void* args);

#endif
