/**
 * @file bb101.h
 * @brief Archivo de cabecera para el proyecto BB-101 que contiene declaraciones de funciones para varias operaciones de entrada.
 *
 * Este archivo contiene las declaraciones de funciones utilizadas para obtener diferentes tipos de entrada del usuario,
 * incluyendo enteros, números de punto flotante, caracteres y cadenas. También incluye una función para preguntar
 * al usuario con una pregunta de sí/no.
 */

#ifndef BB101_H
#define BB101_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @typedef string
 * @brief Alias para char* para representar cadenas.
 */
typedef char *string;

/**
 * @brief Obtiene un entero del usuario.
 *
 * @param argumentos va_list opcional de argumentos para el formato del mensaje.
 * @param mensaje El mensaje para mostrar al usuario.
 * @param ... Argumentos adicionales para el formato del mensaje.
 * @return El entero ingresado por el usuario.
 */
int obtener_entero(va_list *argumentos, const string mensaje, ...)
    __attribute__((format(printf, 2, 3)));
#define obtener_entero(...) obtener_entero(NULL, __VA_ARGS__)

/**
 * @brief Obtiene un entero positivo del usuario.
 *
 * @param mensaje El mensaje para mostrar al usuario.
 * @param ... Argumentos adicionales para el formato del mensaje.
 * @return El entero positivo ingresado por el usuario.
 */
int obtener_entero_positivo(const string mensaje, ...)
    __attribute__((format(printf, 1, 2)));

/**
 * @brief Obtiene un número de punto flotante del usuario.
 *
 * @param mensaje El mensaje para mostrar al usuario.
 * @param ... Argumentos adicionales para el formato del mensaje.
 * @return El número de punto flotante ingresado por el usuario.
 */
float obtener_decimal(const string mensaje, ...)
    __attribute__((format(printf, 1, 2)));

/**
 * @brief Obtiene un número de punto flotante de doble precisión del usuario.
 *
 * @param mensaje El mensaje para mostrar al usuario.
 * @param ... Argumentos adicionales para el formato del mensaje.
 * @return El número de punto flotante de doble precisión ingresado por el usuario.
 */
double obtener_decimal_grande(const string mensaje, ...)
    __attribute__((format(printf, 1, 2)));

/**
 * @brief Obtiene un entero largo del usuario.
 *
 * @param mensaje El mensaje para mostrar al usuario.
 * @param ... Argumentos adicionales para el formato del mensaje.
 * @return El entero largo ingresado por el usuario.
 */
long obtener_entero_largo(const string mensaje, ...)
    __attribute__((format(printf, 1, 2)));

/**
 * @brief Pregunta al usuario con una pregunta de sí/no.
 *
 * @param mensaje El mensaje para mostrar al usuario.
 * @param ... Argumentos adicionales para el formato del mensaje.
 * @return true si el usuario responde que sí, false en caso contrario.
 */
bool preguntar_si_no(const string mensaje, ...)
    __attribute__((format(printf, 1, 2)));

/**
 * @brief Obtiene un carácter del usuario.
 *
 * @param argumentos va_list opcional de argumentos para el formato del mensaje.
 * @param mensaje El mensaje para mostrar al usuario.
 * @param ... Argumentos adicionales para el formato del mensaje.
 * @return El carácter ingresado por el usuario.
 */
char obtener_caracter(va_list *argumentos, const string mensaje, ...)
    __attribute__((format(printf, 2, 3)));
#define obtener_caracter(...) obtener_caracter(NULL, __VA_ARGS__)

/**
 * @brief Obtiene una cadena del usuario.
 *
 * @param argumentos va_list opcional de argumentos para el formato del mensaje.
 * @param mensaje El mensaje para mostrar al usuario.
 * @param ... Argumentos adicionales para el formato del mensaje.
 * @return La cadena ingresada por el usuario.
 */
string obtener_texto(va_list *argumentos, const string mensaje, ...)
    __attribute__((format(printf, 2, 3)));
#define obtener_texto(...) obtener_texto(NULL, __VA_ARGS__)

#endif