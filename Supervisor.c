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


#include "Supervisor.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Display.h"

Supervisor* supervisor_new(int num_products, int num_types, int num_tables)
{

    display_debug("[Supervisor]: constructor\n");

    srand(time(NULL));

    Supervisor* s = malloc(sizeof(Supervisor));

    s->m__base = machine_new();

    supervisor_import_types(s, num_types);
    supervisor_import_products(s, num_products);
    supervisor_import_tables(s, num_tables);

    Retrait* retrait = retrait_new(s);
    Conveyor* conveyor = conveyor_new(s, retrait, s->m__tables, s->m__num_tables);
    Supplier* alim = supplier_new(conveyor);

    s->m__supplier = alim;
    s->m__conveyor = conveyor;
    s->m__retrait = retrait;

    s->m__num_finished = 0;


    return s;

}


void supervisor_delete(Supervisor* supervisor)
{

    display_debug("[Supervisor]: destructor\n");

    supplier_delete(supervisor->m__supplier);
    conveyor_delete(supervisor->m__conveyor);
    retrait_delete(supervisor->m__retrait);

    for(int i = 0; i < supervisor->m__num_products; i++)
        product_delete(supervisor->m__products[i]);
    free(supervisor->m__products);

    for(int i = 0; i < supervisor->m__num_tables; i++)
        table_delete(supervisor->m__tables[i]);
    free(supervisor->m__tables);

    for(int i = 0; i < supervisor->m__num_types; i++)
        type_delete(supervisor->m__types[i]);
    free(supervisor->m__types);

    machine_delete(supervisor->m__base);

    free(supervisor);

}


int supervisor_start(Supervisor* supervisor)
{

    if(conveyor_start(supervisor->m__conveyor))
        return 1;

    if(supplier_start(supervisor->m__supplier))
        return 1;

    if(retrait_start(supervisor->m__retrait))
        return 1;

    for(int i = 0; i < supervisor->m__num_tables; i++)
    {

        if(table_start(supervisor->m__tables[i]))
            return 1;

    }

    return machine_start(supervisor->m__base, &supervisor_thread, supervisor);

}


int supervisor_join(Supervisor* supervisor)
{

    display_debug("[Supervisor]: ==supervisor_thread_join==\n");

    if(conveyor_join(supervisor->m__conveyor))
        return 1;

    if(supplier_join(supervisor->m__supplier))
        return 1;

    if(retrait_join(supervisor->m__retrait))
        return 1;

    for(int i = 0; i < supervisor->m__num_tables; i++)
    {

        if(table_join(supervisor->m__tables[i]))
            return 1;

    }

    return machine_join(supervisor->m__base);

}


int supervisor_stop(Supervisor* supervisor)
{

    display_debug("[Supervisor]: ==supervisor_thread_stop==\n");

    if(conveyor_stop(supervisor->m__conveyor))
        return 1;

    if(supplier_stop(supervisor->m__supplier))
        return 1;

    if(retrait_stop(supervisor->m__retrait))
        return 1;

    for(int i = 0; i < supervisor->m__num_tables; i++)
    {

        if(table_stop(supervisor->m__tables[i]))
            return 1;

    }

    return machine_stop(supervisor->m__base);

}


void supervisor_wake(void* supervisor)
{

    Supervisor* s = (Supervisor*) supervisor;

    machine_wake(s->m__base);

    return;

}


void* supervisor_thread(void* args)
{

    display_debug("[Supervisor]: ==supervisor_start==\n");

    Supervisor* supervisor = (Supervisor*) args;

    while(!machine_get_should_stop(supervisor->m__base))
    {

        if(supervisor->m__current_product < supervisor->m__num_products)
        {

            Type* current_type = product_get_type(supervisor->m__products[supervisor->m__current_product]);

            bool found = false;
            int found_products = 0;// number of product of the same type as the current product, that are in proccess
            int found_tables = 0;
            int i = 0;

            if(supplier_get_product(supervisor->m__supplier))
            {

                found_products++;

            }

            if(conveyor_get_product(supervisor->m__conveyor))
            {

                found_products++;

            }

            while(i < supervisor->m__num_tables && !found)
            {

                if(table_get_type(supervisor->m__tables[i]) == current_type)
                {

                    found_tables++;

                    if(table_get_product(supervisor->m__tables[i]))
                    {

                        found_products++;

                    }

                }

                if(found_products < found_tables)
                {

                    found = true;

                }else
                {

                    i++;

                }

            }

            if(found)
            {

                supervisor_give_product_supplier(supervisor, supervisor->m__products[supervisor->m__current_product]);

                supervisor->m__current_product++;

            }

        }

        int line = 0;

        clean();

        supervisor_display(supervisor, &line);
        supplier_display(supervisor->m__supplier, &line);
        conveyor_display(supervisor->m__conveyor, &line);

        line++;
        display("Tables : ", line);
        for(int i = 0; i < supervisor->m__num_tables; i++)
        {

            line++;

            table_display(supervisor->m__tables[i], &line);

        }

        if(supervisor_finished(supervisor))
        {

            display("[Supervisor]: ALL PRODUCTS HAVE BEEN PROCESSED !", 39);
            pthread_exit(0);

        }

        //machine_sleep(supervisor->m__base);
        sleep(1);

    }

    pthread_exit(0);

    return 0;

}


void supervisor_give_product_supplier(Supervisor* supervisor, Product* product)
{

    supplier_receive_product_supervisor(supervisor->m__supplier, product);

}



void supervisor_import_products(Supervisor* supervisor, int num_products)
{

    supervisor->m__num_products = num_products;
    supervisor->m__current_product = 0;

    supervisor->m__products = (Product**) malloc(sizeof(Product*) * supervisor->m__num_products);

    for(int i = 0; i < supervisor->m__num_products; i++)
    {

        supervisor->m__products[i] = product_new(supervisor->m__types[rand()%supervisor->m__num_types]);

    }

}


void supervisor_import_types(Supervisor* supervisor, int num_types)
{

    supervisor->m__num_types = num_types;
    supervisor->m__types = (Type**) malloc(sizeof(Type*) * supervisor->m__num_types);

    for(int i = 0; i < supervisor->m__num_types; i++)
    {

        supervisor->m__types[i] = type_new(3, 30);

    }

}


void supervisor_import_tables(Supervisor* supervisor, int num_tables)
{

    supervisor->m__num_tables = num_tables;

    supervisor->m__tables = (Table**) malloc(sizeof(Table*) * supervisor->m__num_tables);

    for(int i = 0; i < supervisor->m__num_tables; i++)
    {

        supervisor->m__tables[i] = table_new(supervisor->m__types[rand()%supervisor->m__num_types]);

    }

}


void supervisor_product_finished(Supervisor* supervisor)
{

    supervisor->m__num_finished++;

}


bool supervisor_finished(Supervisor* supervisor)
{

    bool res = supervisor->m__num_finished == supervisor->m__num_products;

    return res;

}


void supervisor_display(Supervisor* supervisor, int* line)
{

    *(line) = *(line) + 1;

    display("Supervisor: ", *(line));
    *(line) = *(line) + 1;
    display("   current : %i", *(line), supervisor->m__current_product);

    for(int i = 0; i < supervisor->m__num_products; i++)
    {

        product_display(supervisor->m__products[i], line);

    }

    *(line) = *(line) + 1;

}
