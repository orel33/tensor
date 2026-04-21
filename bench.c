#include <stdio.h>
#include <stdlib.h>

#include "tensor.h"

#define N 150    // taille dimension
#define ITER 100 // nombre d'itérations

int
main ()
{
  uint shape[3] = { N, N, N };

  tensor *A = tensor_ones (3, shape);
  tensor *B = tensor_ones (3, shape);

  long total_sum = 0;
  for (int i = 0; i < ITER; i++)
    {
      tensor *C = tensor_add (A, B);
      tensor *D = tensor_mul (C, A);
      int s = tensor_sum (D);
      total_sum += s;
      tensor_free (C);
      tensor_free (D);
    }
  printf ("Total sum: %ld\n", total_sum);

  tensor_free (A);
  tensor_free (B);

  return 0;
}