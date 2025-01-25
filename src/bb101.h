#ifndef BB101_H
#define BB101_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

string obtener_texto(const string msg);
int obtener_entero(const string msg); 
float obtener_decimal(const string msg);
double obtener_decimal_grande(const string msg);

#endif 