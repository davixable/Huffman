#include <stdio.h>
#include <stdlib.h>
#include "mem.h"


void *wmalloc(size_t size) {
    if (size == 0) size = 1;                                       
    
    void *newPtr = malloc(size);
    if (newPtr == NULL) {
        fprintf(stderr, "OOM. Couldn't allocate %zu bytes.\n", size);
        exit(EXIT_FAILURE);
    }

    return newPtr;
}

void *wrealloc(void *ptr, size_t size) {
    if (size == 0) size = 1;             
    
    void *newPtr = realloc(ptr, size);
    if (newPtr == NULL) {
        fprintf(stderr, "OOM. Couldn't reallocate %zu bytes.\n", size);
        exit(EXIT_FAILURE);
    }
    
    return newPtr;
}

void *wcalloc(size_t size, size_t element_size){
    if (size == 0) size = 1;

    void *newPtr = calloc(size, element_size);
    if (newPtr == NULL){
        fprintf(stderr, "OOm. Could't allocate %zu bytes. \n", size);
        exit(EXIT_FAILURE);
    }

    return newPtr;
}