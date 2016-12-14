#include "Display.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

void afficheur_init(bool debug)
{

    afficheur = (Afficheur*) malloc(sizeof(Afficheur));

    afficheur->m__debug = debug;


    afficheur->m__cols = 80;
    afficheur->m__lines = 24;

#ifdef TIOCGSIZE
    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    afficheur->m__cols = ts.ts_m__cols;
    afficheur->m__lines = ts.ts_m__lines;
#elif defined(TIOCGWINSZ)
    struct winsize ts;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
    afficheur->m__cols = ts.ws_col;
    afficheur->m__lines = ts.ws_row;
#endif /* TIOCGSIZE */

    afficheur->m__data = (char**) malloc(sizeof(char*) * afficheur->m__lines);
    for(int i = 0; i < afficheur->m__lines; i++)
    {

        afficheur->m__data[i] = (char*) malloc(sizeof(char) * afficheur->m__cols);
        afficheur->m__data[i][0] = '\0';

    }

    afficheur->m__base = machine_new();

}


void afficheur_unload()
{

    for(int i = 0; i < afficheur->m__lines; i++)
    {

        free(afficheur->m__data[i]);

    }

    free(afficheur->m__data);

    machine_delete(afficheur->m__base);

    free(afficheur);

}


int display(const char* format, int line, ...)
{

    machine_lock(afficheur->m__base);

    int done = 1;

    va_list arg;

    if(afficheur->m__affiche)
        machine_wait(afficheur->m__base);

    afficheur->m__affiche = true;

    va_start(arg, line);
    vsprintf(afficheur->m__data[line], format, arg);
    va_end(arg),

    clear();
    for(int i = 0; i < afficheur->m__lines; i++)
    {

        printf("%.*s", afficheur->m__cols, afficheur->m__data[i]);
        printf("\n");

    }


    afficheur->m__affiche = false;

    machine_signal(afficheur->m__base);

    machine_unlock(afficheur->m__base);

    return done;

}


int display_debug(const char* format, ... )
{

    int done = 1;

    if(afficheur->m__debug)
    {
        va_list arg;

        va_start (arg, format);
        done = display(format, 0, arg);
        va_end (arg);
    }

    return done;

}


void clear()
{

    int a = system("clear");

    return;

}
