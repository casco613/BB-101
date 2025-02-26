#include <bb101.h>
#include <stdio.h>

int main()
{
    string nombre = obtener_texto("Dime tu nombre: ");
    printf("%s\n", nombre);
    int edad = obtener_entero("Mi edad es: ");
    long long dinero = obtener_entero_muy_largo("Dime que tengo ahorrado a mis %d: ", edad);
    printf("%lld\n", dinero);
}
