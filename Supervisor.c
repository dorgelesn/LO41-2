#include "Supervisor.h"

#include <stdio.h>
#include <stdlib.h>

#include "Display.h"

Supervisor* supervisor_new(char* products, char* types, char* tables)
{

    display_debug("[Supervisor]: constructor\n");

    Supervisor* s = malloc(sizeof(Supervisor));


    s->m__base = machine_new();

    supervisor_import_types(s, types);
    supervisor_import_products(s, products);
    supervisor_import_tables(s, tables);

    Retrait* retrait = retrait_new();
    Conveyor* conveyor = conveyor_new(retrait, s->m__tables, s->m__num_tables);
    Supplier* alim = supplier_new(conveyor, s->m__products);

    s->m__supplier = alim;
    s->m__conveyor = conveyor;
    s->m__retrait = retrait;

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

    for(int i = 0; i < supervisor->m__num_types; i++)
        type_delete(supervisor->m__types[i]);
    free(supervisor->m__types);

    for(int i = 0; i < supervisor->m__num_tables; i++)
        table_delete(supervisor->m__tables[i]);
    free(supervisor->m__tables);

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


void* supervisor_thread(void* args)
{

    display_debug("[Supervisor]: ==supervisor_start==\n");

    Supervisor* supervisor = (Supervisor*) args;

    while(!machine_get_should_stop(supervisor->m__base))
    {

        for(int i = 0; i < supervisor->m__num_types; i++)
        {

            display("Type : %p", 5+i, supervisor->m__types[i]);

        }
        for(int i = 0; i < supervisor->m__num_tables; i++)
        {

            display("Table : %p", 8+i, supervisor->m__tables[i]);

        }
        for(int i = 0; i < supervisor->m__num_products; i++)
        {

            display("Product : %p", 12+i, supervisor->m__products[i]);

        }
        sleep(1);

    }

    return 0;

}


void supervisor_import_products(Supervisor* supervisor, char* fichier_products)
{

    supervisor->m__num_products = 3;
    supervisor->m__products = (Product**) malloc(sizeof(Product*) * supervisor->m__num_products);

    supervisor->m__products[0] = product_new(supervisor->m__types[0]);
    supervisor->m__products[1] = product_new(supervisor->m__types[0]);
    supervisor->m__products[2] = product_new(supervisor->m__types[0]);

}


void supervisor_import_types(Supervisor* supervisor, char* fichier_types)
{

    supervisor->m__num_types = 1;
    supervisor->m__types = (Type**) malloc(sizeof(Type*) * supervisor->m__num_types);

    supervisor->m__types[0] = type_new(10, 30);

}


void supervisor_import_tables(Supervisor* supervisor, char* fichier_tables)
{

    supervisor->m__num_tables = 3;

    supervisor->m__tables = (Table**) malloc(sizeof(Table*) * supervisor->m__num_tables);

    supervisor->m__tables[0] = table_new(supervisor->m__types);
    supervisor->m__tables[1] = table_new(supervisor->m__types);
    supervisor->m__tables[2] = table_new(supervisor->m__types);

}
