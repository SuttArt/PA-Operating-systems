#include "interface.h"

void Ausgabe (void)
{
    int j;
    printf("\n");
    for (j=0; j<DIM; j++) printf ("%4d", Ar[j]);
    printf("\n");
}