#ifndef FREQUENCY_H
#define FREQUENCY_H
#define NUM_CHARS 256

int *countCharsOccurences(const char *source);
double getEntropy(const int *occurences);

#endif