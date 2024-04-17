// Tensor data structure and operations
// Copyright (C) 2024, <aurelien.esnard@u-bordeaux.fr>

#ifndef TENSOR_H
#define TENSOR_H

#include <stdbool.h>

typedef struct tensor_s tensor;
typedef unsigned int uint;

/* constructor */
tensor *tensor_new(uint ndim, uint *shape, int *data);
tensor *tensor_zeros(uint ndim, uint *shape);
tensor *tensor_ones(uint ndim, uint *shape);
tensor *tensor_copy(tensor *t);

/* basic accessors */
uint *tensor_shape(tensor *t);
uint tensor_ndim(tensor *t);
int *tensor_data(tensor *t);
uint tensor_size(tensor *t);

/* get & set element using n-dimensional indices */
int tensor_get_element(tensor *t, uint *indices);
void tensor_set_element(tensor *t, uint *indices, int value);

/* basic operations */
tensor *tensor_add(tensor *t1, tensor *t2); /* element wise addition */
tensor *tensor_mul(tensor *t1, tensor *t2); /* element wise multiplication */
bool tensor_equal(tensor *t1, tensor *t2);  /* element wise equality */
int tensor_sum(tensor *t);
int tensor_max(tensor *t);
tensor *tensor_reshape(tensor *t, uint ndim, uint *shape);
tensor *tensor_flatten(tensor *t);

/* destructor */
void tensor_free(tensor *t);

#endif
