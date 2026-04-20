#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mem.h"
#include "frequency.h"


// Funzione che calcola le occorrenze dei byte in un file.
// "offset" permette di saltare i primi N byte.
int *get_file_occurrences(const char* filename, int* occurrences, long offset) {
    for(int i = 0; i < 256; i++) {
        occurrences[i] = 0;
    }

    FILE *f = fopen(filename, "rb");
    if (!f) {
        fprintf(stderr, "Errore in apertura del file per l'entropia.\n");
        return;
    }

    if (offset > 0) {
        fseek(f, offset, SEEK_SET);
    }

    int c;
    while ((c = fgetc(f)) != EOF) {
        occurrences[c]++;
    }

    fclose(f);
    return occurances;
}


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

