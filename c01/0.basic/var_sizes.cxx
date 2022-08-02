///
/// var_sizes.cxx
///
/// Tipos de datos basicos - Base data types
///

#include <stdio.h>

int main()
{
  // bool type
  bool bool_var = false;

  // int types
  char char_var = '0';
  short short_int_var = 0;
  int int_var = 0;
  long long_int_var = 0;

  // floating point types
  float float_var = 0.0;
  double double_var = 0.0;
  long double long_double_var = 0.0;

  // -------------------
  
  fprintf(stdout, "sizeof(bool_var) = %ld byte\n", sizeof(bool_var));

  fprintf(stdout, "sizeof(char_var) = %ld byte\n", sizeof(char_var));
  fprintf(stdout, "sizeof(short_int_var) = %ld bytes\n", sizeof(short_int_var));
  fprintf(stdout, "sizeof(int_var) = %ld bytes\n", sizeof(int_var));
  fprintf(stdout, "sizeof(long_int_var) = %ld bytes\n", sizeof(long_int_var));

  fprintf(stdout, "sizeof(float_var) = %ld bytes\n", sizeof(float_var));
  fprintf(stdout, "sizeof(double_var) = %ld bytes\n", sizeof(double_var));
  fprintf(stdout, "sizeof(long_double_var) = %ld bytes\n", sizeof(long_double_var));

  return 0;
}
