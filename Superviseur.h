#ifndef SUPERVISEUR_H
#define SUPERVISEUR_H

#include "Machine.h"
#include "Alimentation.h"

typedef struct
{

    Machine* m__base;

    Alimentation* m__alimentation;

} Superviseur;

Superviseur* superviseur_new(Alimentation* alimentation);
void superviseur_delete(Superviseur* superviseur);

void* superviseur_start(void* args);

#endif
