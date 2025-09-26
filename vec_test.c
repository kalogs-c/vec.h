#include "vec.h"
#include <stdio.h>
#include <stdlib.h>

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

#define DEFAULT_CAPACITY 8

TEST(test_vector_creation) {
    int* v = vec(int, DEFAULT_CAPACITY);
    ASSERT(vec_length(v) == 0);
    ASSERT(vec_capacity(v) == DEFAULT_CAPACITY);
    vec_free(v, false);
}

TEST(test_vector_push) {
    int* v = vec(int, DEFAULT_CAPACITY);
    vec_push(v, 10);
    vec_push(v, 20);
    ASSERT(vec_length(v) == 2);
    ASSERT(v[0] == 10);
    ASSERT(v[1] == 20);
    vec_free(v, false);
}

TEST(test_vector_resize) {
    int* v = vec(int, DEFAULT_CAPACITY);
    for (int i = 0; i < DEFAULT_CAPACITY * 2; i++) {
        vec_push(v, i);
    }

    ASSERT(vec_capacity(v) == DEFAULT_CAPACITY * 2);
    ASSERT(vec_length(v) == DEFAULT_CAPACITY * 2);
    vec_free(v, false);
}

typedef struct {
    int x, y;
} Point;

TEST(test_vector_structs) {
    Point** v = vec(Point*, DEFAULT_CAPACITY);

    Point* p1 = malloc(sizeof(Point));
    p1->x = 1;
    p1->y = 2;

    Point* p2 = malloc(sizeof(Point));
    p2->x = 3;
    p2->y = 4;

    vec_push(v, p1);
    vec_push(v, p2);
    ASSERT(vec_length(v) == 2);
    ASSERT(v[0]->x == 1);
    ASSERT(v[0]->y == 2);
    ASSERT(v[1]->x == 3);
    ASSERT(v[1]->y == 4);

    vec_free(v, true);
}

int main(void) {
    RUN_TEST(test_vector_creation);
    RUN_TEST(test_vector_push);
    RUN_TEST(test_vector_resize);
    RUN_TEST(test_vector_structs);
    return failed;
}
