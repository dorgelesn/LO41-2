/*
 * Gnikwo < gnikwo AT hotmail DOT com >
 *
 * Copyright (c) 2016 Gnikwo
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction,
 * including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>

#include "Display.h"
#include "Factory.h"

Factory* factory;

void stop()
{

    factory_stop(factory);

    factory_join(factory);

    factory_delete(factory);

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

        printf("USAGE: LO41 [-debug] <products> <types> <tables>\n\
\
    -<products>: fichier contenant les products a factoryr.\
    -<types>: fichier contenant les types de products.\
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

        char* products = argv[debug+1];
        char* types = argv[debug+2];
        char* tables = argv[debug+3];

        afficheur_init(debug);

        display("Products : %s", 1, products);
        display("Types : %s", 2, types);
        display("Tables : %s", 3, tables);

        signal(SIGINT, stop_sig);

        factory = factory_new(products, types, tables);

        factory_start(factory);

        display("[Press 'Enter' to quit.]", 39);
        getchar();

        stop(0);

    }

    return 0;
}

