#include "bb101.h"

#include <float.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"

typedef char *string;

/**
 * Número de cadenas asignadas por obtener_texto.
 */
static size_t numero_asignaciones = 0;

/**
 * Arreglo de cadenas asignadas por obtener_texto.
 */
static string *strings_generados = NULL;

#undef obtener_texto
string obtener_texto(va_list *argumentos, const string mensaje, ...)
{
  // Verificar que no se exceda el número máximo de asignaciones.
  if (numero_asignaciones == SIZE_MAX / sizeof(string))
  {
    return NULL;
  }

  string buffer = NULL;
  size_t capacidad = 0;
  size_t tamano = 0;
  int caracter_actual;

  // Mostrar mensaje si se proporciona.
  if (mensaje != NULL)
  {
    va_list lista_argumentos;
    if (argumentos == NULL)
    {
      va_start(lista_argumentos, mensaje);
    }
    else
    {
      va_copy(lista_argumentos, *argumentos);
    }
    vprintf(mensaje, lista_argumentos);
    va_end(lista_argumentos);
  }

  // Leer caracteres de la entrada hasta fin de línea o EOF.
  while ((caracter_actual = fgetc(stdin)) != EOF && caracter_actual != '\n' &&
         caracter_actual != '\r')
  {

    // Asegurar espacio para el nuevo carácter y el terminador nulo.
    if (tamano + 1 >= capacidad)
    {
      size_t nueva_capacidad = (capacidad == 0) ? 16 : capacidad * 2;
      // Comprobar posible desbordamiento.
      if (nueva_capacidad <= capacidad)
      {
        free(buffer);
        return NULL;
      }
      string temp = realloc(buffer, nueva_capacidad * sizeof(char));
      if (temp == NULL)
      {
        free(buffer);
        return NULL;
      }
      buffer = temp;
      capacidad = nueva_capacidad;
    }
    buffer[tamano++] = (char)caracter_actual;
  }

  // Si no se leyó nada y se alcanzó EOF, liberar memoria y retornar NULL.
  if (tamano == 0 && caracter_actual == EOF)
  {
    free(buffer);
    return NULL;
  }

  // Si se leyó '\r', verificar si le sigue '\n' (para Windows).
  if (caracter_actual == '\r')
  {
    caracter_actual = fgetc(stdin);
    if (caracter_actual != '\n' && caracter_actual != EOF)
    {
      if (ungetc(caracter_actual, stdin) == EOF)
      {
        free(buffer);
        return NULL;
      }
    }
  }

  // Ajustar el buffer al tamaño exacto y añadir el terminador nulo.
  string string_capturado = realloc(buffer, (tamano + 1) * sizeof(char));
  if (string_capturado == NULL)
  {
    free(buffer);
    return NULL;
  }
  string_capturado[tamano] = '\0';

  // Almacenar la cadena generada en el arreglo global.
  string *tmp =
      realloc(strings_generados, (numero_asignaciones + 1) * sizeof(string));
  if (tmp == NULL)
  {
    free(string_capturado);
    return NULL;
  }
  strings_generados = tmp;
  strings_generados[numero_asignaciones++] = string_capturado;

  return string_capturado;
}

#undef obtener_caracter
char obtener_caracter(va_list *argumentos, const string mensaje, ...)
{
  va_list lista_argumentos;
  if (argumentos == NULL)
  {
    va_start(lista_argumentos, mensaje);
  }
  else
  {
    va_copy(lista_argumentos, *argumentos);
  }

  char resultado;

  while (true)
  {
    // Se obtiene una línea de texto, utilizando la función que se encarga de
    // gestionar la entrada y el mensaje (y sus argumentos variables).
    string linea = obtener_texto(&lista_argumentos, mensaje);
    if (linea == NULL)
    {
      // Si no se pudo leer la línea, se retorna CHAR_MAX para indicar fallo.
      resultado = CHAR_MAX;
      break;
    }

    // Se intenta extraer exactamente un carácter de la línea.
    // El espacio en el formato " %c %c" descarta los espacios en blanco.
    char primer, extra;
    if (sscanf(linea, " %c %c", &primer, &extra) == 1)
    {
      resultado = primer;
      break;
    }
    // Si no se obtuvo exactamente un carácter, se repite el ciclo para volver a
    // pedir el ingreso al usuario.
  }

  va_end(lista_argumentos);
  return resultado;
}

bool preguntar_si_no(const string mensaje, ...)
{
  va_list lista_argumentos;
  va_start(lista_argumentos, mensaje);
  bool respuesta;
  while (true)
  {
    char caracter = obtener_caracter(&lista_argumentos, mensaje);

    if (caracter == 's' || caracter == 'S')
      respuesta = true;
    if (caracter == 'n' || caracter == 'N')
      respuesta = false;
  }

  va_end(lista_argumentos);
  return respuesta;
}

#undef obtener_entero
int obtener_entero(va_list *argumentos, const string mensaje, ...)
{

  va_list lista_argumentos;
  if (argumentos == NULL)
  {
    va_start(lista_argumentos, mensaje);
  }
  else
  {
    va_copy(lista_argumentos, *argumentos);
  }

  int resultado;

  while (true)
  {
    // Se obtiene una línea de texto, utilizando la función que se encarga de
    // gestionar la entrada y el mensaje (y sus argumentos variables).
    string linea = obtener_texto(&lista_argumentos, mensaje);
    if (linea == NULL)
    {
      // Si no se pudo leer la línea, se retorna INT_MAX para indicar fallo.
      resultado = INT_MAX;
      break;
    }

    // Se intenta extraer exactamente un entero de la línea.
    // El espacio en el formato " %d %c" descarta los espacios en blanco.
    int primer;
    char extra;
    if (sscanf(linea, " %d %c", &primer, &extra) == 1)
    {
      resultado = primer;
      break;
    }
    // Si no se obtuvo exactamente un entero, se repite el ciclo para volver a
    // pedir el ingreso al usuario.
  }

  va_end(lista_argumentos);
  return resultado;
}

