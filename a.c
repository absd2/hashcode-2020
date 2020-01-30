#include <stdio.h>
#include <stdlib.h>

#define ll long long

void runFromFile(char *filename) {
    ll int i, j;

    // Loads input file.
    FILE *fRead = fopen(filename, "rt");
    if(!fRead) {
        printf("Input file could not be opened.\n");
        exit(-1);
    }

    // Reads input from file.
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

    // Loads log file.
    FILE *fLog = fopen("log/log.out", "wt");
    if(!fLog) {
        printf("Could not create log file.\n");
        exit(-1);
    }

    // Processes the answer.
    ll int *currentIndexes=NULL, *maxIndexes=NULL;
    ll int currentSum=0, currentAnswers=0, start=nPizzas-1, maxSum=0, maxAnswers=0;
    while(start>1) {
        // Looks for an answers by searching from the very last element to the back, and moves the beggining point one step to the left every iteration.
        for(i=start; i>=0; i--) {
            if(slices[i]+currentSum<maxSlices) {
                currentSum+=slices[i];
                
                currentAnswers++;
                currentIndexes=(ll int *)realloc(currentIndexes, sizeof(ll int)*currentAnswers);
                currentIndexes[currentAnswers-1]=i;
            }
        }

        fprintf(fLog, "cSum=%lld | maxSum=%lld\n", currentSum, maxSum);

        // If the answer now found is bigger than the maximum answer, replaces it.
        if(currentSum>maxSum) {
            maxSum=currentSum;
            maxAnswers=currentAnswers;
            maxIndexes=(ll int *)realloc(maxIndexes, sizeof(ll int)*currentAnswers);

            for(i=0; i<currentAnswers; i++) {
                maxIndexes[i]=currentIndexes[i];
            }
        }

        currentSum=0;
        currentAnswers=0;
        currentIndexes=NULL;
        free(currentIndexes);

        start--;
    }

    // Shows answer.
    fprintf(fWrite, "%lld\n", maxAnswers);
    for(i=0; i<maxAnswers; i++) {
        if(i==maxAnswers) {
            fprintf(fWrite, "%lld", maxIndexes[i]);
        }else{
            fprintf(fWrite, "%lld ", maxIndexes[i]);
        }
    }


    fclose(fRead);
    fclose(fWrite);
    free(slices);
    free(currentIndexes);
    free(maxIndexes);
}

int main() {
    runFromFile("input/inputAB.in");

    return 0;
}