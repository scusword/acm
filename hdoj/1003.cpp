#include <cstdio>

int A[100000];
int N;
int dp[100000];
int dp_s[100000];
int main() {
    int t;
    int current_max;
    int current_start;
    int current_end;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        scanf("%d", &N);
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[j]);
        }
        current_max = A[0];
        current_start = 0;
        current_end = 0;
        dp[0] = A[0];
        dp_s[0] = 0;
        for (int k = 1; k < N; k++) {
            if (dp[k - 1] >= 0) {
                dp[k] = dp[k - 1] + A[k];
                dp_s[k] = dp_s[k - 1];
            } else {
                dp[k] = A[k];
                dp_s[k] = k;
            }
            if (dp[k] > current_max) {
                current_max = dp[k];
                current_start = dp_s[k];
                current_end = k;
            }
        }
        printf("Case %d:\n%d %d %d\n", i, current_max, current_start + 1, current_end + 1);
        if (i != t) {
            printf("\n");
        }
    }
    return 0;
}