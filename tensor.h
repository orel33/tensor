/**
 * @brief Simple implementation of *tensor* data structure in C.
 * @author aurelien.esnard@u-bordeaux.fr, 2024.
 **/

#ifndef TENSOR_H
#define TENSOR_H

#include <stdbool.h>

typedef struct tensor_s tensor;
typedef int datatype;
typedef unsigned int uint;

/* constructor */
tensor *tensor_new(uint ndim, uint *shape, datatype *data);
tensor *tensor_zeros(uint ndim, uint *shape);
tensor *tensor_ones(uint ndim, uint *shape);

/* basic accessors */
uint *tensor_shape(tensor *t);
uint tensor_size(tensor *t);
uint tensor_ndim(tensor *t);
datatype *tensor_data(tensor *t);
datatype tensor_get_element(tensor *t, uint *indices);
void tensor_set_element(tensor *t, uint *indices, datatype value);

/* some operations */
tensor *tensor_copy(tensor *t);
bool tensor_equal(tensor *t1, tensor *t2);  /* element wise equality */
tensor *tensor_add(tensor *t1, tensor *t2); /* element wise addition */
tensor *tensor_mul(tensor *t1, tensor *t2); /* element wise multiplication */
datatype tensor_sum(tensor *t);
datatype tensor_max(tensor *t);
tensor *tensor_reshape(tensor *t, uint ndim, uint *shape);
tensor *tensor_flatten(tensor *t);

/* destructor */
void tensor_free(tensor *t);

#endif
