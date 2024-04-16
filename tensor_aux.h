#ifndef TENSOR_AUX_H
#define TENSOR_AUX_H

#include "tensor.h"

tensor *tensor_rand_int(uint ndim, uint *shape, int maxval);
void tensor_print_int(tensor *t);
void tensor_save_int(tensor *t, const char *filename);
tensor *tensor_load_int(const char *filename);

#endif
