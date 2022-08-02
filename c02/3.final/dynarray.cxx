///
/// dynamic array operations
///

#include "dynarray.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/// Nuestro glorioso arreglo dinamico (dynarray: dynamic array)
///
/// Es un triple:
/// data: apuntador al arreglo que contiene los datos
/// size: tamaño de los datos, es decir el numero de elementos en la data
/// capacity: la capacidad total del arreglo
/// 
/// La capacidad es el numero maximo de elementos que el dynarray puede contener ...
/// ... sin requerir una nueva reservacion de memoria para la data.
///
/// La diferencia (capacity - size) es la holgura del arreglo de data
/// Otra forma de verlo es que corresponde a la cantidad de "basura" :-)
///
/// Los campos de esta estructura no son directamente visibles
/// El encabezado solo declara 'struct Dynarray' sin revelar su estructura!
///
/// Esto (casi) garantiza que el usuario no puede corromper la implementacion
///
/// Todo lo que el cliente de la libreria (usuario) necesita esta provisto en la interfaz

struct Dynarray {
  double *data;
  size_t size;
  size_t capacity;
};

Dynarray *dynarray(size_t N, Initializer init) {
  Dynarray *dyna = (Dynarray *) malloc(sizeof(Dynarray));
  dyna->size = N;
  dyna->capacity = N;
  dyna->data = (double *) malloc(dyna->capacity * sizeof(double));
  for (size_t i = 0; i < dyna->size; ++i) {
    dyna->data[i] = init(i);
  }
  return dyna;
}

void dyna_destroy(Dynarray **dynarray) {
  // ... implementar
  // liberar las areas de memoria reservadas por malloc
  // ademas, la ultima instruccion debe anular el dynarray mismo
  // la idea es evitar que el usuario se refiera a memoria liberada
}

double dyna_val(size_t i, const Dynarray *dyna) {
  /// size_t es siempre >= 0, por lo tanto solo es posible violar el limite superior
  if (dyna->size <= i) {
    fprintf(stderr, "indice %zu fuera de rango [0-%zu)\n", i, dyna->size);
    // el cliente fue advertido, pero aun tenemos que regresar un double
    return nan("out of range");
  }
  return dyna->data[i];
}

void dyna_assign(size_t i, Dynarray *dyna, double val) {
  /// size_t es siempre >= 0, por lo tanto solo es posible violar el limite superior
  if (dyna->size <= i) {
    fprintf(stderr, "indice %zu fuera de rango [0-%zu)\n", i, dyna->size);
    // el cliente fue advertido; ahora podemos regresar sin hacer nada
    return;
  }
  dyna->data[i] = val;
}

/// advertencia: esto permite que el usuario tenga acceso a los datos sin chequeos
/// pero: 1) es mas eficiente y 2) el valor retornado permite usar la notacion a[i]
const double *dyna_data(const Dynarray *dyna) {
  return dyna->data;
}

size_t dyna_capacity(const Dynarray *dyna) {
  return dyna->capacity;
}

size_t dyna_size(const Dynarray *dyna) {
  return dyna->size;
}

void dyna_insert(Dynarray *dyna, int pos, int N, Initializer init) {
  // ... implementar
}

void dyna_remove(Dynarray *dyna, int pos, int N) {
  // ... implementar
}

void dyna_sort(Dynarray *dyna) {
  // ... implementar
}

Dynarray *dyna_concatenate(const Dynarray *dyna1, const Dynarray *dyna2) {

  // eliminen este mensaje: SIEMPRE deben eliminar trazas como esta al completar
  // igual para trazas de "debugging", a menos que sean "guardadas" por condicionales
  fprintf(stderr, "WARNING: dyna_concatenate: not implemented\n");

  size_t S1 = dyna1->size;
  size_t S2 = dyna2->size;
  Dynarray *result = (Dynarray *) malloc(sizeof(Dynarray));
  result->size = 0; // <<< cambiar y completar
  result->capacity = 0; // <<< cambiar y completar
  result->data = nullptr; // <<< cambiar y completar
  // ... completar
  return result;
}
