# C Vec - Dynamic Array Library

C Vec is a simple dynamic array library for C, provided as a single header file. It automatically resizes arrays as you add elements.

## Usage

### Add the vec.h to your project
Just copy the vec.h file and include
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

### Access Length and Capacity
```c
size_t len = vec_length(my_vec);
size_t cap = vec_capacity(my_vec);
```

### Free Memory
```c
vec_destroy(my_vec);
```
