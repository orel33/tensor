/**
 * @brief Simple implementation of *tensor* data structure in C.
 * @author aurelien.esnard@u-bordeaux.fr, 2024.
 **/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tensor.h"

/* *********************************************************** */

#define MAX(x, y) (((x) <= (y)) ? (y) : (x))

/* *********************************************************** */

struct tensor_s {
  datatype *data;
  uint *shape;
  uint ndim;
};

typedef struct tensor_s tensor;

/* *********************************************************** */

static uint shape_size(uint ndim, uint *shape) {
  assert(shape);
  uint size = 1;
  for (uint i = 0; i < ndim; i++) size *= shape[i];
  return size;
}

/* *********************************************************** */

static uint calculate_index(uint ndim, uint *shape, uint *indices) {
  assert(shape);
  assert(indices);
  uint index = 0;
  uint multiplier = 1;
  for (uint i = ndim - 1; i >= 0; i--) {
    index += indices[i] * multiplier;
    multiplier *= shape[i];
  }
  return index;
}

/* *********************************************************** */

tensor *tensor_new(uint ndim, uint *shape, datatype *data) {
  assert(shape);
  tensor *t = (tensor *)malloc(sizeof(tensor));
  assert(t);
  t->ndim = ndim;
  t->shape = (uint *)malloc(ndim * sizeof(uint));
  assert(t->shape);
  for (uint i = 0; i < ndim; i++) t->shape[i] = shape[i];
  uint size = shape_size(ndim, shape);
  t->data = (datatype *)malloc(size * sizeof(datatype));
  assert(t->data);
  if (data) {
    for (uint i = 0; i < size; i++) t->data[i] = data[i];
  }
  return t;
}

/* *********************************************************** */

tensor *tensor_zeros(uint ndim, uint *shape) {
  tensor *t = tensor_new(ndim, shape, NULL);
  uint size = shape_size(ndim, shape);
  for (uint i = 0; i < size; i++) t->data[i] = 0;
  return t;
}

/* *********************************************************** */

tensor *tensor_ones(uint ndim, uint *shape) {
  tensor *t = tensor_new(ndim, shape, NULL);
  uint size = shape_size(ndim, shape);
  for (uint i = 0; i < size; i++) t->data[i] = 1;
  return t;
}

/* *********************************************************** */

uint *tensor_shape(tensor *t) {
  assert(t);
  return t->shape;
}

/* *********************************************************** */

uint tensor_size(tensor *t) {
  assert(t);
  uint size = shape_size(t->ndim, t->shape);
  return size;
}

/* *********************************************************** */

uint tensor_ndim(tensor *t) {
  assert(t);
  return t->ndim;
}

/* *********************************************************** */

datatype *tensor_data(tensor *t) {
  assert(t);
  return t->data;
}

/* *********************************************************** */

datatype tensor_get_element(tensor *t, uint *indices) {
  assert(t);
  assert(indices);
  uint index = calculate_index(t->ndim, t->shape, indices);
  return t->data[index];
}

/* *********************************************************** */

void tensor_set_element(tensor *t, uint *indices, datatype value) {
  assert(t);
  assert(indices);
  uint index = calculate_index(t->ndim, t->shape, indices);
  t->data[index] = value;
}

/* *********************************************************** */

tensor *tensor_copy(tensor *t) {
  assert(t);
  tensor *copy = tensor_new(t->ndim, t->shape, t->data);
  return copy;
}

/* *********************************************************** */

bool tensor_equal(tensor *t1, tensor *t2) {
  assert(t1);
  assert(t2);
  if (t1->ndim != t2->ndim) return false;
  for (uint i = 0; i < t1->ndim; i++) {
    if (t1->shape[i] != t2->shape[i]) return false;
  }
  uint size = tensor_size(t1);
  for (uint i = 0; i < size; i++) {
    if (t1->data[i] != t2->data[i]) return false;
  }
  return true;
}

/* *********************************************************** */

tensor *tensor_add(tensor *t1, tensor *t2) {
  assert(t1);
  assert(t2);
  assert(t1->ndim == t2->ndim);
  for (uint i = 0; i < t1->ndim; i++) {
    assert(t1->shape[i] == t2->shape[i]);
  }
  uint size = tensor_size(t1);
  tensor *t = tensor_new(t1->ndim, t1->shape, NULL);
  for (uint i = 0; i < size; i++) {
    t->data[i] = t1->data[i] + t2->data[i];
  }
  return t;
}

/* *********************************************************** */

tensor *tensor_mul(tensor *t1, tensor *t2) {
  assert(t1);
  assert(t2);
  assert(t1->ndim == t2->ndim);
  for (uint i = 0; i < t1->ndim; i++) {
    assert(t1->shape[i] == t2->shape[i]);
  }
  uint size = tensor_size(t1);
  tensor *t = tensor_new(t1->ndim, t1->shape, NULL);
  for (uint i = 0; i < size; i++) {
    t->data[i] = t1->data[i] * t2->data[i];
  }
  return t;
}

/* *********************************************************** */

datatype tensor_sum(tensor *t) {
  assert(t);
  uint size = tensor_size(t);
  datatype sum = 0.0f;
  for (uint i = 0; i < size; i++) {
    sum += t->data[i];
  }
  return sum;
}

/* *********************************************************** */

datatype tensor_max(tensor *t) {
  assert(t);
  uint size = tensor_size(t);
  datatype max = t->data[0];
  for (uint i = 1; i < size; i++) {
    max = MAX(max, t->data[i]);
  }
  return max;
}

/* *********************************************************** */

tensor *tensor_reshape(tensor *t, uint ndim, uint *shape) {
  assert(t);
  assert(shape);
  uint size = shape_size(ndim, shape);
  assert(size == tensor_size(t));
  tensor *reshaped = tensor_new(ndim, shape, t->data);
  return reshaped;
}

/* *********************************************************** */

tensor *tensor_flatten(tensor *t) {
  assert(t);
  uint size = tensor_size(t);
  uint shape[] = {size};
  tensor *flattened = tensor_new(1, shape, t->data);
  return flattened;
}

/* *********************************************************** */

void tensor_free(tensor *t) {
  assert(t);
  free(t->shape);
  free(t->data);
  free(t);
}

/* *********************************************************** */
