///
/// type_sizes.cxx
///
/// Tipos de datos basicos - Base data types
///

#include <stdio.h>

int main()
{
  // bool type
  fprintf(stdout, "sizeof(bool) = %ld byte\n", sizeof(bool));

  // int types
  fprintf(stdout, "sizeof(char) = %ld bytes\n", sizeof(char));
  fprintf(stdout, "sizeof(short int) = %ld bytes\n", sizeof(short int));
  fprintf(stdout, "sizeof(int) = %ld bytes\n", sizeof(int));
  fprintf(stdout, "sizeof(long int) = %ld bytes\n", sizeof(long int));
  fprintf(stdout, "sizeof(long long int) = %ld bytes\n", sizeof(long long int));

  // floating point types
  fprintf(stdout, "sizeof(float) = %ld bytes\n", sizeof(float));
  fprintf(stdout, "sizeof(double) = %ld bytes\n", sizeof(double));
  fprintf(stdout, "sizeof(long double) = %ld bytes\n", sizeof(long double));

  return 0;
}
