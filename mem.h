#ifndef MEM_H
#define MEM_H

void *wmalloc(size_t size);
void *wrealloc(void *ptr, size_t size);
void *wcalloc(size_t size, size_t element_size);

#endif