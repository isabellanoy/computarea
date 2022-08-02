///
/// arrays.cxx
///

#include <stdio.h>

int main()
{
  int    a[] = {  0,   1,   2,   3,   4,   5,   6,   7  };
  double b[] = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7 };

  fprintf(stdout, "sizeof(a) = %d bytes\n", sizeof(a));
  fprintf(stdout, "sizeof(b) = %d bytes\n", sizeof(b));

  const int NA = sizeof(a) / sizeof(a[0]);
  fprintf(stdout, "NA = %d\n", NA);

  const int NB = sizeof(b) / sizeof(b[0]);
  fprintf(stdout, "NB = %d\n", NB);
}
