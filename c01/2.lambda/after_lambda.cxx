///
/// after_lambda.cxx
///
/// Abstraccion Funcional - Functional Abstraction
///

#include <math.h>
#include <stdio.h>

double area_circle(double radius)
{
  return M_PI * pow(radius, 2.0); //  math.h => M_PI & pow;
}

int main()
{
  // radio del circulo a - a circle radius
  double a_radius = 10.0;

  // radio del circulo b - b circle radius
  double b_radius = 20.0;

  double a_area = area_circle(a_radius);
  fprintf(stdout, "area del circulo con radio %lf = %lf\n", a_radius, a_area);

  double b_area = area_circle(b_radius);
  fprintf(stdout, "area del circulo con radio %lf = %lf\n", b_radius, b_area);

  double area_ratio = a_area / b_area;
  fprintf(stdout, "area(a) / area(b) = %lf\n", area_ratio);

  return 0;
}
