#include "Affichage.h"

#include<stdarg.h>
#include<stdio.h>

void afficheur_init(bool debug)
{

    afficheur.m__debug = debug;

}


int afficher(const char* format, ...)
{

    pthread_mutex_lock (&(afficheur.m__mutex));

    int done = 1;

    va_list arg;

    if(afficheur.m__affiche)
        pthread_cond_wait(&(afficheur.m__attendre), &(afficheur.m__mutex));

    afficheur.m__affiche = true;

    va_start (arg, format);
    done = fprintf (stdout, format, arg);
    va_end (arg);

    afficheur.m__affiche = false;

    pthread_cond_signal(&(afficheur.m__attendre));


    pthread_mutex_unlock (&(afficheur.m__mutex));

    return done;

}


int afficher_debug(const char* format, ... )
{

    int done = 1;

    if(afficheur.m__debug)
    {

        va_list arg;

        va_start (arg, format);
        done = afficher(format, arg);
        va_end (arg);

    }

    return done;

}
