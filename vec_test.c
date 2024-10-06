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
    int* v = vec(int);
    ASSERT(vec_length(v) == 0);
    ASSERT(vec_capacity(v) == DEFAULT_CAPACITY);
    vec_destroy(v);
}

// Test for pushing elements and checking length
TEST(test_vector_push) {
    int* v = vec(int);
    vec_push(v, 10);
    vec_push(v, 20);
    ASSERT(vec_length(v) == 2);
    ASSERT(v[0] == 10);
    ASSERT(v[1] == 20);
    vec_destroy(v);
}

// Test for resizing when capacity is exceeded
TEST(test_vector_resize) {
    int* v = vec(int);
    for (int i = 0; i < DEFAULT_CAPACITY + 1; i++) {
        vec_push(v, i);
    }
    ASSERT(vec_capacity(v) > DEFAULT_CAPACITY); // Ensure it resized
    ASSERT(vec_length(v) == DEFAULT_CAPACITY + 1);
    vec_destroy(v);
}

// Test for vector with custom types (e.g., struct)
typedef struct {
    int x, y;
} Point;

TEST(test_vector_structs) {
    Point** v = vec(Point*);

    Point* p1 = (Point*)malloc(sizeof(Point));
    p1->x = 1;
    p1->y = 2;

    Point* p2 = (Point*)malloc(sizeof(Point));
    p2->x = 3;
    p2->y = 4;

    vec_push(v, p1);
    vec_push(v, p2);
    ASSERT(vec_length(v) == 2);
    ASSERT(v[0]->x == 1);
    ASSERT(v[0]->y == 2);
    ASSERT(v[1]->x == 3);
    ASSERT(v[1]->y == 4);
    vec_destroyemall(v, Point*);
}

int main() {
  RUN_TEST(test_vector_creation);
  RUN_TEST(test_vector_push);
  RUN_TEST(test_vector_resize);
  RUN_TEST(test_vector_structs);
  return failed;
}
