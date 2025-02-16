#include "bb101.h"
#include <stdbool.h>
#include <stdio.h>

int main()
{
    bool hola = preguntar_si_no("Dame un texto %d: ",1);
    if(hola){
	printf("%s", "SI");
    }else {
	printf("%s", "NO");
    }
}
