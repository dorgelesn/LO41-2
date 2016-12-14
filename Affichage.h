#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <pthread.h>

#include "Machine.h"

typedef int bool;
#define true 1
#define false 0

typedef struct {

    Machine* m__base;

    bool m__debug;
    bool m__affiche;

    int m__cols;
    int m__lines;

    char** m__data;

} Afficheur;

Afficheur* afficheur;

void afficheur_init(bool debug);
void afficheur_unload();

int afficher(const char* format, int line, ...);
int afficher_debug(const char* format, ... );

void clear();

#endif

