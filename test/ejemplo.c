#include "bb101.h"
#include <stdbool.h>
#include <stdio.h>

int main()
{
    int hola = obtener_entero_positivo("Dame un texto %d: ",1);
    printf("El entero es: %d\n", hola);
}
