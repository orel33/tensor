#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tensor.h"
#include "tensor_aux.h"

int main(void) {
  srand(time(NULL));
  uint ndim = 2;
  uint shape[] = {3, 2};

  // make tensors
  printf("make tensor of ones: t1\n");
  tensor *t1 = tensor_ones(ndim, shape);
  printf("make random tensor: t2\n");
  tensor *t2 = tensor_rand_int(ndim, shape, 10);

  // print tensor
  printf("t1: ones\n");
  tensor_print_int(t1);
  printf("t2: random\n");
  tensor_print_int(t2);

  // element wise addition
  printf("t3 = t1 + t2\n");
  tensor *t3 = tensor_add(t1, t2);
  tensor_print_int(t3);

  // save tensor
  // const char *filename = "random.tensor";
  // printf("save tensor: %s\n", filename);
  // tensor_save_int(t, filename);

  // free it
  tensor_free(t1);
  tensor_free(t2);
  tensor_free(t3);

  return EXIT_SUCCESS;
}