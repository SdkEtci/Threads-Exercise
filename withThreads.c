#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>  

#define NUM_THREADS 3 // Number of physical core - 1

int errorNum = 0;
int warningNum = 0;
int infoNum = 0;

pthread_mutex_t mtx;

// Thread function
void* count(void* arg) {
    char* line = (char*)arg;

    pthread_mutex_lock(&mtx);

    if (strstr(line, "ERROR") != NULL) {
        errorNum++;
    } else if (strstr(line, "WARN") != NULL) {
        warningNum++;
    } else {
        infoNum++;
    }

    pthread_mutex_unlock(&mtx); 

    free(line);  // Clear dynamic memory (line data)

    return NULL;
}

int main() {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mtx, NULL);

    FILE *file = fopen("Hadoop_2k.log", "r");
    if (file == NULL) {
        perror("File cannot opened.");
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t len = 0;
    int threadIndex = 0;

    while (getline(&line, &len, file) != -1) {
        // Copy line (dynamic memory allocation with strdup)
        char* lineCopy = strdup(line);

        // Create thread and pass the line as argument
        pthread_create(&threads[threadIndex], NULL, count, lineCopy);
        threadIndex = (threadIndex + 1) % NUM_THREADS;
    }

    free(line);  // Clear dynamic memory (memory allocated by getline)


    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;


    printf("Error: %d\n", errorNum);
    printf("Warning: %d\n", warningNum);
    printf("Info: %d\n", infoNum);
    printf("Time taken: %f seconds\n", cpu_time_used);


    FILE *outputFile = fopen("outputWithThreads.txt", "w");
    if (outputFile == NULL) {
        perror("Output file cannot opened.");
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "Error: %d\n", errorNum);
    fprintf(outputFile, "Warning: %d\n", warningNum);
    fprintf(outputFile, "Info: %d\n", infoNum);
    fprintf(outputFile, "Time taken: %f seconds\n", cpu_time_used);

    fclose(outputFile);  
    pthread_mutex_destroy(&mtx);
    fclose(file);
    return 0;
}