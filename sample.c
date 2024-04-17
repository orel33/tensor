// Sample code for tensor library

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tensor.h"
#include "tensor_aux.h"

int main(void) {
  uint ndim = 3;
  uint shape[] = {4, 3, 2};
  int data[4][3][2] = {{{1, 2}, {3, 4}, {5, 6}},
                       {{7, 8}, {9, 10}, {11, 12}},
                       {{13, 14}, {15, 16}, {17, 18}},
                       {{19, 20}, {21, 22}, {23, 24}}};

  // create tensor
  printf("create tensor\n");
  tensor *t = tensor_new(ndim, shape, (int *)data);

  // print tensor
  printf("print tensor\n");
  tensor_print(t);

  // save tensor
  const char *filename = "tensor.txt";
  printf("save tensor: %s\n", filename);
  tensor_save(t, filename);

  // free it
  tensor_free(t);

  return EXIT_SUCCESS;
}