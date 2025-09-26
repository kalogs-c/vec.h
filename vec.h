#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t capacity;
    size_t length;
} vec_metadata_t;

#define vec(T, capacity) (T*)vec_start(sizeof(T), capacity)

static inline void* vec_start(const size_t item_size, const size_t initial_capacity) {
    const size_t size = sizeof(vec_metadata_t) + item_size * initial_capacity;
    vec_metadata_t* meta = malloc(size);
    assert(meta && "failed allocate vec");

    meta->capacity = initial_capacity;
    meta->length = 0;
    return meta + 1;
}

#define vec_meta(v) ((vec_metadata_t*)(v) - 1)
#define vec_length(v) (vec_meta(v)->length)
#define vec_capacity(v) (vec_meta(v)->capacity)

static inline void vec_free(void* v, const bool cascade) {
    if (v == NULL) return;

    if (cascade) {
        for (size_t i = 0; i < vec_length(v); i++) {
            free(((void**) v)[i]);
        }
    }

    vec_metadata_t* meta = vec_meta(v);
    return free(meta);
}

static inline void* vec_ensure_capacity(void* v, const size_t items_count, const size_t item_size) {
    vec_metadata_t* meta = vec_meta(v);

    const size_t capacity_needed = meta->length + items_count;
    if (meta->capacity >= capacity_needed) {
        return v;
    }

    size_t new_capacity = meta->capacity * 2;
    while (new_capacity < capacity_needed) {
        new_capacity *= 2;
    }

    const size_t new_size = sizeof(vec_metadata_t) + new_capacity * item_size;
    vec_metadata_t* new_meta = realloc(meta, new_size);
    assert(new_meta && "failed realloc vec");

    new_meta->capacity = new_capacity;
    return new_meta + 1;
}

#define vec_push(vec, value) ( \
    (vec) = vec_ensure_capacity(vec, 1, sizeof(*(vec))), \
    (vec)[vec_length(vec)] = (value), \
    &(vec)[vec_meta(vec)->length++] \
)
