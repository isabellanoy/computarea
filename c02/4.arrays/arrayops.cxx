///
/// Operaciones con arreglos (array operations)
///

#include "stochastic.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

/// Constructores y destructores de arreglos

int *int_array(int n) {
  int *x = (int *) malloc(n * sizeof(int));
  for (int i = 0; i < n; ++i) {
    x[i] = 0;
  }
  return x;
}

double *double_array(int n) {
  double *x = (double *) malloc(n * sizeof(double));
  for (int i = 0; i < n; ++i) {
    x[i] = 0.0;
  }
  return x;
}

double *random_uniform_array(int n) {
  double *x = (double *) malloc(n * sizeof(double));
  for (int i = 0; i < n; ++i) {
    x[i] = uniform();
  }
  return x;
}

double *random_normal_array(int n) {
  double *x = (double *) malloc(n * sizeof(double));
  for (int i = 0; i < n; ++i) {
    x[i] = normal();
  }
  return x;
}

static const char *null = "";

const char **string_array(int n) {
  const char **x = (const char **) malloc(n * sizeof(const char *));
  for (int i = 0; i < n; ++i) {
    x[i] = null;
  }
  return x;
}

void delete_array(void *a) {
  free(a);
}

/// Operaciones de busqueda

int find_int(int k, int n, const int a[]) {
  int result = -1;
  for (int i = 0; i < n; ++i) {
    if (a[i] == k) {
      result = i;
      break;
    }
  }
  return result;
  // no hay nada que completar: este codigo esta listo ... es la definicion de papa pelada
  // SIN EMBARGO, deben leer y entender todo el codigo suministrado en la tarea para aprender!
  // borren los comentarios de tarea y ayuda ... pero no los que documentan las funciones.
}

// *** TAREA 2 pts ***
// implementar la funcion (ver encabezado)
//  .........
int find_string(const char *s, int n, const char *a[]) {
  int result = -1;
  for (int i = 0; i < n; ++i) {
    if (strcmp(a[i], s) == 0) {
      result = i;
      break;
    }
  }
  // completar el codigo, usando la funcion estandar strcmp para comparar strings
  // ya conocen strcmp, pero es buena costumbre ver documentacion en caso de dudas
  // estas fuentes son populares - aparecen entre los primeros resultados de busqueda:
  // https://devdocs.io/c/string/byte/strcmp
  // https://cplusplus.com/reference/cstring/strcmp/
  // https://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm
  // https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strcmp-wcscmp-mbscmp
  //
  // en general pueden referirse al manual de libc (libreria estandar de C); aqui esta el de GNU
  // https://www.gnu.org/software/libc/manual/pdf/libc.pdf
  //
  // por cierto: "standard means standard" todo lo que es estandar funciona igual en Unix y Windows
  return result;
}

// *** TAREA 3 pts ***
// implementar la funcion (ver encabezado)
//  .........
int find_min_int(int i, int j, const int a[]) {
  int mindx = i;
  int min = a[mindx];
  for (int k = i+1; k < j; ++k) {
    if (a[k] < min) {
      mindx = k;
      min = a[mindx];
    }
  }
  return mindx;
}

// *** TAREA 2 pts ***
// implementar la funcion (ver encabezado)
//  .........
int find_min_double(int i, int j, const double a[]) {
  int mindx = i;
  double min = a[mindx];
  for (int k = i+1; k < j; ++k) {
    if (a[k] < min) {
      mindx = k;
      min = a[mindx];
    }
  }
  return mindx;
}

// *** TAREA 2 pts ***
// implementar la funcion (ver encabezado)
//  .........
int find_min_string(int i, int j, const char *a[]) {
  int pos = i;
  const char *min = a[pos];
  for (int k = i+1; k < j; ++k) {
    if (strcmp(a[k], min) < 0) {
      pos = k;
      min = a[pos];
    }
  }
  return pos;
}

/// Operaciones para desordenar arreglos

// *** TAREA 2 pts ***
// implementar la funcion
//  .........
/// intercambia dos elementos en un arreglo de enteros
/// i: indice del primer elemento
/// j: indice del segundo elemento
/// data: arreglo de enteros
/// precondicion: 'i' y 'j' deben ser indices validos en 'data'
static void swap_int_elements(int i, int j, int data[]) {
  int tmp = data[i];
  data[i] = data[j];
  data[j] = tmp;
}

/// intercambia dos elementos en un arreglo de numeros (doble precision)
/// i: indice del primer elemento
/// j: indice del segundo elemento
/// data: arreglo de numeros en doble precision
/// precondicion: 'i' y 'j' deben ser indices validos en 'data'
static void swap_double_elements(int i, int j, double data[]) {
  double tmp = data[i];
  data[i] = data[j];
  data[j] = tmp;
}

/// intercambia dos elementos en un arreglo de numeros (doble precision)
/// hace lo mismo que swap_double_elements, usando sintaxis "de-azucarada"
/// just like swap_elements, using "desugared" syntax for teaching purposes
/// i: indice del primer elemento
/// j: indice del segundo elemento
/// data: arreglo de numeros en doble precision
/// precondicion: 'i' y 'j' deben ser indices validos en 'data'
static void swap_double_elements_desugared(int i, int j, double *data) {
  double tmp = *(data + i);
  *(data + i) = *(data + j);
  *(data + j) = tmp;
}

// *** TAREA 2 pts ***
// implementar la funcion
//  .........
/// intercambia dos elementos en un arreglo de "strings" (cadenas de caracteres)
/// i: indice del primer elemento
/// j: indice del segundo elemento
/// data: arreglo de strings
/// precondicion: 'i' y 'j' deben ser indices validos en 'data'
static void swap_string_elements(int i, int j, const char *data[]) {
  const char *tmp = data[i];
  data[i] = data[j];
  data[j] = tmp;
}

void shuffle_int_array(int n, int a[]) {
  for (int i = 0; i < n; ++i) {
    int j = random_int(i, n);
    swap_int_elements(i, j, a);
  }
}

// *** TAREA 2 pts ***
// implementar la funcion
//  .........
void shuffle_double_array(int n, double a[]) {
  for (int i = 0; i < n; ++i) {
    int j = random_int(i, n);
    swap_double_elements(i, j, a);
  }
}

// *** TAREA 2 pts ***
// implementar la funcion
//  .........
void shuffle_string_array(int n, const char *a[]) {
  for (int i = 0; i < n; ++i) {
    int j = random_int(i, n);
    swap_string_elements(i, j, a);
  }
}

/// Operaciones para ordenar arreglos

// *** TAREA 3 pts ***
// implementar la funcion (ver encabezado)
//  .........
void selection_sort_int_array(int n, int a[]) {
  for (int i = 0; i < n-1; ++i) {
    int mindx = find_min_int(i, n, a);
    swap_int_elements(i, mindx, a);
  }
}

// *** TAREA 2 pts ***
// implementar la funcion (ver encabezado)
//  .........
void selection_sort_double_array(int n, double a[]) {
  for (int i = 0; i < n-1; ++i) {
    int mindx = find_min_double(i, n, a);
    swap_double_elements(i, mindx, a);
  }
}

// *** TAREA 2 pts ***
// implementar la funcion (ver encabezado)
//  .........
void selection_sort_string_array(int n, const char *a[]) {
  for (int i = 0; i < n-1; ++i) {
    int mindx = find_min_string(i, n, a);
    swap_string_elements(i, mindx, a);
  }
}
