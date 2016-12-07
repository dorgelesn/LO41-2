#ifndef RETRAIT_H
#define RETRAIT_H

#include "Machine.h"

typedef struct
{

    Machine* m__base;

} Retrait;

Retrait* retrait_new();
void retrait_delete(Retrait* retrait);

void* retrait_start(void* args);

#endif
