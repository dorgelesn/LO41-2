#ifndef TYPE_H
#define TYPE_H

typedef struct
{

    int m__temps;
    int m__temps_max;

} Type;

Type* new_type(int tmps, int tmps_max);
void delete_type(Type* type);

int type_get_temps(Type* type);
int type_get_temps_max(Type* type);

#endif
