#ifndef USINE_H
#define USINE_H

#include "Convoyeur.h"
#include "Superviseur.h"

typedef struct {

    Convoyeur* m__convoyeur;
    Superviseur* m__superviseur;

} Usine;

Usine* new_usine();
void delete_usine(Usine* usine);

void start_usine(Usine* usine);

#endif
