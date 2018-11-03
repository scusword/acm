#include <cstdio>
#include <cstring>
#include <algorithm>

int N;
int number_tower[101][101];
int dp[101][101];
int dp_level_max[101];

int main() {
    int C;
    scanf("%d", &C);
    memset(dp, -1, sizeof(dp));
    memset(dp_level_max, 0, sizeof(dp_level_max));
    while (C--) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= i; j++) {
                scanf("%d", &number_tower[i][j]);
            }
        }
        dp[1][1] = number_tower[1][1];
        dp_level_max[1] = dp[1][1];
        for (int i = 2; i <= N; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - 1]) + number_tower[i][j];
                if (dp[i][j] > dp_level_max[i]) {
                    dp_level_max[i] = dp[i][j];
                }
            }
        }
        printf("%d\n", dp_level_max[N]);
    }
    return 0;
}