#include "bb101.h"
#include <stdbool.h>
#include <stdio.h>

int main()
{
    long long hola = obtener_entero_muy_largo("Dame un texto %d: ",1);
    printf("El numero es: %lld\n", hola);
}