int obtener_entero_positivo(const string mensaje, ...)
{
  va_list lista_argumentos;
  va_start(lista_argumentos, mensaje);
  int resultado;
  while (true)
  {
    int entero = obtener_entero(&lista_argumentos, mensaje);
    if (entero >= 0)
    {
      resultado = entero;
      break;
    }
  }

  va_end(lista_argumentos);
  return resultado;
}

float obtener_decimal(const string mensaje, ...)
{
  va_list lista_argumentos;
  va_start(lista_argumentos, mensaje);
  float resultado;
  while (true)
  {
    // Se obtiene una línea de texto, utilizando la función que se encarga de
    // gestionar la entrada y el mensaje (y sus argumentos variables).
    string linea = obtener_texto(&lista_argumentos, mensaje);
    if (linea == NULL)
    {
      // Si no se pudo leer la línea, se retorna FLT_MAX para indicar fallo.
      resultado = FLT_MAX;
      break;
    }

    // Se intenta extraer exactamente un número de punto flotante de la línea.
    // El espacio en el formato " %f %c" descarta los espacios en blanco.
    float primer;
    char extra;
    if (sscanf(linea, " %f %c", &primer, &extra) == 1)
    {
      resultado = primer;
      break;
    }
    // Si no se obtuvo exactamente un número de punto flotante, se repite el
    // ciclo para volver a pedir el ingreso al usuario.
  }

  va_end(lista_argumentos);
  return resultado;
}

double obtener_decimal_grande(const string mensaje, ...)
{
  va_list lista_argumentos;
  va_start(lista_argumentos, mensaje);
  double resultado;
  while (true)
  {
    // Se obtiene una línea de texto, utilizando la función que se encarga de
    // gestionar la entrada y el mensaje (y sus argumentos variables).
    string linea = obtener_texto(&lista_argumentos, mensaje);
    if (linea == NULL)
    {
      // Si no se pudo leer la línea, se retorna DBL_MAX para indicar fallo.
      resultado = DBL_MAX;
      break;
    }

    // Se intenta extraer exactamente un número de punto flotante de doble
    // precisión de la línea. El espacio en el formato " %lf %c" descarta los
    // espacios en blanco.
    double primer;
    char extra;
    if (sscanf(linea, " %lf %c", &primer, &extra) == 1)
    {
      resultado = primer;
      break;
    }
    // Si no se obtuvo exactamente un número de punto flotante de doble
    // precisión, se repite el ciclo para volver a pedir el ingreso al usuario.
  }

  va_end(lista_argumentos);
  return resultado;
}

long obtener_entero_largo(const string mensaje, ...)
{
  va_list lista_argumentos;
  va_start(lista_argumentos, mensaje);
  long resultado;
  while (true)
  {
    // Se obtiene una línea de texto, utilizando la función que se encarga de
    // gestionar la entrada y el mensaje (y sus argumentos variables).
    string linea = obtener_texto(&lista_argumentos, mensaje);
    if (linea == NULL)
    {
      // Si no se pudo leer la línea, se retorna LONG_MAX para indicar fallo.
      resultado = LONG_MAX;
      break;
    }

    // Se intenta extraer exactamente un entero largo de la línea.
    // El espacio en el formato " %ld %c" descarta los espacios en blanco.
    long primer;
    char extra;
    if (sscanf(linea, " %ld %c", &primer, &extra) == 1)
    {
      resultado = primer;
      break;
    }
    // Si no se obtuvo exactamente un entero largo, se repite el ciclo para
    // volver a pedir el ingreso al usuario.
  }

  va_end(lista_argumentos);
  return resultado;
}

long long obtener_entero_muy_largo(const string mensaje, ...)
{
  va_list lista_argumentos;
  va_start(lista_argumentos, mensaje);
  long long resultado;
  while (true)
  {
    // Se obtiene una línea de texto, utilizando la función que se encarga de
    // gestionar la entrada y el mensaje (y sus argumentos variables).
    string linea = obtener_texto(&lista_argumentos, mensaje);
    if (linea == NULL)
    {
      // Si no se pudo leer la línea, se retorna LLONG_MAX para indicar fallo.
      resultado = LLONG_MAX;
      break;
    }

    // Se intenta extraer exactamente un entero muy largo de la línea.
    // El espacio en el formato " %lld %c" descarta los espacios en blanco.
    long long primer;
    char extra;
    if (sscanf(linea, " %lld %c", &primer, &extra) == 1)
    {
      resultado = primer;
      break;
    }
    // Si no se obtuvo exactamente un entero muy largo, se repite el ciclo para
    // volver a pedir el ingreso al usuario.
  }

  va_end(lista_argumentos);
  return resultado;
}

static void desmantelamiento(void)
{
  if (strings_generados != NULL)
  {
    for (size_t i = 0; i < numero_asignaciones; i++)
    {
      free(strings_generados[i]);
    }
    free(strings_generados);
  }
}

// Función de inicialización.
int INITIALIZER()
{
  setvbuf(stdout, NULL, _IONBF, 0);
  atexit(desmantelamiento);
  return 0;
}
