///
/// Pruebas de arreglos dinamicos
///
/// deben ser extendidas
///

#include "test_dyna.h"
#include "dynarray.h"

#include <stdio.h>
#include <stdlib.h>

///
/// show_dynarray: imprime un arreglo dinamico
///
/// const Dynarray *dyna: apuntador a un arreglo dinamico
///
static void show_dynarray(const Dynarray *dyna) {
  // no podemos accesar directamente los campos de la estructura Dynarray ...
  // ... y tampoco cambiarlos, ya que son partes privadas de la implementacion.
  // pero podemos obtener sus valores usando las funciones de acceso
  size_t size = dyna_size(dyna);
  size_t capacity = dyna_capacity(dyna);
  const double *data = dyna_data(dyna);

  fprintf(stdout, "numero de elementos / capacidad: %u/%u\n", size, capacity);
  fprintf(stdout, "[\n");
  for (size_t i = 0; i < size; ++i) {
    fprintf(stdout, "  %6d: %12.6f\n", i, data[i]); // <== notar la noitacion data[i]
  }
  // a ver si notan y tienen el sentido comun de eliminar este error intencional
  // que pasa si usan la notacion data[] en vez de dyna_val(10000, dyna)?
  size_t i = 801702; // https://www.youtube.com/watch?v=5aQ1wFt82k4
  fprintf(stdout, "  %6d: %12.6f\n", i, dyna_val(i, dyna));
  fprintf(stdout, "]\n\n");
}

int test_dynamic_arrays(int argc, const char *argv[]) {
  // si argc es mayor o igual a 3, usar el parametro provisto
  const size_t NX_DEFAULT = 8;
  const size_t NX = (3 <= argc ? atoi(argv[2]) : NX_DEFAULT);

  Initializer init_x = get_initializer("z");

  Dynarray *x = dynarray(NX, init_x);
  show_dynarray(x);
  dyna_insert(x, 2, 5, init_x);
  show_dynarray(x);
  dyna_remove(x, 3, 4);
  show_dynarray(x);
  dyna_sort(x);
  show_dynarray(x);

  // si argc es mayor o igual a 4, usar el parametro provisto
  const size_t NY_DEFAULT = 16;
  const size_t NY = (4 <= argc ? atoi(argv[3]) : NY_DEFAULT);
  Initializer init_y = get_initializer("f");

  Dynarray *y = dynarray(NY, init_y);
  show_dynarray(y);

  Dynarray *result = dyna_concatenate(x, y);
  show_dynarray(result);
  return 0;    
}
