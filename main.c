#include <stdio.h>
#include <stdlib.h>

#include "Usine.h"

int main(int argc, char** argv)
{

    if(argc > 1)
    {

        printf("USAGE: LO41\n");

    }else
    {

        Usine* usine = new_usine();

        start_usine(usine);

        delete_usine(usine);

    }

    return 0;
}

