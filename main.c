#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

#include "Affichage.h"
#include "Usine.h"

int main(int argc, char** argv)
{

    if(argc < 2 || argc > 3)
    {

        printf("USAGE: LO41 <file> [-debug]\n\
\
    -<file>: file containing products\n");

    }else
    {

        int pos = 1;
        int debug = 0;
        if(argc > 2)
        {

            if(!strcmp(argv[1], "-debug"))
            {

                pos = 2;
                debug = 1;

            }else if(!strcmp(argv[2], "-debug"))
            {

                pos = 1;
                debug = 1;

            }

        }

        printf("File : %s\n\n\n\n", argv[pos]);

        afficheur_init(debug);

        Usine* usine = usine_new();

        usine_start(usine);

        usine_delete(usine);

    }

    return 0;
}

