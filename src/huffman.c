#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"
#include "frequency.h"
#include "huffman.h"


typedef struct HuffmanNode {
    unsigned char character;      // il carattere originale
    int frequency;       // la frequenza del carattere
    struct HuffmanNode *left; 
    struct HuffmanNode *right;   
} HuffmanNode;


typedef struct MinHeap {
    unsigned int size;      // numero attuale di nodi nel minHeap
    unsigned int capacity;  // capacità massima
    HuffmanNode **array;    // array di puntatori ai nodi di Huffman
} MinHeap;


HuffmanNode *createNode(unsigned char character, unsigned int frequency) {
    HuffmanNode *newNode = (HuffmanNode*)wmalloc(sizeof(HuffmanNode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->character = character;
    newNode->frequency = frequency;
    return newNode;
}

HuffmanNode *extractMin(MinHeap *minHeap){
    HuffmanNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    
    return temp;
}



MinHeap *createMinHeap(int capacity){
    MinHeap *minHeap = (MinHeap*)wmalloc(sizeof(MinHeap));
    minHeap->size = 0;                      // numero di elementi attualmente presenti
    minHeap->capacity = capacity;           // capacità massima, ovvero il numero di caratteri diversi che possono essere presenti
    minHeap->array = (HuffmanNode**)wmalloc(sizeof(HuffmanNode*)*minHeap->capacity); // array di puntatori ai nodi di Huffman, che rappresentano i nodi dell'heap
    return minHeap;
}


bool isLeaf(HuffmanNode *node){
    return (!node->left && !node->right);
}


void swapNodes(HuffmanNode **x, HuffmanNode **y){
    HuffmanNode *temp = *x;
    *x = *y;
    *y = temp;
}



void minHeapify(MinHeap *minHeap, int index){                       // agiamo in maniera analoga all'insert, ma partendo dall'inizio dell'heap
    int smallest = index;                                                                               
    int left = 2*index + 1;
    int right = 2*index + 2;

    if(left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency){      // il genitore viene confrontato con i figli.
        smallest = left;
    }

    if(right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency){
        smallest = right;
    }

    if(smallest != index){                                                                                  // se il genitore non è il minore tra i 3, il nodo di
        swapNodes(&minHeap->array[smallest], &minHeap->array[index]);                                       // indice index non è ancora al suo posto nell'heap.
        minHeapify(minHeap, smallest);
    }
}


void minHeapInsert(MinHeap *minHeap, HuffmanNode *node){
    int i = minHeap->size;                                                      // comininciamo i confronti partendo dall'ultimo elemento del minHeap
    minHeap->size++;                                                           

    while(i && node->frequency < minHeap->array[(i-1) / 2]->frequency){         // l'insert avviene confrontando i nodi "genitori". se il nodo da inserire ha 
        minHeap->array[i] = minHeap->array[(i-1) / 2];                          // una frequenza minore, il genitore si sposta per fare spazio al nuovo nodo.
        i = (i-1) / 2;                                                          // l'insert avverrà in tempo logaritmico.
    }

    minHeap->array[i] = node;
}


HuffmanNode *buildHuffmanTree(int *occurences){
    HuffmanNode *parent, *left, *right;
    MinHeap *minHeap = createMinHeap(NUM_CHARS);

    for(int i = 0; i < NUM_CHARS; i++){
        if(occurences[i] > 0){
            HuffmanNode *newNode = createNode((unsigned char) i, occurences[i]);
            minHeapInsert(minHeap, newNode);        
        }
    }

    if(minHeap->size == 1){
        parent = extractMin(minHeap);
        free(minHeap->array);
        free(minHeap);
        return parent;
    }

    while(minHeap->size > 1){
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        parent = createNode('\0', left->frequency + right->frequency);   // del genitore ci interessa solo la frequenza, ovvero la somma dei figli.
        parent->left = left;
        parent->right = right;

        minHeapInsert(minHeap, parent);     // il genitore viene inserito nuovamente nel minHeap, in modo da essere confrontato con gli altri nodi e posizionato correttamente.
    }

    parent = extractMin(minHeap);       // quando rimane un solo nodo, avremo la radice.

    free(minHeap->array);
    free(minHeap);

    return parent;
}


void createMap(HuffmanNode *root, char *current_code, int depth, char map[MAX_SYMBOLS][MAX_SYMBOLS]){
    if(root == NULL) return;

    if(root->left){
        current_code[depth] = '0';        // se il nodo ha un figlio sinistro, aggiungiamo '0' al codice corrente 
        createMap(root->left, current_code, depth + 1, map);           // e continuiamo a scendere nell'albero fino ad incontrare una foglia
    }

    if(root->right){
        current_code[depth] = '1';
        createMap(root->right, current_code, depth + 1, map);
    }

    if(isLeaf(root)){
        current_code[depth] = '\0';       // quando incontriamo una foglia, il codice corrente è completo e viene salvato nella mappa
        
        if(depth == 0) {        // caso limite in cui abbiamo un solo carattere, a cui assegnamo il codice "0".
            strcpy(map[root->character], "0");
        } else{
            strcpy(map[root->character], current_code);     // altrimenti, il codice è quello costruito durante la discesa nell'albero.
        }
    }

}

void freeHuffmanTree(HuffmanNode *root){
    if(root == NULL) return;
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    free(root);
}
