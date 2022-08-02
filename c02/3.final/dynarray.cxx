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

void dyna_destroy(Dynarray *dynarray) {
  // liberar las areas de memoria reservadas por malloc
  // ademas, la ultima instruccion debe anular el dynarray mismo
  // la idea es evitar que el usuario se refiera a memoria liberada
  free(dynarray->data);
  free(dynarray);
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

  // Si pos se sale del rango
  if (pos < 0 || pos > dyna->size){
    printf("Pos no cumple con la condicion");
    return;
  }

  // Si hay espacio
  if (dyna->capacity - dyna->size >= N){

    dyna->size = dyna->size + N;
    double prevArr[N];
    size_t i;

    // Copiando vieja informacion y generando la nueva
    for (i = pos; i < pos + N; i++){
      prevArr[i] = dyna->data[i];
      dyna->data[i] = init(i);
    }

    for (i = pos + N; i < dyna->size; i++){
      dyna->data[i] = prevArr[i];
    }

  // Si no hay espacio
  } else {
    int prevSize = dyna->size;
    double prevArr[prevSize];
    size_t i;
    size_t j;
    dyna->capacity = dyna->capacity + N;
    dyna->size = dyna->size + N;

    // Copiando vieja informacion y generando la nueva
    for (i = 0; i < prevSize; i++){
      prevArr[i] = dyna->data[i];
    }

    free(dyna->data);
    dyna->data = (double *) malloc(dyna->capacity * sizeof(double));

    for (i = 0; i < pos; i++){
      dyna->data[i] = prevArr[i];
    }

    for (j = pos; j < pos + N; j++){
      dyna->data[j] = init(i);
    }

    for (j = pos + N; j < dyna->size; j++){
      dyna->data[j] = prevArr[i];
      i++;
    }
  }


}

void dyna_remove(Dynarray *dyna, int pos, int N) {
// Si pos se sale del rango
  if (pos < 0 || N > dyna->size - pos){
    printf("Pos no cumple con la condicion");
    return;
  }

  size_t i;

  for (i = pos + N; i < dyna->size; i++){
    dyna->data[i - N] = dyna->data[i];
  }

  dyna->size = dyna->size - N;
}

void dyna_sort(Dynarray *dyna) {
  size_t i;
  size_t j;
  double a;
  for (i = 0; i < dyna->size; ++i) {
    for (j = i + 1; j < dyna->size; ++j){
      if (dyna->data[i] > dyna->data[j]) {
        a =  dyna->data[i];
        dyna->data[i] = dyna->data[j];
        dyna->data[j] = a;
      }
    }
  }
}

Dynarray *dyna_concatenate(const Dynarray *dyna1, const Dynarray *dyna2) {

  size_t S1 = dyna1->size;
  size_t S2 = dyna2->size;
  size_t C1 = dyna1->capacity;
  size_t C2 = dyna2->capacity;
  size_t i;
  Dynarray *result = (Dynarray *) malloc(sizeof(Dynarray));
  result->size = S1 + S2;
  result->capacity = C1 + C2;
  result->data = (double *) malloc(result->capacity * sizeof(double));
  for (i = 0; i < S1; i++){
    result->data[i] = dyna1->data[i];
  }
  for (i = 0; i < S2; i++){
    result->data[S1 + i] = dyna2->data[i];
  }
  return result;
}
