#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "decompress.h"


void decompress(const char *compressed_filename) {
    // Ripuliamo il nome del file di output rimuovendo l'estensione ".compressed"
    char output_filename[1024];
    strcpy(output_filename, compressed_filename);

    // Cerchiamo l'ultima occorrenza di ".compressed" nel nome del file
    char *extension_pos = strstr(output_filename, ".compressed");
    
    if(extension_pos == NULL){
        fprintf(stderr, "Errore: il file non è stato compresso usando questo programma.\n");
        exit(EXIT_FAILURE);
    } else{
        *extension_pos = '\0'; // rimuoviamo l'estensione
    }

    // Aggiungiamo l'estensione corretta per il file decompresso
    strcat(output_filename, ".txt");

    FILE *input_file = fopen(compressed_filename, "rb");
    if (!input_file) {
        fprintf(stderr, "Errore: impossibile aprire %s\n", compressed_filename);
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) {
        fprintf(stderr, "Errore creazione file di output.\n");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    // Leggiamo l'Header
    size_t original_length;
    fread(&original_length, sizeof(size_t), 1, input_file);

    int occurences[256];
    fread(occurences, sizeof(int), 256, input_file);

    // Ricostruiamo l'albero di Huffman a partire dalle frequenze lette dall'header
    HuffmanNode *root = buildHuffmanTree(occurences);

    
    unsigned char buffer;
    size_t written_chars = 0;
    HuffmanNode *current = root;

    // Caso limite: il file conteneva un solo tipo di carattere ripetuto
    if (isLeaf(root)) {
        for (size_t i = 0; i < original_length; i++) {
            fputc(root->character, output_file);
        }
        written_chars = original_length;
    }

    
    while (written_chars < original_length) {
        // Leggiamo un byte alla volta
        if (fread(&buffer, sizeof(unsigned char), 1, input_file) != 1) {
            break; 
        }

        /* Estraiamo i bit da sinistra (MSB, indice 7) a destra (LSB, indice 0)
           in quanto in fase di compressione li spostavamo verso sinistra.
        */  
        for (int i = 7; i >= 0; i--) {
            int bit = (buffer >> i) & 1;

            if (bit == 0) {
                current = current->left;
            } else {
                current = current->right;
            }

            // Nelle foglie troveremo le lettere originali
            if (isLeaf(current)) {
                fputc(current->character, output_file); // scriviamo su file
                written_chars++;                     // aggiorniamo il contatore
                current = root;                      // torniamo in cima all'albero per il prossimo carattere
                
                // Se abbiamo raggiunto la lunghezza originale, ignoriamo i bit di padding
                if (written_chars == original_length) {
                    break; 
                }
            }
        }
    }

    
    fclose(input_file);
    fclose(output_file);
    freeHuffmanTree(root);

    printf("File decompresso con successo in: %s\n", output_filename);
}