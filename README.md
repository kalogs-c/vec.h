# C Vec - Dynamic Array Library

C Vec is a simple dynamic array library for C, provided as a single header file. It automatically resizes arrays as you add elements.

## Usage

### Add the `vec.h` to Your Project
Just copy the `vec.h` file and include it:
```c
#include "vec.h"
```

### Create a Dynamic Array
```c
int* my_vec = vec(int);
```

### Add Elements
```c
vec_push(my_vec, 10);
vec_push(my_vec, 20);
```

### Access Elements
Just like a regular array.
```c
int first = my_vec[0];
```

### Access Length and Capacity
```c
size_t len = vec_length(my_vec);
size_t cap = vec_capacity(my_vec);
```

### Free Memory

- If your vector holds simple data types like `int`, use:
```c
vec_destroy(my_vec);
```

- If your vector holds dynamically allocated pointers (e.g., struct pointers), use `vec_destroyemall` to free each element and the vector itself:
```c
vec_destroyemall(my_vec, MyStruct*);
```

### Example: Freeing Struct Pointers

```c
typedef struct {
    int x;
    int y;
} MyStruct;

MyStruct** my_vec = vec(MyStruct*);

// Dynamically allocate and add elements
MyStruct* p1 = (MyStruct*)malloc(sizeof(MyStruct));
vec_push(my_vec, p1);

// Free the elements and the vector
vec_destroyemall(my_vec, MyStruct*);
```

This ensures both the individual dynamically allocated elements and the vector metadata are properly freed.
