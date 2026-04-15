#include <stdio.h>
#include <stdlib.h>

#include "huffman.h"
#include "mem.h"
#include "file_utils.h"
#include "frequency.h"
#include "compress.h"


int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "Error. Usage: <program_name> <file_name>\n");
        exit(EXIT_FAILURE);
    }

    char map[256][256] = {0};
    char current_code[256];

    char *source = readFromFile(argv[1]);
    int *occurences = countCharsOccurences(source);
    double entropy = getEntropy(occurences);

    HuffmanNode *root = buildHuffmanTree(occurences);
    createMap(root, current_code, 0, map);
    compress(argv[1], source, occurances, map);

    free(source);
    free(occurences);
    exit(EXIT_SUCCESS);
}