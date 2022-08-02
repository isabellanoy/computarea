///
/// p1.cxx
///
/// Introducción a apuntadores y arreglos - Introduction to pointers and arrays
///
/// con la primera aparición exclusiva de una nueva actriz: la estructura de control for
/// 

#include <stdio.h>

void show_array_double(int length, double a[])
{
  int i = 0;
  while (i < length) {
    fprintf(stdout, "[%d]: %lf\n", i, a[i]);
    i = i + 1;
  }
  fprintf(stdout, "--------\n");
}

int main()
{
  double a[] = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 };
  double b[] = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };

  const int NA = sizeof(a) / sizeof(a[0]);
  const int NB = sizeof(b) / sizeof(b[0]);

  show_array_double(NA, a);
  show_array_double(NB, b);

  return 0;
}
