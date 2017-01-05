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

        printf("USAGE: LO41 [-debug] <products>\n\
\
    -<products>: product number to give to the factory.\n");

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

        int products = atoi(argv[debug+1]);
        int types = 1;
        int tables = 3;

        afficheur_init(debug);

        display("Products : %i", 1, products);
        display("Types : %i", 2, types);
        display("Tables : %i", 3, tables);

        signal(SIGINT, stop_sig);

        factory = factory_new(products, types, tables);

        factory_start(factory);

        display("[Press 'Enter' to quit.]", 39);
        getchar();

        stop();

    }

    return 0;
}

