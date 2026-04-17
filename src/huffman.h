#include <stdbool.h>
#ifndef HUFFMAN_H
#define HUFFMAN_H
#define MAX_SYMBOLS 256

typedef struct HuffmanNode {
    unsigned char character;      // il carattere originale
    int frequency;       // la frequenza del carattere
    struct HuffmanNode *left; 
    struct HuffmanNode *right;   
} HuffmanNode;


typedef struct MinHeap MinHeap;

HuffmanNode *createNode(unsigned char character, unsigned int frequency);
HuffmanNode *extractMin(MinHeap *minHeap);
HuffmanNode *buildHuffmanTree(int *occurences);
MinHeap *createMinHeap(int capacity);
bool isLeaf(HuffmanNode *node);
void swapNodes(HuffmanNode **x, HuffmanNode **y);
void minHeapify(MinHeap *minHeap, int index);
void minHeapInsert(MinHeap *minHeap, HuffmanNode *node);
void createMap(HuffmanNode *root, char *current_code, int depth, char map[MAX_SYMBOLS][MAX_SYMBOLS]);
void freeHuffmanTree(HuffmanNode *root);

#endif