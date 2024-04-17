#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tensor.h"
#include "tensor_aux.h"

/* *********************************************************** */

tensor *tensor_rand(uint ndim, uint *shape, int maxval) {
  tensor *t = tensor_new(ndim, shape, NULL);
  uint size = tensor_size(t);
  int *data = tensor_data(t);
  for (uint i = 0; i < size; i++) data[i] = (int)(rand() * 1.0 * maxval / RAND_MAX);
  return t;
}

/* *********************************************************** */

void tensor_print(tensor *t) {
  assert(t);
  uint ndim = tensor_ndim(t);
  uint *shape = tensor_shape(t);
  printf("shape: (");
  for (uint i = 0; i < ndim; i++) {
    printf("%d", shape[i]);
    if (i < ndim - 1) printf(", ");
  }
  printf(")\n");
  printf("data: [");
  uint size = tensor_size(t);
  int *data = tensor_data(t);
  for (uint i = 0; i < size; i++) {
    printf("%d", (int)data[i]);
    if (i < size - 1) printf(", ");
  }
  printf("]\n");
}

/* *********************************************************** */

void tensor_save(tensor *t, const char *filename) {
  FILE *file = fopen(filename, "w");
  assert(file);
  uint ndim = tensor_ndim(t);
  uint *shape = tensor_shape(t);
  uint size = tensor_size(t);
  int *data = tensor_data(t);
  fprintf(file, "%d\n", ndim);
  for (uint i = 0; i < ndim; i++) fprintf(file, "%d ", shape[i]);
  fprintf(file, "\n");
  for (uint i = 0; i < size; i++) fprintf(file, "%d ", (int)data[i]);
  fprintf(file, "\n");
  fclose(file);
}

/* *********************************************************** */

tensor *tensor_load(const char *filename) {
  FILE *file = fopen(filename, "r");
  assert(file);
  uint ndim;
  fscanf(file, "%d", &ndim);
  uint shape[ndim];
  for (uint i = 0; i < ndim; i++) fscanf(file, "%d", &shape[i]);
  tensor *t = tensor_new(ndim, shape, NULL);
  uint size = tensor_size(t);
  int *data = tensor_data(t);
  for (uint i = 0; i < size; i++) {
    int value;
    fscanf(file, "%d", &value);
    data[i] = value;
  }
  fclose(file);
  return t;
}

/* *********************************************************** */
