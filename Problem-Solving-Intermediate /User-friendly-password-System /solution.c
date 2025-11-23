#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define P 131
#define M 1000000007
#define MAX_PW_LENGTH 11
#define APPENDS_COUNT 63

// Precompute P powers
long long PP[MAX_PW_LENGTH];

void precompute_pp() {
    PP[0] = 1;
    for (int i = 1; i < MAX_PW_LENGTH; i++) {
        PP[i] = (PP[i-1] * P) % M;
    }
}

// Calculate hash for a password
long long calc_hash(const char* pw) {
    int len = strlen(pw);
    long long cur_h = 0;
    
    for (int i = 0; i < len; i++) {
        cur_h = (cur_h + (long long)pw[len - 1 - i] * PP[i]) % M;
    }
    return cur_h;
}

int* authEvents(int events_rows, int events_columns, char*** events, int* result_count) {
    precompute_pp();
    
    // Initialize APPENDS array
    char appends[APPENDS_COUNT][2] = {""};
    int idx = 1;
    
    // Add lowercase letters
    for (char c = 'a'; c <= 'z'; c++) {
        appends[idx][0] = c;
        appends[idx][1] = '\0';
        idx++;
    }
    
    // Add uppercase letters  
    for (char c = 'A'; c <= 'Z'; c++) {
        appends[idx][0] = c;
        appends[idx][1] = '\0';
        idx++;
    }
    
    // Add digits
    for (char c = '0'; c <= '9'; c++) {
        appends[idx][0] = c;
        appends[idx][1] = '\0';
        idx++;
    }
    
    long long* good_hashes = NULL;
    int hash_count = 0;
    int* ans = malloc(events_rows * sizeof(int));
    int ans_idx = 0;
    
    for (int i = 0; i < events_rows; i++) {
        char* event_type = events[i][0];
        char* value = events[i][1];
        
        if (strcmp(event_type, "setPassword") == 0) {
            // Free previous hashes if they exist
            if (good_hashes != NULL) {
                free(good_hashes);
            }
            
            // Calculate all possible hashes for the password + each append character
            hash_count = APPENDS_COUNT;
            good_hashes = malloc(APPENDS_COUNT * sizeof(long long));
            
            for (int j = 0; j < APPENDS_COUNT; j++) {
                char temp_pw[MAX_PW_LENGTH + 2]; // +1 for append char, +1 for null terminator
                strcpy(temp_pw, value);
                strcat(temp_pw, appends[j]);
                good_hashes[j] = calc_hash(temp_pw);
            }
        } 
        else if (strcmp(event_type, "authorize") == 0) {
            long long auth_hash = atoll(value);
            int found = 0;
            
            for (int j = 0; j < hash_count; j++) {
                if (good_hashes[j] == auth_hash) {
                    found = 1;
                    break;
                }
            }
            
            ans[ans_idx++] = found;
        }
    }
    
    // Clean up
    if (good_hashes != NULL) {
        free(good_hashes);
    }
    
    *result_count = ans_idx;
    return ans;
}

// Helper function to read input and call authEvents
int main() {
    int events_rows, events_columns;
    
    // Read dimensions
    scanf("%d", &events_rows);
    scanf("%d", &events_columns);
    getchar(); // Consume newline
    
    // Allocate memory for events
    char*** events = malloc(events_rows * sizeof(char**));
    for (int i = 0; i < events_rows; i++) {
        events[i] = malloc(events_columns * sizeof(char*));
        for (int j = 0; j < events_columns; j++) {
            events[i][j] = malloc(100 * sizeof(char));
        }
    }
    
    // Read events
    for (int i = 0; i < events_rows; i++) {
        char line[256];
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = 0; // Remove newline
        
        // Simple tokenization - assuming exactly 2 tokens per line
        char* token = strtok(line, " ");
        if (token != NULL) {
            strcpy(events[i][0], token);
            token = strtok(NULL, " ");
            if (token != NULL) {
                strcpy(events[i][1], token);
            }
        }
    }
    
    int result_count;
    int* result = authEvents(events_rows, events_columns, events, &result_count);
    
    // Output results
    for (int i = 0; i < result_count; i++) {
        printf("%d\n", result[i]);
    }
    
    // Free memory
    free(result);
    for (int i = 0; i < events_rows; i++) {
        for (int j = 0; j < events_columns; j++) {
            free(events[i][j]);
        }
        free(events[i]);
    }
    free(events);
    
    return 0;
}
