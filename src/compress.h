#ifndef COMPRESS_H
#define COMPRESS_H
#define MAX_SYMBOLS 256

void compress(const char *input_filename, const char *source, int *occurances, char map[MAX_SYMBOLS][MAX_SYMBOLS]);

#endif