// Test file for tensor.c

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tensor.h"
#include "tensor_aux.h"

/* *********************************************************** */

uint sample_shape[] = {3, 2};
int sample_data[] = {1, 2, 3, 4, 5, 6};
uint zeros_shape[] = {3, 2};
int zeros_data[] = {0, 0, 0, 0, 0, 0};
uint ones_shape[] = {3, 2};
int ones_data[] = {1, 1, 1, 1, 1, 1};

/* *********************************************************** */

static bool check_tensor(tensor *t, uint ndim, uint *shape, int *data) {
  if (t == NULL) return false;
  if (tensor_ndim(t) != ndim) return false;
  uint *tshape = tensor_shape(t);
  for (int i = 0; i < ndim; i++)
    if (tshape[i] != shape[i]) return false;
  uint tsize = tensor_size(t);
  int *tdata = tensor_data(t);
  for (int i = 0; i < tsize; i++)
    if (tdata[i] != data[i]) return false;
  return true;
}

/* *********************************************************** */

bool test_new(void) {
  tensor *t = tensor_new(2, sample_shape, sample_data);
  bool ok = check_tensor(t, 2, sample_shape, sample_data);
  tensor_free(t);
  return ok;
}

/* *********************************************************** */

bool test_zeros(void) {
  tensor *t = tensor_zeros(2, zeros_shape);
  bool ok = check_tensor(t, 2, zeros_shape, zeros_data);
  return ok;
}

/* *********************************************************** */

bool test_ones(void) {
  tensor *t = tensor_ones(2, ones_shape);
  bool ok = check_tensor(t, 2, ones_shape, ones_data);
  return ok;
}

/* *********************************************************** */

bool test_copy(void) {
  tensor *t0 = tensor_new(2, sample_shape, sample_data);
  bool ok0 = check_tensor(t0, 2, sample_shape, sample_data);
  tensor *t1 = tensor_copy(t0);
  bool ok1 = check_tensor(t1, 2, sample_shape, sample_data);
  tensor_free(t0);
  tensor_free(t1);
  return ok0 && ok1;
}

/* *********************************************************** */

bool test_get(void) {
  tensor *t = tensor_new(2, sample_shape, sample_data);
  bool ok0 = check_tensor(t, 2, sample_shape, sample_data);
  uint ndim = tensor_ndim(t);
  uint *shape = tensor_shape(t);
  int *data = tensor_data(t);
  bool ok1 = check_tensor(t, ndim, shape, data);
  tensor_free(t);
  return ok0 && ok1;
}

/* *********************************************************** */

bool test_size(void) {
  tensor *t = tensor_new(2, sample_shape, sample_data);
  bool ok = (tensor_size(t) == 6);
  tensor_free(t);
  return ok;
}

/* *********************************************************** */

bool test_element(void) {
  tensor *t = tensor_new(2, sample_shape, sample_data);
  bool ok0 = check_tensor(t, 2, sample_shape, sample_data);
  uint indices[] = {1, 1};
  bool ok1 = (tensor_get_element(t, indices) == 4);
  tensor_set_element(t, indices, 42);
  bool ok2 = (tensor_get_element(t, indices) == 42);
  printf("%d %d %d\n", ok0, ok1, ok2);
  tensor_free(t);
  return ok0 && ok1 && ok2;
}

/* *********************************************************** */

bool test_add(void) {
  tensor *t0 = tensor_new(2, sample_shape, sample_data);
  tensor *t1 = tensor_new(2, sample_shape, sample_data);
  tensor *t2 = tensor_add(t0, t1);
  int expected_data[] = {2, 4, 6, 8, 10, 12};
  bool ok = check_tensor(t2, 2, sample_shape, expected_data);
  tensor_free(t0);
  tensor_free(t1);
  tensor_free(t2);
  return ok;
}

/* *********************************************************** */

bool test_mul(void) {
  tensor *t0 = tensor_new(2, sample_shape, sample_data);
  tensor *t1 = tensor_new(2, sample_shape, sample_data);
  tensor *t2 = tensor_mul(t0, t1);
  int expected_data[] = {1, 4, 9, 16, 25, 36};
  bool ok = check_tensor(t2, 2, sample_shape, expected_data);
  tensor_free(t0);
  tensor_free(t1);
  tensor_free(t2);
  return ok;
}

/* *********************************************************** */

bool test_equal(void) {
  tensor *t0 = tensor_new(2, sample_shape, sample_data);
  tensor *t1 = tensor_new(2, sample_shape, sample_data);
  bool ok0 = check_tensor(t0, 2, sample_shape, sample_data);
  bool ok1 = check_tensor(t1, 2, sample_shape, sample_data);
  bool ok2 = tensor_equal(t0, t1);
  tensor_free(t0);
  tensor_free(t1);
  return ok0 && ok1 && ok2;
}

/* *********************************************************** */

bool test_sum(void) {
  tensor *t = tensor_new(2, sample_shape, sample_data);
  bool ok = (tensor_sum(t) == 21);
  tensor_free(t);
  return ok;
}

/* *********************************************************** */

bool test_max(void) {
  tensor *t = tensor_new(2, sample_shape, sample_data);
  bool ok = (tensor_max(t) == 6);
  tensor_free(t);
  return ok;
}

/* *********************************************************** */

bool test_reshape(void) {
  tensor *t = tensor_new(2, sample_shape, sample_data);
  uint new_shape[] = {2, 3};
  tensor *t1 = tensor_reshape(t, 2, new_shape);
  bool ok = check_tensor(t1, 2, new_shape, sample_data);
  tensor_free(t);
  tensor_free(t1);
  return ok;
}

/* *********************************************************** */

bool test_flatten(void) {
  tensor *t = tensor_new(2, sample_shape, sample_data);
  tensor *t1 = tensor_flatten(t);
  uint new_shape[] = {6};
  bool ok = check_tensor(t1, 1, new_shape, sample_data);
  tensor_free(t);
  tensor_free(t1);
  return ok;
}

/* *********************************************************** */

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/* *********************************************************** */

int main(int argc, char *argv[]) {
  if (argc == 1) usage(argc, argv);

  // start test
  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;
  if (strcmp("new", argv[1]) == 0)
    ok = test_new();
  else if (strcmp("zeros", argv[1]) == 0)
    ok = test_zeros();
  else if (strcmp("ones", argv[1]) == 0)
    ok = test_ones();
  else if (strcmp("copy", argv[1]) == 0)
    ok = test_copy();
  else if (strcmp("get", argv[1]) == 0)
    ok = test_get();
  else if (strcmp("size", argv[1]) == 0)
    ok = test_size();
  else if (strcmp("element", argv[1]) == 0)
    ok = test_element();
  else if (strcmp("add", argv[1]) == 0)
    ok = test_add();
  else if (strcmp("mul", argv[1]) == 0)
    ok = test_mul();
  else if (strcmp("equal", argv[1]) == 0)
    ok = test_equal();
  else if (strcmp("sum", argv[1]) == 0)
    ok = test_sum();
  else if (strcmp("max", argv[1]) == 0)
    ok = test_max();
  else if (strcmp("reshape", argv[1]) == 0)
    ok = test_reshape();
  else if (strcmp("flatten", argv[1]) == 0)
    ok = test_flatten();
  else {
    fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // print test result
  if (ok) {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}
