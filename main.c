#include "vec.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int age;
    char* name;
} Person;

void rand_str(char *dest, size_t length) {
    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (length-- > 0) {
        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}

int main() {
    Person* nums = vec(Person);
    for (size_t i = 1; i < 1000; i++)
    {
        char name[] = { [20] = '\1' };
        rand_str(name, sizeof name - 1);
        Person p = {
            .name = name,
            .age = i,
        };
        vec_push(nums, p);
    }

    for (size_t i = 0; i < vec_length(nums); i++)
    {
        printf("Name: %s | Age: %i\n", nums[i].name, nums[i].age);
    }

    vec_metadata_t* meta = vec_meta(nums);
    printf("Capacity: %d\nLength: %d\n", meta->capacity, meta->length);
    
    return 0;
}