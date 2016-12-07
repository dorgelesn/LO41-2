#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <pthread.h>

typedef int bool;
#define true 1
#define false 0

typedef struct {

    bool m__debug;
    pthread_mutex_t m__mutex;
    pthread_cond_t m__attendre;
    bool m__affiche;

} Afficheur;

Afficheur afficheur;

void afficheur_init(bool debug);

int afficher(const char* format, ...);
int afficher_debug(const char* format, ... );

#endif

