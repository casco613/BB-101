#ifndef BB101_H
#define BB101_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *string;

int obtener_entero(const string mensaje);
int obtener_entero_positivo(const string mensaje);

float obtener_decimal(const string mensaje);
double obtener_decimal_grande(const string mensaje);

bool preguntar_si_no(const string mensaje, ...)
    __attribute__((format(printf, 1, 2)));

char obtener_caracter(va_list *argumentos, const string mensaje, ...)
    __attribute__((format(printf, 2, 3)));
#define obtener_caracter(...) obtener_caracter(NULL, __VA_ARGS__)

string obtener_texto(va_list *argumentos, const string mensaje, ...)
    __attribute__((format(printf, 2, 3)));
#define obtener_texto(...) obtener_texto(NULL, __VA_ARGS__)

#endif
