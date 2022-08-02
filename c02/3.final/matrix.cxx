///
/// matrix.cxx
///

#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

typedef double (*Initializer)(int i);

struct Matrix {
  double **data;
  size_t NR;
  size_t NC;
};

Matrix *matrix(size_t NR, size_t NC, Initializer init) {
  Matrix *result = (Matrix *) malloc(sizeof(Matrix));
  result->NR = NR;
  result->NC = NC;
  result->data = (double **) malloc(NR * sizeof(double *));
  for (size_t i = 0; i < NR; ++i) {
    result->data[i] = (double *) malloc(NC * sizeof(double));
    for (size_t j = 0; j < NC; ++j) {
      result->data[i][j] = init(NC * i + j);
    }
  }
  return result;
}

void matrix_destroy(Matrix **matrix) {
  size_t NR = (*matrix)->NR;
  for (size_t i = 0; i < NR; ++i) {
    free((*matrix)->data[i]);
    (*matrix)->data[i] = nullptr;
  }
  free((*matrix)->data);
  (*matrix)->data = nullptr;
  free(*matrix);
  *matrix = nullptr;
}

const double **matrix_data(const Matrix *matrix) {
  return (const double **) matrix->data;
}

size_t matrix_nr(const Matrix *matrix) {
  return matrix->NR;
}

size_t matrix_nc(const Matrix *matrix) {
  return matrix->NC;
}

Matrix *matrix_sum(const Matrix *lhs, const Matrix *rhs) {
  size_t LNR = lhs->NR;
  size_t LNC = lhs->NC;
  size_t RNR = rhs->NR;
  size_t RNC = rhs->NC;
  // if lhs and rhs are not conformant, print error and return null
  if (LNR != RNR || LNC != RNC) {
    fprintf(stderr, "Error: matrices que no tienen la misma forma no pueden ser sumadas: ");
    fprintf(stderr, "(%zux%zu) != (%zux%zu)\n", LNR, LNC, RNR, RNC);
    return nullptr;
  }
  Matrix *result = (Matrix *) malloc(sizeof(Matrix));
  result->NR = LNR;
  result->NC = LNC;
  result->data = (double **) malloc(LNR * sizeof(double *));
  for (size_t i = 0; i < LNR; ++i) {
    result->data[i] = (double *) malloc(LNC * sizeof(double));
    for (size_t j = 0; j < LNC; ++j) {
      result->data[i][j] = lhs->data[i][j] + rhs->data[i][j];
    }
  }
  return result;
}

Matrix *matrix_mult(const Matrix *lhs, const Matrix *rhs) {
  if (matrix_nc(lhs) != matrix_nr(rhs)){
    printf("Las matrices no tienen el tamaño adecuado para multiplicarse\n");
    return 0;
  }

  Matrix *result = (Matrix *) malloc(sizeof(Matrix));
  result->NR = matrix_nr(rhs);
  result->NC = matrix_nc(rhs);
  result->data = (double **) malloc(result->NR * sizeof(double *));
  size_t i;
  size_t j;
  size_t k;
  for (size_t i = 0; i < result->NR; ++i) {
    result->data[i] = (double *) malloc(result->NC * sizeof(double));
  }
  for (i = 0; i < matrix_nc(rhs); i++) {
    for (j = 0; j < matrix_nr(lhs); j++) {
        double suma = 0;
        for (k = 0; k < matrix_nc(lhs); k++) {
            suma += lhs->data[j][k] * rhs->data[k][i];
        }
        result->data[j][i] = suma;
    }
  }
  return result;
}