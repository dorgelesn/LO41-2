#ifndef USINE_H
#define USINE_H

#include "Superviseur.h"

typedef struct {

    Superviseur* m__superviseur;

} Usine;

Usine* usine_new(char* produits, char* types, char* tables);
void usine_delete(Usine* usine);

int usine_start(Usine* usine);
int usine_join(Usine* usine);
int usine_stop(Usine* usine);

#endif
