#include <stdio.h>
#include <stdlib.h>

// Top-down approach with memoization
int knapsackTopDown(int W, int wt[], int val[], int n, int **dp) {
    // Base case
    if (n == 0 || W == 0)
        return 0;
    
    // If already computed
    if (dp[n][W] != -1)
        return dp[n][W];
    
    // If weight of item is more than capacity
    if (wt[n-1] > W)
        return dp[n][W] = knapsackTopDown(W, wt, val, n-1, dp);
    
    // Return maximum of two cases:
    // 1) nth item included
    // 2) nth item not included
    else {
        dp[n][W] = max(val[n-1] + knapsackTopDown(W - wt[n-1], wt, val, n-1, dp),
                       knapsackTopDown(W, wt, val, n-1, dp));
        return dp[n][W];
    }
}

// Bottom-up approach
void knapsackBottomUp(int W, int wt[], int val[], int n) {
    int dp[n + 1][W + 1];
    int selected[n];
    int i, w;

    // Build table dp[][] in bottom-up manner
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i-1] <= w)
                dp[i][w] = max(val[i-1] + dp[i-1][w-wt[i-1]], dp[i-1][w]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }

    // Reconstruct the solution
    int res = dp[n][W];
    w = W;
    for (i = 0; i < n; i++)
        selected[i] = 0;

    for (i = n; i > 0 && res > 0; i--) {
        if (res != dp[i-1][w]) {
            selected[i-1] = 1;
            res -= val[i-1];
            w -= wt[i-1];
        }
    }

    // Print the solution
    printf("\nBottom-up approach:\n");
    printf("Maximum value: %d\n", dp[n][W]);
    printf("Selected items (weight, value): ");
    for (i = 0; i < n; i++) {
        if (selected[i])
            printf("(%d,%d) ", wt[i], val[i]);
    }
    printf("\n");
}

// Utility function to reconstruct solution for top-down approach
void printTopDownSolution(int W, int wt[], int val[], int n, int **dp) {
    int i = n, w = W;
    printf("\nTop-down approach:\n");
    printf("Maximum value: %d\n", dp[n][W]);
    printf("Selected items (weight, value): ");
    
    while (i > 0 && w > 0) {
        if (dp[i][w] != dp[i-1][w]) {
            printf("(%d,%d) ", wt[i-1], val[i-1]);
            w -= wt[i-1];
        }
        i--;
    }
    printf("\n");
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n, W, i;
    
    printf("Enter number of items: ");
    scanf("%d", &n);
    
    int *wt = (int *)malloc(n * sizeof(int));
    int *val = (int *)malloc(n * sizeof(int));
    
    printf("Enter weight and value for each item:\n");
    for (i = 0; i < n; i++) {
        printf("Item %d: ", i + 1);
        scanf("%d %d", &wt[i], &val[i]);
    }
    
    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    // Allocate memory for dp table (top-down)
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((W + 1) * sizeof(int));
        for (int j = 0; j <= W; j++)
            dp[i][j] = -1;
    }

    // Solve using top-down approach
    knapsackTopDown(W, wt, val, n, dp);
    printTopDownSolution(W, wt, val, n, dp);

    // Solve using bottom-up approach
    knapsackBottomUp(W, wt, val, n);

    // Free allocated memory
    for (i = 0; i <= n; i++)
        free(dp[i]);
    free(dp);
    free(wt);
    free(val);

    return 0;
}