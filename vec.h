#include <malloc.h>
#include <string.h>

#ifndef C_VEC
#define C_VEC

#define vec(T) (T*)vec_start(sizeof(T))
#define DEFAULT_CAPACITY 5

typedef struct {
    size_t capacity;
    size_t length;
} vec_metadata_t;

void* vec_start(size_t item_size) {
    void* ptr = 0;
    size_t size = item_size * DEFAULT_CAPACITY + sizeof(vec_metadata_t);
    vec_metadata_t* meta = (vec_metadata_t*)malloc(size);

    if (meta) {
        meta->capacity = DEFAULT_CAPACITY;
        meta->length = 0;

        ptr = meta + 1;
    }

    return ptr;
}

#define vec_meta(v) ((vec_metadata_t*)(v) - 1)
#define vec_length(v) (vec_meta(v)->length)
#define vec_capacity(v) (vec_meta(v)->capacity)

void* vec_ensure_capacity(void* v, size_t items_count, size_t item_size) {
    vec_metadata_t* meta = vec_meta(v);
    size_t capacity_needed = meta->length + items_count;

    if (meta->capacity > capacity_needed) {
        meta = meta + 1;
        return meta;
    }

    size_t new_capacity = meta->capacity * 2;
    while (new_capacity < capacity_needed) {
        new_capacity *= 2;
    }

    size_t new_size = sizeof(vec_metadata_t) + new_capacity * item_size;
    vec_metadata_t* new_meta = (vec_metadata_t*)malloc(new_size);
    if (new_meta == NULL) {
        return 0;
    }

    size_t old_size = sizeof(*meta) + meta->length * item_size;
    memcpy(new_meta, meta, old_size);
    free(meta);

    new_meta->capacity = new_capacity;
    return new_meta + 1;
}

#define vec_push(vec, value) ( \
    vec = vec_ensure_capacity(vec, 1, sizeof(value)), \
    (vec)[vec_length(vec)] = value, \
    &(vec)[vec_meta(vec)->length++])

#endif