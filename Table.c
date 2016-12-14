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


#include "Table.h"

#include <stdio.h>
#include <stdlib.h>

#include "Display.h"

#include "Conveyor.h"

Table* table_new(Type** types)
{

    display_debug("[Table]: constructor\n");

    Table* t = malloc(sizeof(Table));

    t->m__base = machine_new();

    t->m__product = NULL;
    t->m__types = types;

    return t;

}


void table_delete(Table* table)
{

    display_debug("[Table]: desctructor\n");

    machine_delete(table->m__base);
    free(table);

}


int table_start(Table* table)
{

    return machine_start(table->m__base, &table_thread, table);

}


int table_join(Table* table)
{

    display_debug("[Table]: ==table_thread_join==\n");
    return machine_join(table->m__base);

}


int table_stop(Table* table)
{

    display_debug("[Table]: ==table_thread_stop==\n");
    return machine_stop(table->m__base);

}


void table_wake(Table* table)
{

    display_debug("[Table]: ==table_thread_wake==\n");
    machine_wake(table->m__base);
    return;

}


void* table_thread(void* args)
{

    display_debug("[Table]: ==table_thread==\n");

    Table* table = (Table*) args;

    while(!machine_get_should_stop(table->m__base))
    {

        machine_lock(table->m__base);
        {

            //Sleep
            machine_sleep(table->m__base);

        }
        machine_unlock(table->m__base);

    }

    return 0;

}


void table_receive_product_conveyor(Table* table, void* conveyor, Product* product)
{

    machine_lock(table->m__base);

    if(table->m__product)
        machine_wait(table->m__base);

    table->m__product = product;

    machine_signal(table->m__base);

    machine_unlock(table->m__base);

}


void table_donner_product_conveyor(Table* table, void* conveyor)
{

    conveyor_receive_product_table((Conveyor*)conveyor, table, table->m__product);
    table->m__product = NULL;

}


Product* table_get_product(Table* table)
{

    return table->m__product;

}

