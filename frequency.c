#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mem.h"
#include "frequency.h"


int *countCharsOccurences(const char *source){
    int *occurences = (int*) wcalloc(NUM_CHARS,sizeof(int));

    for(int i = 0; source[i] != '\0'; i++){
        int idx = (unsigned char)source[i];
        occurences[idx]++;
    }

    return occurences;
}

double getEntropy(const int* occurences){
    if (occurences == NULL) return 0.0;

    int chars_num = 0;
    for(int i = 0; i < NUM_CHARS; i++){
        chars_num += occurences[i];
    }

    double entropy = 0;
    for(int i = 0; i < NUM_CHARS; i++){
        int entry = occurences[i];
        if (entry != 0 ){
            double char_probability = (double) entry/chars_num;
            entropy += char_probability * log2(char_probability);
        }
    }

    return -entropy;
}