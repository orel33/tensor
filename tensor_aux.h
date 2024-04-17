// Auxiliary functions for tensor manipulation

#ifndef TENSOR_AUX_H
#define TENSOR_AUX_H

#include "tensor.h"

tensor *tensor_rand(uint ndim, uint *shape, int maxval);
void tensor_print(tensor *t);
void tensor_save(tensor *t, const char *filename);
tensor *tensor_load(const char *filename);

#endif
