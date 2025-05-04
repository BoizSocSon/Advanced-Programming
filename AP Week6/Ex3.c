#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 100

// Function declarations
int lcs_length_topdown(char *X, char *Y, int m, int n, int **dp);
void print_lcs_topdown(char *X, char *Y, int m, int n, int **dp);
void lcs_bottomup(char *X, char *Y, int m, int n);

// Top-down approach with memoization
int lcs_length_topdown(char *X, char *Y, int m, int n, int **dp) {
    if (m == 0 || n == 0)
        return 0;
    
    if (dp[m][n] != -1)
        return dp[m][n];
    
    if (X[m-1] == Y[n-1])
        dp[m][n] = 1 + lcs_length_topdown(X, Y, m-1, n-1, dp);
    else
        dp[m][n] = (lcs_length_topdown(X, Y, m-1, n, dp) > 
                    lcs_length_topdown(X, Y, m, n-1, dp)) ? 
                    lcs_length_topdown(X, Y, m-1, n, dp) : 
                    lcs_length_topdown(X, Y, m, n-1, dp);
    
    return dp[m][n];
}

// Print LCS using top-down approach
void print_lcs_topdown(char *X, char *Y, int m, int n, int **dp) {
    char lcs[MAX_LENGTH];
    int index = dp[m][n];
    lcs[index] = '\0';
    
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i-1] == Y[j-1]) {
            lcs[index-1] = X[i-1];
            i--; j--; index--;
        }
        else if (dp[i-1][j] > dp[i][j-1])
            i--;
        else
            j--;
    }
    
    printf("LCS: %s\n", lcs);
}

// Bottom-up approach
void lcs_bottomup(char *X, char *Y, int m, int n) {
    int dp[MAX_LENGTH][MAX_LENGTH];
    int i, j;
    
    // Build dp table
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i-1] == Y[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = (dp[i-1][j] > dp[i][j-1]) ? dp[i-1][j] : dp[i][j-1];
        }
    }
    
    // Reconstruct LCS
    char lcs[MAX_LENGTH];
    int index = dp[m][n];
    lcs[index] = '\0';
    
    i = m; j = n;
    while (i > 0 && j > 0) {
        if (X[i-1] == Y[j-1]) {
            lcs[index-1] = X[i-1];
            i--; j--; index--;
        }
        else if (dp[i-1][j] > dp[i][j-1])
            i--;
        else
            j--;
    }
    
    printf("LCS: %s\n", lcs);
}

int main() {
    char X[] = "ABCDGH";
    char Y[] = "AEDFHR";
    int m = strlen(X);
    int n = strlen(Y);
    
    // Allocate memory for top-down dp table
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        for (int j = 0; j <= n; j++)
            dp[i][j] = -1;
    }
    
    printf("Top-down approach:\n");
    lcs_length_topdown(X, Y, m, n, dp);
    print_lcs_topdown(X, Y, m, n, dp);
    
    printf("\nBottom-up approach:\n");
    lcs_bottomup(X, Y, m, n);
    
    // Free allocated memory
    for (int i = 0; i <= m; i++)
        free(dp[i]);
    free(dp);
    
    return 0;
}