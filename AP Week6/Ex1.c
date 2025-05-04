#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function declarations
int max(int a, int b);
int cutRodTopDown(int price[], int n, int memo[], int cuts[]);
int cutRodBottomUp(int price[], int n, int cuts[]);
void printCuts(int cuts[], int n);

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Top-down approach with memoization
int cutRodTopDown(int price[], int n, int memo[], int cuts[]) {
    if (n <= 0) return 0;
    if (memo[n] != -1) return memo[n];
    
    int maxValue = INT_MIN;
    for (int i = 0; i < n; i++) {
        int currentValue = price[i] + cutRodTopDown(price, n-i-1, memo, cuts);
        if (currentValue > maxValue) {
            maxValue = currentValue;
            cuts[n] = i + 1;
        }
    }
    memo[n] = maxValue;
    return maxValue;
}

// Bottom-up approach with tabulation
int cutRodBottomUp(int price[], int n, int cuts[]) {
    int dp[n + 1];
    dp[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        int maxValue = INT_MIN;
        for (int j = 0; j < i; j++) {
            int currentValue = price[j] + dp[i-j-1];
            if (currentValue > maxValue) {
                maxValue = currentValue;
                cuts[i] = j + 1;
            }
        }
        dp[i] = maxValue;
    }
    return dp[n];
}

// Function to print the optimal cuts
void printCuts(int cuts[], int n) {
    printf("Optimal cuts: ");
    while (n > 0) {
        printf("%d ", cuts[n]);
        n = n - cuts[n];
    }
    printf("\n");
}

int main() {
    int n = 10;
    // printf("Enter the length of the rod: ");
    // scanf("%d", &n);
    
    int price[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

    // printf("Enter the prices for lengths 1 to %d:\n", n);
    // for (int i = 0; i < n; i++) {
    //     scanf("%d", &price[i]);
    // }
    
    // Arrays to store the cuts
    int cutsTopDown[n + 1];
    int cutsBottomUp[n + 1];
    
    // Initialize memoization array for top-down
    int *memo = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
        cutsTopDown[i] = 0;
        cutsBottomUp[i] = 0;
    }
    
    // Top-down approach
    printf("\n--- Top-down approach ---\n");
    int maxProfitTopDown = cutRodTopDown(price, n, memo, cutsTopDown);
    printf("Maximum profit: %d\n", maxProfitTopDown);
    printCuts(cutsTopDown, n);
    
    // Bottom-up approach
    printf("\n--- Bottom-up approach ---\n");
    int maxProfitBottomUp = cutRodBottomUp(price, n, cutsBottomUp);
    printf("Maximum profit: %d\n", maxProfitBottomUp);
    printCuts(cutsBottomUp, n);
    
    free(memo);
    return 0;
}

