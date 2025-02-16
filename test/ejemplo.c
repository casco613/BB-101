#include "bb101.h"
#include <stdbool.h>
#include <stdio.h>

int main()
{
    long hola = obtener_entero_largo("Dame un texto %d: ",1);
    printf("El numero es: %ld\n", hola);
}
