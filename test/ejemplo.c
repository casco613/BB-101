#include "bb101.h"
#include <stdbool.h>
#include <stdio.h>

int main()
{
    double hola = obtener_decimal_grande("Dame un texto %d: ",1);
    printf("El numero es: %f\n", hola);
}
