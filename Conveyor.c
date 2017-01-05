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


#include "Conveyor.h"

#include <stdio.h>
#include <stdlib.h>

#include "Display.h"
#include "Supplier.h"
#include "Supervisor.h"

Conveyor* conveyor_new(void* supervisor, Retrait* retrait, Table** tables, int num_tables)
{

    display_debug("[Conveyor]: constructor\n");

    Conveyor* c = malloc(sizeof(Conveyor));

    c->m__base = machine_new();
    c->m__supervisor = supervisor;

    c->m__retrait = retrait;
    c->m__tables = tables;
    c->m__num_tables = num_tables;

    c->m__product = NULL;
    c->m__position = 0;

    return c;

}


void conveyor_delete(Conveyor* conveyor)
{

    display_debug("[Conveyor]: destructor\n");

    machine_delete(conveyor->m__base);

    free(conveyor);

}


int conveyor_start(Conveyor* conveyor)
{

    return machine_start(conveyor->m__base, &conveyor_thread, conveyor);

}


int conveyor_join(Conveyor* conveyor)
{

    display_debug("[Conveyor]: ==conveyor_thread_join==\n");
    int res = machine_join(conveyor->m__base);

    display_debug("[Conveyor]: ==conveyor_thread_join_2==\n");

    return res;

}


int conveyor_stop(Conveyor* conveyor)
{

    display_debug("[Conveyor]: ==conveyor_thread_stop==\n");
    return machine_stop(conveyor->m__base);

}


void conveyor_wake(Conveyor* supplier){

    machine_wake(supplier->m__base);
    return;

}


void* conveyor_thread(void* args)
{

    display_debug("[Conveyor]: ==conveyor_thread==\n");

    Conveyor* conveyor = (Conveyor*) args;

    while(!machine_get_should_stop(conveyor->m__base))
    {

        sleep(1);
        machine_lock(conveyor->m__base);
        {

            if(!conveyor->m__product)
                machine_sleep(conveyor->m__base);

        }
        machine_unlock(conveyor->m__base);

        if(!machine_get_should_stop(conveyor->m__base))
        {

            if(product_treated(conveyor->m__product))
            {

                conveyor_give_product_retrait(conveyor);

            }else
            {

                if(conveyor->m__position >= conveyor->m__num_tables)
                {

                    conveyor->m__position = 0;

                }

                if(!table_get_product(conveyor->m__tables[conveyor->m__position]) && (table_get_type(conveyor->m__tables[conveyor->m__position]) == product_get_type(conveyor->m__product)))
                {

                    conveyor_give_product_table(conveyor, conveyor->m__tables[conveyor->m__position]);

                }else
                {

                    conveyor->m__position++;

                }

            }

        }

    }

    pthread_exit(NULL);

    return 0;

}


void conveyor_receive_product_supplier(Conveyor* conveyor, void* supplier, Product* product)
{

    display_debug("[Conveyor]: conveyor_receive_product_supplier\n");

    Supplier* s = (Supplier*) supplier;

    machine_lock(conveyor->m__base);
    {

        if(conveyor->m__product)
            machine_wait_receive(conveyor->m__base);

    }
    machine_unlock(conveyor->m__base);

    if(!machine_get_should_stop(s->m__base))
    {

        conveyor->m__position = 0;
        conveyor->m__product = product;

        supervisor_wake(conveyor->m__supervisor);
        machine_wake(conveyor->m__base);

    }


}


void conveyor_receive_product_table(Conveyor* conveyor, Table* table, Product* product)
{

    machine_lock(conveyor->m__base);
    {

        if(conveyor->m__product)
            machine_wait_receive(conveyor->m__base);

    }
    machine_unlock(conveyor->m__base);

    int i = 0;
    bool found_table = false;
    while(!found_table)
    {

        if(conveyor->m__tables[i] == table)
        {

            found_table = true;

        }else
        {

            i++;

        }

    }

    conveyor->m__position = i + 1;
    conveyor->m__product = product;

    machine_wake(conveyor->m__base);


}


void conveyor_give_product_table(Conveyor* conveyor, Table* table)
{

    table_receive_product_conveyor(table, conveyor, conveyor->m__product);
    conveyor->m__product = NULL;
    machine_signal_receive(conveyor->m__base);

}


void conveyor_give_product_retrait(Conveyor* conveyor)
{

    retrait_receive_product_conveyor(conveyor->m__retrait, conveyor, conveyor->m__product);
    conveyor->m__product = NULL;

    machine_signal_receive(conveyor->m__base);

}

int conveyor_position_max(Conveyor* conveyor)
{

    return conveyor->m__num_tables + 2;

}


Product* conveyor_get_product(Conveyor* conveyor)
{

    return conveyor->m__product;

}


void conveyor_display(Conveyor* conveyor, int* line)
{

    *(line) = *(line) + 1;

    display("Conveyor: Position: %i; Product:%p", *line, conveyor->m__position, conveyor->m__product);

}
