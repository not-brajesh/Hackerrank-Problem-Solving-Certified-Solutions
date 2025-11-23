#include <stdio.h>
#include <stdlib.h>

// Comparison function for descending order
int compare_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

long minTime(int files[], int files_count, int numCores, int limit) {
    // Allocate arrays for divisible and non-divisible files
    int *x = malloc(files_count * sizeof(int));
    int *y = malloc(files_count * sizeof(int));
    int x_count = 0, y_count = 0;
    
    // Separate files into divisible and non-divisible by numCores
    for (int i = 0; i < files_count; i++) {
        if (files[i] % numCores == 0) {
            x[x_count++] = files[i];
        } else {
            y[y_count++] = files[i];
        }
    }
    
    // Sort divisible files in descending order
    qsort(x, x_count, sizeof(int), compare_desc);
    
    // Calculate total time
    long total_time = 0;
    
    // Process first 'limit' divisible files with parallel processing
    for (int i = 0; i < limit && i < x_count; i++) {
        total_time += x[i] / numCores;
    }
    
    // Process remaining divisible files without parallel processing
    for (int i = limit; i < x_count; i++) {
        total_time += x[i];
    }
    
    // Process non-divisible files
    for (int i = 0; i < y_count; i++) {
        total_time += y[i];
    }
    
    free(x);
    free(y);
    
    return total_time;
}

int main() {
    int files_count;
    scanf("%d", &files_count);
    
    int *files = malloc(files_count * sizeof(int));
    for (int i = 0; i < files_count; i++) {
        scanf("%d", &files[i]);
    }
    
    int numCores, limit;
    scanf("%d", &d", &numCores);
    scanf("%d", &limit);
    
    long result = minTime(files, files_count, numCores, limit);
    printf("%ld\n", result);
    
    free(files);
    return 0;
}
