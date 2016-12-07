#ifndef TYPE_H
#define TYPE_H

typedef struct
{

    int m__temps;
    int m__temps_max;

} Type;

Type* type_new(int tmps, int tmps_max);
void type_delete(Type* type);

int type_get_temps(Type* type);
int type_get_temps_max(Type* type);

#endif
