#ifndef RETRAIT_H
#define RETRAIT_H

#include "Machine.h"

typedef struct
{

    Machine base;

} Retrait;

Retrait* new_retrait();
void delete_retrait(Retrait* retrait);

#endif
