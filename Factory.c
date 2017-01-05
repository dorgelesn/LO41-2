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


#include "Factory.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "Display.h"

Factory* factory_new(int num_products, int num_types, int num_tables)
{

    display_debug("[Factory]: constructor\n");

    Factory* u = malloc(sizeof(Factory));

    u->m__supervisor = supervisor_new(num_products, num_types, num_tables);

    return u;

}


void factory_delete(Factory* factory)
{

    display_debug("[Factory]: destructor\n");

    supervisor_delete(factory->m__supervisor);

    free(factory);

}

int factory_start(Factory* factory)
{

    display_debug("[Factory] : ==factory_start==\n");

    return supervisor_start(factory->m__supervisor);

}


int factory_join(Factory* factory)
{

    display_debug("[Factory]: ==factory_join==\n");
    return supervisor_join(factory->m__supervisor);

}


int factory_stop(Factory* factory)
{

    display_debug("[Factory]: ==factory_stop==\n");
    return supervisor_stop(factory->m__supervisor);

}

