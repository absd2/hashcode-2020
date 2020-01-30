#include <stdio.h>
#include <stdlib.h>

#define ll long long

void runFromFile(char *filename) {
    // Loads input file.
    FILE *fRead = fopen(filename, "rt");
    if(!fRead) {
        printf("Input file could not be opened.\n");
        exit(-1);
    }

    // Reads input from file.
    ll int i;
    ll int maxSlices, nPizzas;
    
    fscanf(fRead, "%lld %lld", &maxSlices, &nPizzas);
    ll int *slices=(ll int *)malloc(sizeof(ll int)*nPizzas);
    
    for(i=0; i<nPizzas; i++) {
        fscanf(fRead, "%lld", &slices[i]);
    }

    // Loads output file.
    FILE *fWrite = fopen("output/output.out", "wt");
    if(!fWrite) {
        printf("Could not create output file.\n");
        exit(-1);
    }

    // Processes the answer.
    ll int *indexes=NULL;
    ll int sum=0, nAnswers=0;
    for(i=nPizzas-1; i>=0; i--) {
        if(slices[i]+sum<maxSlices) {
            sum+=slices[i];
            
            nAnswers++;
            indexes=(ll int *)realloc(indexes, sizeof(ll int)*nAnswers);
            indexes[nAnswers-1]=i;
        }
    }

    // Shows answer.
    fprintf(fWrite, "%lld\n", nAnswers);
    for(i=0; i<nAnswers; i++) {
        fprintf(fWrite, "%lld ", indexes[i]);
    }


    fclose(fRead);
    fclose(fWrite);
    free(slices);
}

int main() {
    runFromFile("input/inputAB.in");

    return 0;
}