#include "utils.h"

static stack_struct hdr_stack = { NULL, NULL, 0 };

void init_stack(void){
    hdr_stack.stack_starting_address = _aligned_malloc(HDR_STACK_TOTAL_SIZE, 0x20);
    if (hdr_stack.stack_starting_address == NULL){
        printf("failed creating memory stack\n");
        exit(-1);
    }
    hdr_stack.stack_current_address = (char*)hdr_stack.stack_starting_address;
    hdr_stack.stack_current_alloc_size = 0;
}

void free_stack(void){
    _aligned_free(hdr_stack.stack_starting_address);
}

void* alloc_from_stack(unsigned int len){
    void* ptr = NULL;
    if (len <= 0){
        len = 0x20;
    }
    unsigned int aligned_len = (len + 0xF) & (~0xF);
    hdr_stack.stack_current_alloc_size += aligned_len;
    if (hdr_stack.stack_current_alloc_size >= HDR_STACK_TOTAL_SIZE){
        printf("failed allocating memory from stack anymore\n");
        _aligned_free(hdr_stack.stack_starting_address);
        exit(-1);
    }
    ptr = hdr_stack.stack_current_address;
    hdr_stack.stack_current_address += aligned_len;
    //C99: all zero bits means 0 for fixed points, 0.0 for floating points
    memset(ptr, 0, len);
    return ptr;
}

void partial_free_from_stack(unsigned int len){
    unsigned int aligned_len = (len + 0xF) & (~0xF);
    hdr_stack.stack_current_alloc_size -= aligned_len;
    hdr_stack.stack_current_address -= aligned_len;
}

unsigned int get_stack_current_alloc_size(void){
    return hdr_stack.stack_current_alloc_size;
}

void reset_stack_ptr_to_assigned_position(unsigned int assigned_size){
    hdr_stack.stack_current_address = (char*)hdr_stack.stack_starting_address + assigned_size;
    hdr_stack.stack_current_alloc_size = assigned_size;
}