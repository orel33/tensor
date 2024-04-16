#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tensor.h"
#include "tensor_aux.h"

/* *********************************************************** */

tensor *tensor_rand_int(uint ndim, uint *shape, int maxval) {
  tensor *t = tensor_new(ndim, shape, NULL);
  uint size = tensor_size(t);
  datatype *data = tensor_data(t);
  for (uint i = 0; i < size; i++) data[i] = (int)(rand() * 1.0 * maxval / RAND_MAX);
  return t;
}

/* *********************************************************** */

void tensor_print_int(tensor *t) {
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
  datatype *data = tensor_data(t);
  for (uint i = 0; i < size; i++) {
    printf("%d", (int)data[i]);
    if (i < size - 1) printf(", ");
  }
  printf("]\n");
}

/* *********************************************************** */

void tensor_save_int(tensor *t, const char *filename) {
  FILE *file = fopen(filename, "w");
  assert(file);
  // TODO
  fclose(file);
}

/* *********************************************************** */

tensor *tensor_load_int(const char *filename) {
  FILE *file = fopen(filename, "r");
  assert(file);
  tensor *t = NULL;
  fclose(file);
  return t;
}

/* *********************************************************** */
