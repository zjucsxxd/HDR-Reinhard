#if !defined UTILS_H
#define UTILS_H

#include <stdio.h> //for printf
#include <stdlib.h> //for aligned malloc
#include <string.h> //for memset
#include <math.h>

#define HDR_STACK_TOTAL_SIZE (0x8000000) //128Mbytes

typedef struct{
    void *stack_starting_address;
    char *stack_current_address;
    unsigned int stack_current_alloc_size;
}stack_struct;

void init_stack(void);

void free_stack(void);

void *alloc_from_stack(unsigned int len);

void partial_free_from_stack(unsigned int len);

unsigned int get_stack_current_alloc_size(void);

void reset_stack_ptr_to_assigned_position(unsigned int assigned_size);

#endif /* UTILS_H */