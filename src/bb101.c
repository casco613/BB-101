#include "bb101.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef char* string;

string obtener_texto(const string msg){
    puts(msg);
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return NULL; 
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    char* text = malloc(strlen(buffer) + 1); 
    if (text != NULL){
        strcpy(text, buffer);
    }
    return text; 
}

int obtener_entero(const string msg){
    puts(msg); 
    int value; 
    scanf("%d", &value);
    return value; 
}
float obtener_decimal(const string msg){
    puts(msg);
    float value;
    scanf("%f", &value);
    return value; 
}
double obtener_decimal_grande(const string msg){
    puts(msg);
    double value; 
    scanf("%lf", &value);
    return value; 
}
