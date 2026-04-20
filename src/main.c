#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "mem.h"
#include "file_utils.h"
#include "frequency.h"
#include "compress.h"
#include "decompress.h"
#define MAX_SYMBOLS 256

int main(int argc, char **argv){
    if(argc == 2){
        char *source = readFromFile(argv[1]);

        char map[MAX_SYMBOLS][MAX_SYMBOLS] = {0};
        char current_code[256];
        int *occurences = countCharsOccurences(source);

        HuffmanNode *root = buildHuffmanTree(occurences);
        createMap(root, current_code, 0, map);
        compress(argv[1], source, occurences, map);

        free(source);
        free(occurences);
        exit(EXIT_SUCCESS);
    }
    
    if (argc == 3 && strcmp(argv[2], "-decode") == 0) {
        decompress(argv[1]);
        exit(EXIT_SUCCESS);
    }

    fprintf(stderr, "Error. Usage: <program_name> <file_name> || <program_name> <file_name> -decode\n");
    exit(EXIT_FAILURE);
}