#include "vec.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Test helpers
int failed = 0;
#define TEST(name) void name()
#define RUN_TEST(name)                                                         \
  printf("\n\033[1m%s\n\033[0m", #name);                                       \
  name()
#define ASSERT(expr)                                                           \
  if (!(expr)) {                                                               \
    failed = 1;                                                                \
    printf("\033[0;31mFAIL: %s\n\033[0m", #expr);                              \
  } else {                                                                     \
    printf("\033[0;32mPASS: %s\n\033[0m", #expr);                              \
  }
// End of test helpers

// Test for vector creation and initial length and capacity
TEST(test_vector_creation) {
    int* vec = vec(int);
    ASSERT(vec_length(vec) == 0);
    ASSERT(vec_capacity(vec) == DEFAULT_CAPACITY);
    free(vec_meta(vec));
}

// Test for pushing elements and checking length
TEST(test_vector_push) {
    int* vec = vec(int);
    vec_push(vec, 10);
    vec_push(vec, 20);
    ASSERT(vec_length(vec) == 2);
    ASSERT(vec[0] == 10);
    ASSERT(vec[1] == 20);
    free(vec_meta(vec));
}

// Test for resizing when capacity is exceeded
TEST(test_vector_resize) {
    int* vec = vec(int);
    for (int i = 0; i < DEFAULT_CAPACITY + 1; i++) {
        vec_push(vec, i);
    }
    ASSERT(vec_capacity(vec) > DEFAULT_CAPACITY); // Ensure it resized
    ASSERT(vec_length(vec) == DEFAULT_CAPACITY + 1);
    free(vec_meta(vec));
}

// Test for vector with custom types (e.g., struct)
typedef struct {
    int x, y;
} Point;

TEST(test_vector_structs) {
    Point* vec = vec(Point);
    vec_push(vec, ((Point){.x = 1, .y = 2}));
    vec_push(vec, ((Point){.x = 3, .y = 4}));
    ASSERT(vec_length(vec) == 2);
    ASSERT(vec[0].x == 1);
    ASSERT(vec[0].y == 2);
    ASSERT(vec[1].x == 3);
    ASSERT(vec[1].y == 4);
    free(vec_meta(vec));
}

int main() {
  RUN_TEST(test_vector_creation);
  RUN_TEST(test_vector_push);
  RUN_TEST(test_vector_resize);
  RUN_TEST(test_vector_structs);
  return failed;
}
