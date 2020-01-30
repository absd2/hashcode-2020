#include <stdio.h>
#include <stdlib.h>

#define ll long long

void runFromFile(char *inputFilename, char *outputFilename, char *logFilename) {
    ll int i;

    // Loads input file.
    FILE *fRead = fopen(inputFilename, "rt");
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
    FILE *fWrite = fopen(outputFilename, "wt");
    if(!fWrite) {
        printf("Could not create output file.\n");
        exit(-1);
    }

    // Loads log file.
    FILE *fLog = fopen(logFilename, "wt");
    if(!fLog) {
        printf("Could not create log file.\n");
        exit(-1);
    }

    // Processes the answer.
    ll int *currentIndexes=NULL, *maxIndexes=NULL;
    ll int currentSum=0, currentAnswers=0, start=nPizzas-1, maxSum=0, maxAnswers=0;

    while(start>1) {
        // Looks for an answers by searching from the very last element to the back, and moves the startpoint step to the left as it iterates.
        for(i=start; i>=0; i--) {
            if(slices[i]+currentSum<=maxSlices) {
                currentSum+=slices[i];
                
                currentAnswers++;
                currentIndexes=(ll int *)realloc(currentIndexes, sizeof(ll int)*currentAnswers);
                currentIndexes[currentAnswers-1]=i;
            }
        }

        // Save step on the logfile.
        fprintf(fLog, "(slices[%lld]) currentSum=%lld | maxSum=%lld\n", start, currentSum, maxSum);

        // If the answer now found is bigger than the maximum answer, replaces it.
        if(currentSum>maxSum) {
            maxSum=currentSum;
            maxAnswers=currentAnswers;
            maxIndexes=(ll int *)realloc(maxIndexes, sizeof(ll int)*currentAnswers);

            for(i=0; i<currentAnswers; i++) {
                maxIndexes[i]=currentIndexes[i];
            }
        }

        // Resets variables for next iteration.
        currentSum=0;
        currentAnswers=0;
        currentIndexes=NULL;
        free(currentIndexes);
        
        // Moves startpoint one step to the left.
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

    // Releases all alocated memory.
    fclose(fRead);
    fclose(fWrite);
    fclose(fLog);
    free(slices);
    free(currentIndexes);
    free(maxIndexes);
}

int main() {
    int choice;
    
    // Shows menu and manages options that doesn't exist.
    while(choice<0 || choice >5) {
        system("clear");
        printf("AVAILABLE DATASETS:\n\n  1- Example.\n  2- Small.\n  3- Medium.\n  4- Quite Big.\n  5- Also Big.\n\n  0- All of them.\n\n--------------------\nChoose input file to run: ");
        scanf("%d", &choice);
    }

    // Handles available options.
    switch(choice) {
        case 1:
            printf("\nRunning example dataset..........");
            runFromFile("input/inputE.in", "output/outputE.out", "logs/logOutputE.out");
            printf("[OK]\n");
        break;
        case 2:
            printf("\nRunning small dataset............");
            runFromFile("input/inputS.in", "output/outputS.out", "logs/logOutputS.out");
            printf("[OK]\n");
        break;
        case 3:
            printf("\nRunning medium dataset...........");
            runFromFile("input/inputM.in", "output/outputM.out", "logs/logOutputM.out"); 
            printf("[OK]\n");
        break;
        case 4:
            printf("\nRunning quite big dataset........");
            runFromFile("input/inputQB.in", "output/outputQB.out", "logs/logOutputQB.out");
            printf("[OK]\n");
        break;
        case 5:
            printf("\nRunning also big dataset.........");
            runFromFile("input/inputAB.in", "output/outputAB.out", "logs/logOutputAB.out");
            printf("OK\n");
        break;

        // Option 0 was created to update all logs and output files if an update in the algorithm was done.
        case 0:
            printf("\nRunning example dataset..........");
            runFromFile("input/inputE.in", "output/outputE.out", "logs/logOutputE.out");
            printf("[OK]\n");

            printf("Running small dataset............");
            runFromFile("input/inputS.in", "output/outputS.out", "logs/logOutputS.out");
            printf("[OK]\n");

            printf("Running medium dataset...........");
            runFromFile("input/inputM.in", "output/outputM.out", "logs/logOutputM.out"); 
            printf("[OK]\n");

            printf("Running quite big dataset........");
            runFromFile("input/inputQB.in", "output/outputQB.out", "logs/logOutputQB.out");
            printf("[OK]\n");

            printf("Running also big dataset.........");
            runFromFile("input/inputAB.in", "output/outputAB.out", "logs/logOutputAB.out");
            printf("[OK]\n");
        break;
    }

    printf("\nTask fully completed.\n");
    return 0;
}
