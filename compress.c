#include <stdio.h>
#include <stdlib.h>


void compress(const char *input_filename, const char *source, int *occurances, char **map){
    char output_filename[1024];
    sprintf(output_filename, "%s.compressed", input_filename);

    FILE *output_file = fopen(output_filename, "wb");
    if(!output_file){
        fprintf(stderr, "Couldn't create output file.\n");
        exit(EXIT_FAILURE);
    }

    /* Header del file compresso.
       Salviamo sia la lunghezza del testo originale che
       le frequenze, in modo da poter succesivamente decomprimere
       decomprimere il file ricostruendo l'albero di Huffman. 
    */
    size_t original_length = strlen(source);
    fwrite(&original_length, sizeof(size_t), 1, output_file);   
    fwrite(occurances, sizeof(int), 256, output_file);    
}