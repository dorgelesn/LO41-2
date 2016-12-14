#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>

#include "Affichage.h"
#include "Usine.h"

Usine* usine;

void stop()
{

    usine_stop(usine);

    usine_join(usine);

    usine_delete(usine);

    afficheur_unload();

    return;

}


void stop_sig(int signal)
{

    stop();

    exit(0);

}


int main(int argc, char** argv)
{

    if(argc < 4 || argc > 5)
    {

        printf("USAGE: LO41 [-debug] <produits> <types> <tables>\n\
\
    -<produits>: fichier contenant les produits a usiner.\
    -<types>: fichier contenant les types de produits.\
    -<tables>: fichier contenant les tables d'usinage.\n");

    }else
    {

        int debug = 0;
        if(argc > 4)
        {

            if(!strcmp(argv[1], "-debug"))
            {
                debug = 1;
            }

        }

        char* produits = argv[debug+1];
        char* types = argv[debug+2];
        char* tables = argv[debug+3];

        afficheur_init(debug);

        afficher("Produits : %s", 1, produits);
        afficher("Types : %s", 2, types);
        afficher("Tables : %s", 3, tables);

        signal(SIGINT, stop_sig);

        usine = usine_new(produits, types, tables);

        usine_start(usine);

        afficher("[Press 'Enter' to quit.]", 39);
        getchar();

        stop(0);

    }

    return 0;
}

