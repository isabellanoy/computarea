///
/// p0.cxx
///
/// Introducción a apuntadores - Introductión to pointers
///

#include <stdio.h>

int main()
{
  int an = 10;
  int bn = 20;

  double ax = 10.0;
  double bx = 20.0;

  int *pan = &an; // &an es la dirección en memoria de an
  int *pbn = &bn; // &bn es la dirección en memoria de bn

  double *pax = &ax; // &ax es la dirección en memoria de ax
  double *pbx = &bx; // &bx es la dirección en memoria de bx

  fprintf(stdout, "an = %d, *pan = %d\n", an, *pan);
  fprintf(stdout, "ax = %lf, *pax = %lf\n", ax, *pax);

  fprintf(stdout, "size of an = %d, size of pan = %d\n", sizeof(an), sizeof(pan));
  fprintf(stdout, "size of ax = %d, size of pax = %d\n", sizeof(ax), sizeof(pax));

  return 0;
}
