#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"
#include "frequency.h"

void compress(const char *input_filename, const char *source, int *occurances, char map[MAX_SYMBOLS][MAX_SYMBOLS]){
    char output_filename[1024];
    strcpy(output_filename, input_filename);

    // Cerchiamo ".txt" nel nome del file di input
    char *extension_pos = strstr(output_filename, ".txt");
    
    if(extension_pos == NULL){
        fprintf(stderr, "Errore: il file non è stato compresso usando questo programma.\n");
        exit(EXIT_FAILURE);
    } else{
        *extension_pos = '\0'; // rimuoviamo l'estensione
    }

    // Aggiungiamo l'estensione corretta per il file compresso
    strcat(output_filename, ".compressed");


    FILE *output_file = fopen(output_filename, "wb");
    if(!output_file){
        fprintf(stderr, "Couldn't create output file.\n");
        exit(EXIT_FAILURE);
    }

    /* Header del file compresso.
       Salviamo sia la lunghezza del testo originale che
       le frequenze, in modo da poter succesivamente decomprimere
       il file ricostruendo l'albero di Huffman. 
    */
    size_t original_length = strlen(source);
    fwrite(&original_length, sizeof(size_t), 1, output_file);   
    fwrite(occurances, sizeof(int), 256, output_file);  
    
    // Compressione del file usando un buffer di 8 bit
    unsigned char buffer = 0; 
    int bit_count = 0;        

    for (size_t i = 0; i < original_length; i++) {
        unsigned char c = (unsigned char)source[i];         
        char *code = map[c];                                // accedo alla stringa binaria associata al carattere

        for (int j = 0; code[j] != '\0'; j++) {            
            buffer = buffer << 1;                           // facciamo spazio spostando tutto a sinistra di 1 bit
            if (code[j] == '1') {
                buffer = buffer | 1;                        // accendiamo l'ultimo bit più a destra
            }
            
            bit_count++;

            if (bit_count == 8) {                           // se il byte è pieno, possiamo scriverlo su file
                fwrite(&buffer, sizeof(unsigned char), 1, output_file);
                buffer = 0;    
                bit_count = 0; 
            }
        }
    }

    // Padding degli ultimi bit rimasti in sospeso
    if (bit_count > 0) {
        buffer = buffer << (8 - bit_count); 
        fwrite(&buffer, sizeof(unsigned char), 1, output_file);
    }

    fclose(output_file);
    printf("File compresso salvato con successo.\n");

    double input_entropy = getEntropy(occurances);
    double output_entropy = getEntropy(get_file_occurrences(output_filename, occurances, 256));

    printf("Entropia del file originale: %.2f\n", input_entropy);
    printf("Entropia del file compresso: %.2f\n", output_entropy);

}
