#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  

int errorNum = 0;
int warningNum = 0;
int infoNum = 0;

int main() {
    clock_t start, end;  
    double cpu_time_used;
    start = clock();

    FILE *file = fopen("Hadoop_2k.log", "r");
    if (file == NULL) {
        perror("File cannot opened.");
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        if (strstr(line, "ERROR") != NULL) {
            errorNum++;
        } else if (strstr(line, "WARN") != NULL) {
            warningNum++;
        } else {
            infoNum++;
        }
    }

    free(line); 
    fclose(file);

    end = clock();  
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;  

    
    printf("Error: %d\n", errorNum);
    printf("Warning: %d\n", warningNum);
    printf("Info: %d\n", infoNum);
    printf("Time taken: %f seconds\n", cpu_time_used);

   
    FILE *outputFile = fopen("outputNonThreads.txt", "w");
    if (outputFile == NULL) {
        perror("Output file cannot opened.");
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "Error: %d\n", errorNum);
    fprintf(outputFile, "Warning: %d\n", warningNum);
    fprintf(outputFile, "Info: %d\n", infoNum);
    fprintf(outputFile, "Time taken: %f seconds\n", cpu_time_used);

    fclose(outputFile);  

    return 0;
}