#include "bb101.h"
#include <stdbool.h>
#include <stdio.h>

int main()
{
    float hola = obtener_decimal("Dame un texto %d: ",1);
    printf("El numero es: %f\n", hola);
}
