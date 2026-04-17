#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include "file_utils.h"

/* TODO: aprire il file in modalità binaria per evitare problemi con i caratteri \r\n , 
 * inoltre aggiungere un size_t file_size come parametro di output per restituire la 
 * dimensione del file letto, in modo da evitare di dover chiamare strlen().
 * Così facendo la compressione sarà 100% lossless.
*/
char *readFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        fprintf(stderr, "File %s not found.\n", filename);
        exit(EXIT_FAILURE);
    }

    /* Move the file pointer to the very end of the file */
    if(fseek(fp, 0, SEEK_END) != 0) {                                               
        fprintf(stderr, "Error: Cannot seek in file '%s'.\n", filename);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    long size = ftell(fp);
    rewind(fp);

    char *buffer = wmalloc(size + 1);                                               

    fread(buffer, sizeof(char), size, fp);
    buffer[size] = '\0';
    fclose(fp);

    return buffer;
}
