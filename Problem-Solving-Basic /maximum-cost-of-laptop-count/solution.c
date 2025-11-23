#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxCost(int cost_count, int* cost, int labels_count, char** labels, int dailyCount) {
    int ans = 0;
    int cur_cnt = 0;
    int cur_cost = 0;
    
    for (int i = 0; i < cost_count; i++) {
        cur_cost += cost[i];
        
        if (strcmp(labels[i], "illegal") == 0) {
            continue;
        }
        
        cur_cnt += 1;
        
        if (cur_cnt == dailyCount) {
            if (cur_cost > ans) {
                ans = cur_cost;
            }
            cur_cnt = 0;
            cur_cost = 0;
        }
    }
    
    return ans;
}

int main() {
    int cost_count;
    scanf("%d", &cost_count);
    getchar(); // consume newline
    
    int* cost = (int*)malloc(cost_count * sizeof(int));
    for (int i = 0; i < cost_count; i++) {
        scanf("%d", &cost[i]);
        getchar(); // consume newline
    }
    
    int labels_count;
    scanf("%d", &labels_count);
    getchar(); // consume newline
    
    char** labels = (char**)malloc(labels_count * sizeof(char*));
    for (int i = 0; i < labels_count; i++) {
        labels[i] = (char*)malloc(100 * sizeof(char)); // assuming max label length is 100
        fgets(labels[i], 100, stdin);
        // Remove newline character if present
        size_t len = strlen(labels[i]);
        if (len > 0 && labels[i][len-1] == '\n') {
            labels[i][len-1] = '\0';
        }
    }
    
    int dailyCount;
    scanf("%d", &dailyCount);
    
    int result = maxCost(cost_count, cost, labels_count, labels, dailyCount);
    
    printf("%d\n", result);
    
    // Free allocated memory
    free(cost);
    for (int i = 0; i < labels_count; i++) {
        free(labels[i]);
    }
    free(labels);
    
    return 0;
}
