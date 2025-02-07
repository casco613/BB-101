#include "bb101.h"

int main(){
    string c = obtener_texto("Dame un texto");
    printf("INPUT:%s \n", c);
    float valor = obtener_decimal("Dame un núemro");
    printf("%f\n", valor);
    return 0 ; 
}
